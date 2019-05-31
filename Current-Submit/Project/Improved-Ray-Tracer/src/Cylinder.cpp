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

#include "Cylinder.h"
#include "SolveQuadratic.h"

#include <array>
#include <cmath>

//== IMPLEMENTATION =========================================================

bool
Cylinder::
intersect(const Ray&  _ray,
          vec3&       _intersection_point,
          vec3&       _intersection_normal,
          double&     _intersection_t) const
{
    /** \todo
     * - compute the first valid intersection `_ray` with the cylinder
     *   (valid means in front of the viewer: t > 0)
     * - store intersection point in `_intersection_point`
     * - store ray parameter in `_intersection_t`
     * - store normal at _intersection_point in `_intersection_normal`.
     * - return whether there is an intersection with t > 0
    */

    // precompute redundant expressions for a, b and c
    vec3 delta_points                = _ray.origin - center;
    vec3 dot_ray_dir_axis_times_axis = dot(_ray.direction, axis) * axis;
    vec3 dot_delta_axis_times_axis   = dot(delta_points, axis)*axis;

    vec3 a_sqrt = (_ray.direction - dot_ray_dir_axis_times_axis);
    double a = dot(a_sqrt, a_sqrt);

    double b = 2 * dot(_ray.direction - dot_ray_dir_axis_times_axis,
                       delta_points - dot_delta_axis_times_axis);

    vec3 c_minus_r2_sqrt = delta_points - dot_delta_axis_times_axis;
    double c = dot(c_minus_r2_sqrt, c_minus_r2_sqrt) - radius*radius;

    std::array<double, 2> t;
    size_t nsol = solveQuadratic(a, b, c, t);

    _intersection_t = NO_INTERSECTION;

    for (size_t i = 0; i < nsol; ++i)
    {
        //check the solution is in font of the viewer,
        //closer than the others and does not exceed the height
        if (t[i] > 0 && t[i] < _intersection_t
                     && abs(dot(axis, _ray(t[i]) - center)) < height/2)
            _intersection_t = t[i];
    }

    if (_intersection_t == NO_INTERSECTION) return false;

    _intersection_point  = _ray(_intersection_t);
    
    //compute the normal as
    //the intersection point minus the orthogonal projection
    //of the intersection point on axis
    _intersection_normal = normalize(_intersection_point-
        (center + dot(_intersection_point - center, axis)*axis));

    // Take the normal pointing towards the viewer
    if (dot(_ray.direction, _intersection_normal) > 0)
    {
        _intersection_normal *= -1;
    }

    return true;
}
