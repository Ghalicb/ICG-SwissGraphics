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
};


//-----------------------------------------------------------------------------


/// read material from stream
inline std::istream& operator>>(std::istream& is, Material& m)
{
    is >> m.diffuse >> m.mirror;
    return is;
}


//=============================================================================
#endif // MATERIAL_H defined
//=============================================================================
