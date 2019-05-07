//
//  CutPlane.cpp
//  raytrace
//
//  Created by Samuel Chassot on 07.05.19.
//

//== INCLUDES =================================================================

#include "CutPlane.h"
#include <limits>


//== CLASS DEFINITION =========================================================



CutPlane::CutPlane(const vec3& _center, const vec3& _normal, const double _hole_radius)
: center(_center), normal(_normal), hole_radius(_hole_radius)
{
  plane = new Plane(center, normal);
}

//-----------------------------------------------------------------------------


bool
CutPlane::
intersect(const Ray& _ray,
          vec3&      _intersection_point,
          vec3&      _intersection_normal,
          double&    _intersection_t ) const
{

    if(plane->intersect(_ray, _intersection_point, _intersection_normal, _intersection_t)){
      // the ray intersects the plane, now need to check if point lays in the hole, if yes return false

      //distance computed using this formula http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
      double distance_squared;
      vec3 v1 = center - _intersection_point;
      double t1 = norm(v1);
      t1 = t1*t1;
      double t2 = 1; //norm(normal)
      double dotv1normal = dot(v1, normal);
      distance_squared = t1*t2 - dotv1normal*dotv1normal;

      if(distance_squared <= hole_radius*hole_radius) {
        _intersection_t = NO_INTERSECTION;
        return false;
      }
      return true;

    }
    return false;
}
