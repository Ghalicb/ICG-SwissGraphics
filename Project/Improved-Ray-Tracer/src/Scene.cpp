//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

//== INCLUDES =================================================================
#include "Scene.h"

#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Mesh.h"
#include "Cuboid.h"

#include <limits>
#include <map>
#include <functional>
#include <stdexcept>

#if HAS_TBB
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#endif

#define PATHS_PER_PIXEL 10
#define MAX_BOUNCE 15

Image Scene::render()
{
    // allocate new image.
    Image img(camera.width, camera.height);

    // Function rendering a full column of the image
    auto raytraceColumn = [&img, this](int x) {
        for (int y=0; y<int(camera.height); ++y)
        {
            Ray ray = camera.primary_ray(x,y);

            vec3 color = vec3(0.0);
            // compute color by tracing this ray
            for(int i=0; i<PATHS_PER_PIXEL; ++i){
              color += trace(ray, 0);
            }
            // avoid over-saturation
            color = min(color/PATHS_PER_PIXEL, vec3(1, 1, 1));

            // store pixel color
            img(x,y) = color;
        }
    };

    // If possible, raytrace image columns in parallel. We use TBB if available
    // and try OpenMP otherwise. Note that OpenMP only works on the latest
    // clang compilers, so macOS users will probably have the best luck with TBB.
    // You can install TBB with MacPorts/Homebrew, or from Intel:
    // https://github.com/01org/tbb/releases
#if HAS_TBB
    tbb::parallel_for(tbb::blocked_range<int>(0, camera.width), [&raytraceColumn](const tbb::blocked_range<int> &range) {
        for (size_t i = range.begin(); i < range.end(); ++i)
            raytraceColumn(i);
    });
#else
#if defined(_OPENMP)
#pragma omp parallel for
#endif
    for (int x=0; x<int(camera.width); ++x)
        raytraceColumn(x);
#endif

    // Note: compiler will elide copy.
    return img;
}

//-----------------------------------------------------------------------------

vec3 Scene::trace(const Ray& _ray, int _depth) {
    // stop if recursion depth (=number of reflections) is too large
    if (_depth > MAX_BOUNCE) return vec3(0,0,0);

    // Find first intersection with an object. If an intersection is found,
    // it is stored in object, point, normal, and t.
    Object_ptr  object;
    vec3        point;
    vec3        normal;
    double      t;
    if (!intersect(_ray, object, point, normal, t)) {
        return background;
    }

    // compute local Phong lighting (ambient+diffuse+specular)
    vec3 color = lighting(point, normal, -_ray.direction, object->material, _depth);

    return color;
}

//-----------------------------------------------------------------------------

bool Scene::intersect(const Ray& _ray, Object_ptr& _object, vec3& _point, vec3& _normal, double& _t)
{
    double  t, tmin(Object::NO_INTERSECTION);
    vec3    p, n;

    for (const auto &o: objects) // for each object
    {
        if (o->intersect(_ray, p, n, t)) // does ray intersect object?
        {
            if (t < tmin) // is intersection point the currently closest one?
            {
                tmin = t;
                _object = o.get();
                _point  = p;
                _normal = n;
                _t      = t;
            }
        }
    }

    return (tmin != Object::NO_INTERSECTION);
}

vec3 Scene::lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material, const int _depth) {

    vec3 color = vec3(0.0);

    double mirror_coeff = _material.mirror;

    // now we will do diffuse or specular with a probability mirror_coeff (it is between 0 and 1)
    // for that, generate a random number between 0 and 1 and check if it is smaller than mirror_coeff
    // if yes, do as specular, if not do as diffuse
    double random_number = (rand()%100)/100.0;

    if(random_number < mirror_coeff){
      //for specular, trace a new ray but reflected with respect to normal
      vec3 reflected_ray_dir = reflect(-_view, _normal);

      //take a vector only in the semi-space in normal direction, otherwise a ray can be traced inside objects
      // reflected_ray_dir = dot(reflected_ray_dir, _normal) < 0 ? -reflected_ray_dir : reflected_ray_dir;
      Ray reflected_ray = Ray(_point + EPSILON * _normal, reflected_ray_dir);
      vec3 color_traced = trace(reflected_ray, _depth + 1);

      color += color_traced;

    } else {
      //diffuse objects

      for (Light light : lights) {
          vec3 to_light_source = normalize(light.position - _point);

          // Add EPSILON times (*) the _normal to get the _point out of the object
          Ray        ray_to_light = Ray(_point + EPSILON * _normal, to_light_source);
          Object_ptr object_intersect;
          vec3       point_intersect;
          vec3       normal_intersect;
          double     t_intersect = 0.0;

          bool does_intersect = intersect(ray_to_light, object_intersect,
                                          point_intersect, normal_intersect,
                                          t_intersect);

          // if there is no intersection of if the intersection is beyond the
          // the light source, then there is no shadow
          if (!does_intersect || t_intersect > distance(light.position, _point)) {
              double dot_normal_light = dot(_normal, to_light_source);

              // the dot_normal_light and dot_reflection_light_view must be positive
              // to produce any effect to the viewed image
              double emittance_coeff = 0.2;
              if (dot_normal_light > 0) {
                  color += light.color * _material.diffuse * dot_normal_light + emittance_coeff * _material.diffuse;
              }
          }
      }


      //generate a random vector in 3D space
      vec3 random_reflected_ray_dir = vec3::random_vector();

      //take a vector only in the semi-space in normal direction, otherwise a ray can be traced inside objects
      random_reflected_ray_dir = dot(random_reflected_ray_dir, _normal) < 0 ? -random_reflected_ray_dir : random_reflected_ray_dir;
      Ray random_reflected_ray = Ray(_point + EPSILON * _normal, random_reflected_ray_dir);
      vec3 color_traced = trace(random_reflected_ray, _depth + 1);

      color += color_traced;

      color *= 1.0/2.0;

    }

    return color;
}

//-----------------------------------------------------------------------------

void Scene::read(const std::string &_filename)
{
    std::ifstream ifs(_filename);
    if (!ifs)
        throw std::runtime_error("Cannot open file " + _filename);

    const std::map<std::string, std::function<void(void)>> entityParser = {
        {"camera",     [&]() { ifs >> camera; }},
        {"background", [&]() { ifs >> background; }},
        {"ambience",   [&]() { ifs >> ambience; }},
        {"light",      [&]() { lights .emplace_back(ifs); }},
        {"plane",      [&]() { objects.emplace_back(new    Plane(ifs)); }},
        {"sphere",     [&]() { objects.emplace_back(new   Sphere(ifs)); }},
        {"cylinder",   [&]() { objects.emplace_back(new Cylinder(ifs)); }},
        {"mesh",       [&]() { objects.emplace_back(new Mesh(ifs, _filename)); }},
        {"cuboid",     [&]() { objects.emplace_back(new Cuboid(ifs)); }}
    };

    // parse file
    std::string token;
    while (ifs && (ifs >> token) && (!ifs.eof())) {
        if (token[0] == '#') {
            ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (entityParser.count(token) == 0)
            throw std::runtime_error("Invalid token encountered: " + token);
        entityParser.at(token)();
    }
}


//=============================================================================
