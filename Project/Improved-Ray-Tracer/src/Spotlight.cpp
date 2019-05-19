#include "Spotlight.h"
#include "Object.h"

#define PI 3.14159265

bool Spotlight::intersect(const Ray&  _ray,
                               vec3&  _intersection_point,
                               vec3&  _intersection_normal,
                             double&  _intersection_t) const
{
  _intersection_t = Object::NO_INTERSECTION;

  if (plane.intersect(_ray, _intersection_point, _intersection_normal, _intersection_t))
  {
    vec3 center_to_point = _intersection_point - plane.getCenter();

    if (dot(center_to_point, center_to_point) <= radius*radius)
    {
      return true;
    }
  }
  return false;

}

vec3 Spotlight::getLightPosition(int light_index) const
{
  double r = radius * (rand() % 1000) / 1000.0;
  double a = 2 * PI * (rand() % 1000) / 1000.0;

  vec3 temp = center + radius * cos(a) * vec3(1,0,0) + radius * sin(a) * vec3(0,0,1);

  return temp;
}

double Spotlight::getSurface() const
{
  return PI * radius * radius;
}
