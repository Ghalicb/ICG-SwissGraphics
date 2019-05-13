#include "Plane.h"
#include <limits>

bool
Plane::
intersect(const Ray& _ray,
               vec3& _intersection_point,
               vec3& _intersection_normal,
             double& _intersection_t ) const
{
    double denom = dot(normal, _ray.direction);

    if (denom == 0) return false;

    _intersection_t = dot(normal, center -_ray.origin)/denom;

    if (_intersection_t > 0) {
        _intersection_point = _ray(_intersection_t);

        _intersection_normal = normal;

        if (denom > 0)
        {
          _intersection_normal *= -1;
        }

        return true;
    }

    return false;
}
