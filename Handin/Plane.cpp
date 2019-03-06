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

#include "Plane.h"
#include <limits>


//== CLASS DEFINITION =========================================================



Plane::Plane(const vec3& _center, const vec3& _normal)
: center(_center), normal(_normal)
{
}


//-----------------------------------------------------------------------------


bool
Plane::
intersect(const Ray& _ray,
          vec3&      _intersection_point,
          vec3&      _intersection_normal,
          double&    _intersection_t ) const
{
    double denom = dot(normal, _ray.direction);

    // If the normal of the plan is perpendicular to the ray -> no intersection
    if (denom == 0) return false;

    // Otherwise we compute the point of intersection
    _intersection_t = dot(normal, center - _ray.origin)/ denom;
    
    // The plan is in front of the viewer
    if (_intersection_t > 0) {
        _intersection_point = _ray(_intersection_t);

        _intersection_normal = normal;

        // Take the normal pointing towards the viewer
        if (denom > 0) {
            _intersection_normal *= -1;
        }

        return true;
    }

    // The plan is behind the viewer
    return false;
}


//=============================================================================
