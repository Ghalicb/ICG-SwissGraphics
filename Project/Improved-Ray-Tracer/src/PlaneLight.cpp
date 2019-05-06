//
//  PlaneLight.cpp
//  raytrace
//
//  Created by Samuel Chassot on 05.05.19.
//

//== INCLUDES =================================================================

#include "PlaneLight.h"

PlaneLight::PlaneLight(const vec3& _center, const vec3& _x_side_dir, const vec3& _y_side_dir,
const double _size, const vec3& _color)
:center(_center), x_side_dir(_x_side_dir), y_side_dir(_y_side_dir), size(_size), color(_color)
{
  normal = normalize(cross(x_side_dir, y_side_dir));
  x_side_dir = normalize(x_side_dir);
  y_side_dir = normalize(y_side_dir);
}

bool intersect(const Ray&        _ray,
                     vec3&       _intersection_point,
                     vec3&       _intersection_normal,
                     double&     _intersection_t)
{
  double denom = dot(normal, _ray.direction);

  // If the normal of the plan is perpendicular to the ray -> no intersection
  if (denom == 0) return false;

  // Otherwise we compute the point of intersection
  _intersection_t = dot(normal, center - _ray.origin)/ denom;

  // The plan is in front of the viewer
  if (_intersection_t > 0) {
      _intersection_point = _ray(_intersection_t);

      //check if the intersection is in the square centered at _center and and of size _size
      vec3 center_to_intersection = _intersection_point - center;

      double delta_x = std::abs(dot(center_to_intersection, x_side_dir));
      double delta_y = std::abs(dot(center_to_intersection, y_side_dir));

      if(delta_x > size/2 || delta_y > size/2) {
        // the intersection point lays outside the bounds of the light
        return false
      }

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
