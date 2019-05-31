//== INCLUDES =================================================================

#include "ClosedCylinder.h"
#include "Cylinder.h"

//== IMPLEMENTATION =========================================================

bool ClosedCylinder::intersect(const Ray&  _ray,
                           vec3&       _intersection_point,
                           vec3&       _intersection_normal,
                           double&     _intersection_t) const 
{
    vec3 intersection_point_tmp;
    vec3 intersection_normal_tmp;
    double intersection_t_tmp = NO_INTERSECTION;
    bool is_intersecting = false;

    if (cylinder.intersect(_ray, intersection_point_tmp, intersection_normal_tmp, intersection_t_tmp)
        && intersection_t_tmp > 0) {
        _intersection_point = intersection_point_tmp;
        _intersection_normal = intersection_normal_tmp;
        _intersection_t = intersection_t_tmp;
        is_intersecting = true;
    }

    if (upperPlane.intersect(_ray, intersection_point_tmp, intersection_normal_tmp, intersection_t_tmp)
        && norm(intersection_point_tmp - upperPlane.getCenter()) <= cylinder.getRadius() 
        && intersection_t_tmp > 0) {
        if (_intersection_t > intersection_t_tmp) {
            _intersection_point = intersection_point_tmp;
            _intersection_normal = intersection_normal_tmp;
            _intersection_t = intersection_t_tmp;
            is_intersecting = true;

        }
    }

    if (bottomPlane.intersect(_ray, intersection_point_tmp, intersection_normal_tmp, intersection_t_tmp)
    && norm(intersection_point_tmp - bottomPlane.getCenter()) <= cylinder.getRadius()) {
        if (_intersection_t > intersection_t_tmp) {
            _intersection_point = intersection_point_tmp;
            _intersection_normal = intersection_normal_tmp;
            _intersection_t = intersection_t_tmp;
            is_intersecting = true;

        }
    }

    return is_intersecting;
}