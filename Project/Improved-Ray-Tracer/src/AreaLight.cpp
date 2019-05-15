#include "AreaLight.h"

bool
AreaLight::
intersect(const Ray&  _ray,
               vec3&  _intersection_point,
               vec3&  _intersection_normal,
             double&  _intersection_t) const
{
  _intersection_t = NO_INTERSECTION;

  if (plane.intersect(_ray, _intersection_point, _intersection_normal, _intersection_t))
  {
    vec3 center_to_point = _intersection_point - plane.getCenter();

    double dot_ctp_x_axis = fabs(dot(center_to_point, x_axis));
    double dot_ctp_y_axis = fabs(dot(center_to_point, y_axis));

    if (dot_ctp_x_axis <= x_size/2 && dot_ctp_y_axis <= y_size/2)
    {
      return true;
    }
  }
  return false;
}

vec3
AreaLight::
get_light_intensity(int light_index)
{
  return vec3(1);
}
