//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

#ifndef VEC3_H
#define VEC3_H

//== INCLUDES =================================================================

#include <iostream>
#include <assert.h>
#include <math.h>
#include <algorithm>

#include <stdlib.h>     // for rand()

#define PI 3.14159265


//== CLASS DEFINITION =========================================================


/// \file vec3.h Implements the vector class and its mathematical operations.


/// \class vec3 vec3.h
/// This class implements a simple 3D vector, that we use to represent
/// 3D points and 3D color. You can access the individual components either by
/// x,y,z or by r,g,b. The vec3 class provides all commonly used mathematical
/// operations.
/// \sa vec3.h
class vec3
{
private:

    double data_[3];

public:

    /// default constructor
    vec3() {}

    /// construct with scalar value that is assigned to x, y, and z
    /// The "explicit" keyword prevents automatic conversions
    /// from double to vec3, which generally should indicate bugs.
    explicit vec3(double _s) : data_{_s,_s,_s} {}

    /// construct with x,y,z values
    vec3(double _x, double _y, double _z) : data_{_x,_y,_z} {}


    /// read/write the _i'th vector component (_i from 0 to 2)
    double& operator[](unsigned int _i)
    {
        assert(_i < 3);
        return data_[_i];
    }

    /// read the _i'th vector component (_i from 0 to 2)
    const double operator[](unsigned int _i) const
    {
        assert(_i < 3);
        return data_[_i];
    }


    /// multiply this vector by a scalar \c s
    vec3& operator*=(const double s)
    {
        for (int i=0; i<3; ++i) data_[i] *= s;
        return *this;
    }

    /// divide this vector by a scalar \c s
    vec3& operator/=(const double s)
    {
        for (int i=0; i<3; ++i) data_[i] /= s;
        return *this;
    }

    /// component-wise multiplication of this vector with vector \c v
    vec3& operator*=(const vec3& v)
    {
        for (int i=0; i<3; ++i) data_[i] *= v[i];
        return *this;
    }

    /// subtract vector \c v from this vector
    vec3& operator-=(const vec3& v)
    {
        for (int i=0; i<3; ++i) data_[i] -= v[i];
        return *this;
    }

    /// add vector \c v to this vector
    vec3& operator+=(const vec3& v)
    {
        for (int i=0; i<3; ++i) data_[i] += v[i];
        return *this;
    }

    /// create a random vector in space, normalized
    static vec3 random_vector()
    {
        double a = 2*PI*(rand()%100000)/100000.0;
        double b = 2*PI*(rand()%100000)/100000.0;

        double sina = sin(a);
        double sinb = sin(b);
        double cosa = cos(a);
        double cosb = cos(b);

        return vec3(sina*sinb, -sina*cosb, cosa);
    }
};


//-----------------------------------------------------------------------------


/// unary minus: turn v into -v
inline const vec3 operator-(const vec3& v)
{
    return vec3(-v[0], -v[1], -v[2]);
}

/// multiply vector \c v by scalar \c s
inline const vec3 operator*(const double s, const vec3& v )
{
    return vec3(s * v[0],
                s * v[1],
                s * v[2]);
}

/// multiply vector \c v by scalar \c s
inline const vec3 operator*(const vec3& v, const double s)
{
    return vec3(s * v[0],
                s * v[1],
                s * v[2]);
}

/// component-wise multiplication of vectors \c v0 and \c v1
inline const vec3 operator*(const vec3& v0, const vec3& v1)
{
    return vec3(v0[0] * v1[0],
                v0[1] * v1[1],
                v0[2] * v1[2]);
}

/// divide vector \c v by scalar \c s
inline const vec3 operator/(const vec3& v, const double s)
{
    return vec3(v[0] / s,
                v[1] / s,
                v[2] / s);
}

/// component-wise division of vectors \c v0 by \c v1
inline const vec3 operator/(const vec3& v0, const vec3& v1)
{
  return vec3(v0[0] / v1[0],
              v0[1] / v1[1],
              v0[2] / v1[2]);
}

/// add two vectors \c v0 and \c v1
inline const vec3 operator+(const vec3& v0, const vec3& v1)
{
    return vec3(v0[0] + v1[0],
                v0[1] + v1[1],
                v0[2] + v1[2]);
}

/// subtract vector \c v1 from vector \c v0
inline const vec3 operator-(const vec3& v0, const vec3& v1)
{
    return vec3(v0[0] - v1[0],
                v0[1] - v1[1],
                v0[2] - v1[2]);
}

/// compute the component-wise minimum of vectors \c v0 and \c v1
inline const vec3 min(const vec3& v0, const vec3& v1)
{
    return vec3(std::min(v0[0], v1[0]),
                std::min(v0[1], v1[1]),
                std::min(v0[2], v1[2]));
}

/// compute the component-wise maximum of vectors \c v0 and \c v1
inline const vec3 max(const vec3& v0, const vec3& v1)
{
    return vec3(std::max(v0[0], v1[0]),
                std::max(v0[1], v1[1]),
                std::max(v0[2], v1[2]));
}

