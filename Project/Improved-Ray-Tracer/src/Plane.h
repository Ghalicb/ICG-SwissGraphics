#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "vec3.h"

#include <float.h>

class Plane : public Object
{
public:
    Plane(const vec3& _center=vec3(0,0,0),
          const vec3& _normal=vec3(0,1,0),
          const double _outer_radius=FLT_MAX,
          const double _hole_radius=0.0):center(_center),
                                         normal(_normal),
                                         outer_radius(_outer_radius),
                                         hole_radius(_hole_radius){}

    Plane(std::istream &is) { parse(is); }

    virtual bool intersect(const Ray& _ray,
                                vec3& _intersection_point,
                                vec3& _intersection_normal,
                              double& _intersection_t) const override;

    virtual void parse(std::istream &is) override
    {
        is >> center >> normal >> outer_radius >> hole_radius >> material;

        normal = normalize(normal);

        if (hole_radius <= 0.0)
        {
          hole_radius = 0.0;
        }
    }

    const vec3 getCenter() const { return center; }

private:
    vec3 center;
    vec3 normal;

    double outer_radius;
    double hole_radius;
};

#endif
