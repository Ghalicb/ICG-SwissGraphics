#include "Cuboid.h"

#include "Plane.h"

bool
Cuboid::
intersect(const Ray&  _ray,
               vec3&  _intersection_point,
               vec3&  _intersection_normal,
             double&  _intersection_t) const
{
  std::array<double, 2> t;

  for (size_t i = 0; i < faces.size(); ++i)
  {
    #TODO
  }
  return true;
}
