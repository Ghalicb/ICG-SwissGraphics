#include "Scene.h"

#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Mesh.h"
#include "Cuboid.h"
#include "Light.h"
#include "AreaLight.h"
#include "Spotlight.h"
#include "ClosedCylinder.h"

#include <limits>
#include <map>
#include <functional>
#include <stdexcept>

#if HAS_TBB
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>
#endif

#define PATHS_PER_PIXEL 4
#define MAX_BOUNCE 2
#define AMBIENT_REFRACTION_INDEX (1.0)

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
              //assume that we raytrace scenes where camera is in air (refraction_index = 1.0)
              double _ambient_refraction_index = 1.0;
              color += trace(ray, 0, AMBIENT_REFRACTION_INDEX);
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
    using namespace tbb;
    typedef mutex myMutex;
    static myMutex mut;
    myMutex::scoped_lock lock;
    int done = 0;
    int total = camera.width;
    int done_percents = 0;
    std::cout << '\n';
    tbb::parallel_for(tbb::blocked_range<int>(0, camera.width), [&raytraceColumn, &done, &lock, &total, &done_percents](const tbb::blocked_range<int> &range) {
        for (size_t i = range.begin(); i < range.end(); ++i){
            raytraceColumn(i);
            lock.acquire(mut);
            done = done + 1;
            int done_percents_temp = done*100/total;
            if(done_percents_temp > done_percents){
              done_percents = done_percents_temp;
              std::cout << "\r" << done_percents << " percents" << std::flush;
            }
            lock.release();
        }
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

vec3 Scene::trace(const Ray& _ray, int _depth, double _current_refraction_index) {
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

    normal = dot(normal, -_ray.direction) > 0 ? normal : -normal;
    vec3 color = vec3(0.0);

    if(object->isLight()){
      Light* al = dynamic_cast<Light*>(object);
      color = al->getColor();
    } else {
      color = lighting(point, normal, -_ray.direction, object->material, _depth, _current_refraction_index);
    }

    return color;
}

//-----------------------------------------------------------------------------

bool Scene::intersect(const Ray& _ray, Object_ptr& _object, vec3& _point, vec3& _normal, double& _t)
{
    double  t, tmin(Object::NO_INTERSECTION);
    vec3    p, n;

    for (const auto &o: objects)
    {
      if (o->intersect(_ray, p, n, t))
      {
        if (t < tmin)
        {
          tmin    = t;
          _object = o.get();
          _point  = p;
          _normal = n;
          _t      = t;
        }
      }
    }

    for (const auto &al: lights)
    {
      if (al->intersect(_ray, p, n, t))
      {
        if (t < tmin)
        {
          tmin    = t;
          _object = al.get();
          _point  = p;
          _normal = n;
          _t      = t;
        }
      }
    }

    return (tmin != Object::NO_INTERSECTION);
}

vec3 Scene::lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material, const int _depth, double _current_refraction_index) {

    vec3 point = _point + EPSILON * _normal;

    vec3 color = vec3(0.0);
    double mirror_coeff = _material.mirror;
    double transparency_coeff = _material.transparency;

    // now we will do diffuse or specular with a probability mirror_coeff (it is between 0 and 1)
    // for that, generate a random number between 0 and 1 and check if it is smaller than mirror_coeff
    // if yes, do as specular, if not do as diffuse
    double random_number = (rand()%100)/100.0;

    if(random_number < mirror_coeff){
      //for specular, trace a new ray but reflected with respect to normal
      vec3 reflected_ray_dir = reflect(-_view, _normal);

      //take a vector only in the semi-space in normal direction, otherwise a ray can be traced inside objects
      // reflected_ray_dir = dot(reflected_ray_dir, _normal) < 0 ? -reflected_ray_dir : reflected_ray_dir;
      Ray reflected_ray = Ray(point, reflected_ray_dir);
      vec3 color_traced = trace(reflected_ray, _depth + 1, _current_refraction_index);

      color += color_traced;

    } else if(random_number < mirror_coeff + transparency_coeff){
      //here do transparent work (using refraction laws)
      double refraction_index = _material.refraction_index;

      double refraction_indexes_quotient;
      double next_refraction_index;
      if(_current_refraction_index == AMBIENT_REFRACTION_INDEX){
        // go into the object
        refraction_indexes_quotient = AMBIENT_REFRACTION_INDEX/refraction_index;
        next_refraction_index = refraction_index;
      } else {
        // go out of the object
        refraction_indexes_quotient = refraction_index/AMBIENT_REFRACTION_INDEX;
        next_refraction_index = AMBIENT_REFRACTION_INDEX;
      }

      vec3 refracted_ray_dir = refract(-_view, _normal, refraction_indexes_quotient);

      // here -EPSILON*normal because we go inside the object
      Ray refracted_ray = Ray(_point - EPSILON * _normal, refracted_ray_dir);
      vec3 color_traced = trace(refracted_ray, _depth + 1, next_refraction_index);
      color += color_traced;


    } else {
      //diffuse objects

      vec3 direct_illumination = vec3(0.0);

      for (const auto &al: lights)
      {
        for (size_t i = 0; i < al->getNumberOfLights(); ++i)
        {
          vec3 lightPosition = al->getLightPosition(i) - vec3(0, EPSILON, 0);
          vec3 to_light_source = normalize(lightPosition - point);

          // Add EPSILON times (*) the _normal to get the point out of the object
          Ray        ray_to_light = Ray(point, to_light_source);
          Object_ptr object_intersect;
          vec3       point_intersect;
          vec3       normal_intersect;
          double     t_intersect = 0.0;

          bool does_intersect = intersect(ray_to_light, object_intersect,
                                          point_intersect, normal_intersect,
                                          t_intersect);

          if ((!does_intersect || t_intersect > distance(lightPosition, point)) &&
              (!al->isSpotlight() || (al->isSpotlight() && to_light_source[1] >= 0.98))) {
              double dot_normal_light = dot(_normal, to_light_source);
              if (dot_normal_light > 0) {
                  direct_illumination += al->getLightIntensity() * al->getSurface() / lightsTotalSurface * _material.diffuse * dot_normal_light;
              }
          }
        }
      }
      color += direct_illumination;

      vec3 indirect_illumination = vec3(0.0);

      // generate a random vector in 3D space
      vec3 random_reflected_ray_dir = vec3::random_vector();

      //take a vector only in the semi-space in normal direction, otherwise a ray can be traced inside objects
      random_reflected_ray_dir = dot(random_reflected_ray_dir, _normal) < 0 ? -random_reflected_ray_dir : random_reflected_ray_dir;
      Ray random_reflected_ray = Ray(point, random_reflected_ray_dir);
      vec3 color_traced = trace(random_reflected_ray, _depth + 1, _current_refraction_index);

      indirect_illumination += color_traced * dot(random_reflected_ray_dir, _normal);

      color += _material.diffuse*indirect_illumination;
    }

    return color;
}

void Scene::read(const std::string &_filename)
{
    std::ifstream ifs(_filename);
    if (!ifs)
        throw std::runtime_error("Cannot open file " + _filename);

    const std::map<std::string, std::function<void(void)>> entityParser = {
        {"camera",        [&]() { ifs >> camera; }},
        {"background",    [&]() { ifs >> background; }},
        {"areaLight",     [&]() { lights.emplace_back(new AreaLight(ifs)); }},
        {"light",         [&]() { lights.emplace_back(new Spotlight(ifs)); }},
        {"plane",         [&]() { objects.emplace_back(new Plane(ifs)); }},
        {"sphere",        [&]() { objects.emplace_back(new Sphere(ifs)); }},
        {"cylinder",      [&]() { objects.emplace_back(new Cylinder(ifs)); }},
        {"mesh",          [&]() { objects.emplace_back(new Mesh(ifs, _filename)); }},
        {"cuboid",        [&]() { objects.emplace_back(new Cuboid(ifs)); }},
        {"closedCylinder",[&]() { objects.emplace_back(new ClosedCylinder(ifs)); }}
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

    for (const auto &l: lights)
    {
      lightsTotalSurface += l->getSurface();
    }
}
