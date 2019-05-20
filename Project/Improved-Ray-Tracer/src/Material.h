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

    /// refraction index (air=1, water=1.333, window glass=1.52, diamond=1.8)
    double refraction_index;

    /// transparency factor (if >0.0, material is refractive)
    double transparency;
};


//-----------------------------------------------------------------------------


/// read material from stream
inline std::istream& operator>>(std::istream& is, Material& m)
{
    is >> m.diffuse >> m.mirror >> m.refraction_index >> m.transparency;
    return is;
}


//=============================================================================
#endif // MATERIAL_H defined
//=============================================================================
