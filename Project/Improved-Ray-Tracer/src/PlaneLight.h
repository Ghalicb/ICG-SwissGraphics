//
//  PlaneLight.h
//  raytrace
//
//  Created by Samuel Chassot on 05.05.19.
//

#ifndef PLANELIGHT_H
#define PLANELIGHT_H

//== INCLUDES =================================================================

#include "Object.h"
#include "vec3.h"


//== CLASS DEFINITION =========================================================

class PlaneLight : public Object
{
public:
    /// constructor
    PlaneLight(const vec3& _center=vec3(0,0,0), const vec3& _x_side_dir=vec3(1,0,0), const vec3& _y_side_dir=vec3(0,1,0),
    const double _size=1.0, const vec3& _color=vec3(1.0, 1.0, 1.0));

    /// Construct a plane light with parameters parsed from an input stream.
    PlaneLight(std::istream &is) { parse(is); }

    /// Compute the intersection of the plane light with \c _ray. Return whether
    /// there is an intersection. If there is one, return the intersection data.
    /// This function overrides Object::intersect().
    /// \param[in] _ray the ray to intersect the planeLight with
    /// \param[out] _intersection_point position of the intersection
    /// \param[out] _intersection_normal normal vector at the intersection point
    /// \param[out] _intersection_t ray parameter at the intesection point
    virtual bool intersect(const Ray&  _ray,
                           vec3&       _intersection_point,
                           vec3&       _intersection_normal,
                           double&     _intersection_t) const override;

    /// parse plane light from an input stream
    virtual void parse(std::istream &is) override {
        is >> center >> x_side_dir >> y_side_dir >> size >> color;
        normal = normalize(cross(x_side_dir, y_side_dir));
        x_side_dir = normalize(x_side_dir);
        y_side_dir = normalize(y_side_dir);
    }

private:
    /// center point on the plane light
    vec3 center;
    /// vector (normalized) giving a side of the square
    vec3 x_side_dir;
    /// vector (normalized) giving a side of the square
    vec3 y_side_dir;
    /// normal vector of the plane light
    vec3 normal;
    /// size of a side of the square plane light
    double size;
    /// color of the light
    vec3 color;
};

#endif
