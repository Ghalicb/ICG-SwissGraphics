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

    vec3 delta_points = _ray.origin - center;
    double dot_ray_dir_axis = dot(_ray.direction, axis);
    vec3 dot_delta_axis_times_axis = dot(delta_points, axis)*axis;

    vec3 a_sqrt = (_ray.direction - dot_ray_dir_axis* axis);
    double a = dot(a_sqrt, a_sqrt);

    double b = 2 * dot(_ray.direction - dot_ray_dir_axis * axis,
                       dot_delta_axis_times_axis);

    vec3 c_minus_r2_sqrt = delta_points - dot_delta_axis_times_axis;
    double c = dot(c_minus_r2_sqrt, c_minus_r2_sqrt) - radius*radius;

    //solveQuadratic(a, b, c, );

    return false;
}
