#ifndef SCENE_H
#define SCENE_H

#define EPSILON 0.00000000001

#include "StopWatch.h"
#include "Object.h"
#include "Light.h"
#include "AreaLight.h"
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

    vec3  trace(const Ray& _ray, int _depth);

    bool  intersect(const Ray& _ray, Object_ptr& _Object_ptr, vec3& _point, vec3& _normal, double& _t);

    vec3  lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material, int _depth);

    void read(const std::string &filename);

    size_t numObjects() const { return objects.size(); }

    const std::vector<std::unique_ptr<Object>> &getObjects() const { return objects; }

    const Camera &getCamera() const { return camera; }

private:
    Camera camera;

    std::vector<Light> lights;
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<AreaLight>> areaLights;

    vec3 background = vec3(0, 0, 0);
};

#endif
