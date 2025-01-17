#ifndef SCENE_H
#define SCENE_H

#define EPSILON 0.00000000001

#include "StopWatch.h"
#include "Object.h"
#include "Light.h"
#include "Ray.h"
#include "Material.h"
#include "Image.h"
#include "Camera.h"

#include <memory>
#include <string>

class Scene {
public:

    Scene(const std::string &path) {
        read(path);
    }

    Image  render();

    /// Determine the color seen by a viewing ray
    /**
    *   @param[in] _ray passed Ray
    *   @param[in] _depth holds the information, how many times the `_ray` had been reflected. Goes from 0 to max_depth. Should be used for recursive function call.
    *   @return    color
    **/
    vec3  trace(const Ray& _ray, int _depth, bool shadow_rays);

    bool  intersect(const Ray& _ray, Object_ptr& _Object_ptr, vec3& _point, vec3& _normal, double& _t);

    /// Computes the phong lighting for a given object intersection
    /**
    *   @param _point the point, whose color should be determined.
    *   @param _normal `_point`'s normal
    *   @param _view normalized direction from the point to the viewer's position.
    *   @param _material holds material parameters of the `_point`, that should be lit.
    *   @param[in] _depth holds the information, how many times the `_ray` had been reflected. Goes from 0 to max_depth. Should be used for recursive function call.
    */
    vec3  lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material, int _depth, bool shadow_rays);

    void read(const std::string &filename);

    size_t numObjects() const { return objects.size(); }

    const std::vector<std::unique_ptr<Object>> &getObjects() const { return objects; }

    const Camera &getCamera() const { return camera; }

    double lightsTotalSurface = 0;

private:
    Camera camera;

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Light>>  lights;

    vec3 background = vec3(0, 0, 0);

    int max_depth = 0;

    int paths_per_pixel = 0;
};

#endif
