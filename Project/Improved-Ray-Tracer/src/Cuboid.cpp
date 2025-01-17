#include "Cuboid.h"

bool
Cuboid::
intersect(const Ray&  _ray,
               vec3&  _intersection_point,
               vec3&  _intersection_normal,
             double&  _intersection_t) const
{
  _intersection_t = NO_INTERSECTION;

  int solutions = 0;

  for (size_t i = 0; i < faces.size(); ++i)
  {
    if (solutions >= 2) break;
    Plane f = faces[i];

    vec3   intersection_point;
    vec3   intersection_normal;
    double intersection_t;

    if (f.intersect(_ray, intersection_point, intersection_normal, intersection_t))
    {
      vec3 center_to_point = intersection_point - f.getCenter();

      if (norm(center_to_point) <= max_size)
      {
        bool in_cuboid = false;

        double dot_ctp_x_axis;
        double dot_ctp_y_axis;
        double dot_ctp_z_axis;

        switch (i) {
          case 0:
          case 1:
            dot_ctp_y_axis = fabs(dot(center_to_point, y_axis));
            dot_ctp_z_axis = fabs(dot(center_to_point, z_axis));
            if (dot_ctp_y_axis <= y_size/2 && dot_ctp_z_axis <= z_size/2) {in_cuboid = true; }
            break;
          case 2:
          case 3:
            dot_ctp_x_axis = fabs(dot(center_to_point, x_axis));
            dot_ctp_z_axis = fabs(dot(center_to_point, z_axis));
            if (dot_ctp_x_axis <= x_size/2 && dot_ctp_z_axis <= z_size/2) { in_cuboid = true; }
            break;
          case 4:
          case 5:
            dot_ctp_x_axis = fabs(dot(center_to_point, x_axis));
            dot_ctp_y_axis = fabs(dot(center_to_point, y_axis));
            if (dot_ctp_x_axis <= x_size/2 && dot_ctp_y_axis <= y_size/2) { in_cuboid = true; }
            break;
        }

        if (in_cuboid && intersection_t > 0 && intersection_t < _intersection_t)
        {
          _intersection_point  = intersection_point;
          _intersection_normal = intersection_normal;
          _intersection_t      = intersection_t;

          ++solutions;
        }
      }
    }
  }

  return !(solutions <= 0 || _intersection_t >= NO_INTERSECTION);
}
