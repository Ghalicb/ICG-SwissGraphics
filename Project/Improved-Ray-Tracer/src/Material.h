//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

#ifndef MATERIAL_H
#define MATERIAL_H


//== INCLUDES =================================================================

#include "vec3.h"


//== CLASS DEFINITION =========================================================


/// \class Material Material.h
/// This class stores all material parameters.
struct Material
{
    /// diffuse color
    vec3   diffuse;

    /// reflectivity factor (1=perfect mirror, 0=no reflection).
    double mirror;

    /// refraction coefficient (air=1, water=1.333, window glass=1.52)
    double refraction_coeff;

    /// transparency factor (1=perfectly transparent, 0=complete opacity)
    double transparency;
};


//-----------------------------------------------------------------------------


/// read material from stream
inline std::istream& operator>>(std::istream& is, Material& m)
{
    is >> m.diffuse >> m.mirror >> m.refraction_coeff >> m.transparency;
    return is;
}


//=============================================================================
#endif // MATERIAL_H defined
//=============================================================================
