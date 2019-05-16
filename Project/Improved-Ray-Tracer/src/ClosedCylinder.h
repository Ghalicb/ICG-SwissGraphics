#ifndef CLOSED_CYLINDER_H
#define CLOSED_CYLINDER_H

//== INCLUDES =================================================================

#include "Object.h"
#include "Cylinder.h"
#include "Plane.h"
#include "vec3.h"

//== CLASS DEFINITION =========================================================


/// \class ClosedCylinder Cylinder.h
/// This class implements a closed cylinder object, which is specified by one
/// open cylinder and two closed planes.
class ClosedCylinder : public Object {
    public:
        /// Construct a closed cylinder by directly specifying its parameters
        ClosedCylinder(const vec3 &_center = vec3(0,0,0),
                double _radius = 1,
                const vec3 &_axis = vec3(1,0,0),
                double _height = 1)
            :  cylinder(_center,_radius,_axis,_height), 
                upperPlane(_center + _height/2.*_axis, _axis),
                bottomPlane(_center - _height/2*_axis, -_axis) { }

        /// Construct a closed cylinder with parameters parsed from an input stream.
        ClosedCylinder(std::istream &is) { parse(is); }

        virtual bool intersect(const Ray&  _ray,
                           vec3&       _intersection_point,
                           vec3&       _intersection_normal,
                           double&     _intersection_t) const override;

        /// parse closed cylinder from an input stream
        virtual void parse(std::istream &is) override {
            vec3 center;
            double radius;
            vec3 axis;
            double height; 
            axis = normalize(axis);

            is >> center >> radius >> axis >> height >> material;
            cylinder = Cylinder(center, radius, axis, height);
            upperPlane = Plane(center + height/2.*axis, axis);
            upperPlane = Plane(center - height/2.*axis, -axis);
        }

    private:
        Cylinder cylinder;
        Plane upperPlane;
        Plane bottomPlane;
};


#endif