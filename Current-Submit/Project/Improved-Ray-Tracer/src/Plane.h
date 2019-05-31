#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "vec3.h"

#include <float.h>

class Plane : public Object
{
public:
    Plane(const vec3& _center=vec3(0,0,0),
          const vec3& _normal=vec3(0,1,0)):center(_center),
                                           normal(_normal){}

    Plane(std::istream &is) { parse(is); }

    virtual bool intersect(const Ray& _ray,
                                vec3& _intersection_point,
                                vec3& _intersection_normal,
                              double& _intersection_t) const override;

    virtual void parse(std::istream &is) override
    {
        is >> center >> normal >> material;

        normal = normalize(normal);
    }

    const vec3 getCenter() const { return center; }

private:
    vec3 center;
    vec3 normal;
};

#endif