/// compute the Euclidean dot product of \c v0 and \c v1
inline const double dot(const vec3& v0, const vec3& v1)
{
    return (v0[0]*v1[0] + v0[1]*v1[1] + v0[2]*v1[2]);
}

/// compute the Euclidean norm (length) of a vector \c v
inline const double norm(const vec3& v)
{
    return sqrt(dot(v,v));
}

/// normalize vector \c v by dividing it by its norm
inline const vec3 normalize(const vec3& v)
{
    const double n = norm(v);
    if (n != 0.0)
    {
        return vec3(v[0] / n,
                    v[1] / n,
                    v[2] / n);
    }
    return v;
}

/// compute the distance between vectors \c v0 and \c v1
inline const double distance(const vec3& v0, const vec3& v1)
{
    return norm(v0-v1);
}

/// compute the cross product of \c v0 and \c v1
inline const vec3 cross(const vec3& v0, const vec3& v1)
{
    return vec3(v0[1]*v1[2] - v0[2]*v1[1],
                v0[2]*v1[0] - v0[0]*v1[2],
                v0[0]*v1[1] - v0[1]*v1[0]);
}

/// reflect vector \c v at normal \c n
inline const vec3 reflect(const vec3& v, const vec3& n)
{
    return v - (2.0 * dot(n,v)) * n;
}

/// reflect vector \c v at normal \c n
inline const vec3 reflect_glossy(const vec3& v, const vec3& n, const double angle)
{
  double random_angle = angle*(rand()%100000)/100000.0;

  if ((rand()%100000)/100000.0 >= 0.5)
  {
    random_angle *= -1;
  }

  double c = cos(random_angle);
  double s = sin(random_angle);

  vec3 rotate_around_vector = normalize(cross(v, n));
  double x = rotate_around_vector[0];
  double y = rotate_around_vector[1];
  double z = rotate_around_vector[2];

  vec3 reflected_vector = v - (2.0 * dot(n,v)) * n;

  return vec3((x*x*(1-c)+c)  *reflected_vector[0] + (x*y*(1-c)-z*s)*reflected_vector[1] + (x*z*(1-c)+y*s)*reflected_vector[2],
              (x*y*(1-c)+z*s)*reflected_vector[0] + (y*y*(1-c)+c)  *reflected_vector[1] + (y*z*(1-c)-x*s)*reflected_vector[2],
              (x*z*(1-c)-y*s)*reflected_vector[0] + (y*z*(1-c)+x*s)*reflected_vector[1] + (z*z*(1-c)+c)  *reflected_vector[2]);
}

/// refract vector \c v at normal \c n according to \c eta = refraction_indexes_quotient (n1/n2)
/// this method takes into account the total reflection possibility
inline const vec3 refract(const vec3& v, const vec3& n, const float refr_ind)
{
  bool ray_going_into = dot(n,v) < 0;
  vec3 normal = ray_going_into ? n : -n;
  double etaIn = 1.0;
  double etaOut = refr_ind;
  double eta = ray_going_into ? etaIn/etaOut : etaOut/etaIn;
  double cosIn = dot(v, normal);
  double cosSquareOut = 1.0f - eta*eta*(1 - cosIn*cosIn);

  return normalize(v*eta - normal*(cosIn*eta + sqrtf(cosSquareOut)));
}

/// compute the Schlick's approximation of the Fresnel reflectivity coefficient
inline const float fresnel(const vec3& v, const vec3& n, float refr_ind, const vec3& refracted_dir){
  bool ray_going_into = dot(n,v) < 0;
  double etaIn = 1.0;
  double etaOut = refr_ind;
  double eta = ray_going_into ? etaIn/etaOut : etaOut/etaIn;

  double a = etaOut - etaIn;
  double b = etaOut + etaIn;
  double f0 = a*a/(b*b);

  double cosIn = ray_going_into ? dot(v,-n) : dot(v,n);

  double c = 1 - cosIn;
  double res = f0 + (1 - f0)*c*c*c*c*c;

  return res;
}

inline const bool total_reflection(const vec3& v, const vec3& n, float refr_ind){
  bool ray_going_into = dot(n,v) < 0;
  double etaIn = 1.0;
  double etaOut = refr_ind;
  double eta = ray_going_into ? etaIn/etaOut : etaOut/etaIn;
  double cosIn = ray_going_into ? dot(v,n) : dot(v,-n);
  return 1.0f - eta*eta*(1 - cosIn*cosIn) < 0;
}

/// mirrors vector \c v at normal \c n
inline const vec3 mirror(const vec3& v, const vec3& n)
{
    return (2.0 * dot(n,v)) * n - v;
}

/// read the space-separated components of a vector from a stream
inline std::istream& operator>>(std::istream& is, vec3& v)
{
    is >> v[0] >> v[1] >> v[2];
    return is;
}

/// output a vector by printing its comma-separated compontens
inline std::ostream& operator<<(std::ostream& os, const vec3& v)
{
    os << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
    return os;
}


//=============================================================================
#endif // VEC3_H
//=============================================================================
