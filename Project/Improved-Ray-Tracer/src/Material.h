#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

struct Material
{
    vec3 color;
    bool mirror;
    bool transparent;
    ///air=1, water=1.333, window glass=1.52, diamond=1.8
    double refraction_index;
    ///0=perfect mirror, 1~=diffuse
    double glossy_index;
};

inline std::istream& operator>>(std::istream& is, Material& m)
{
    is >> m.color >> m.mirror >> m.transparent >> m.refraction_index >> m.glossy_index;
    return is;
}

#endif
