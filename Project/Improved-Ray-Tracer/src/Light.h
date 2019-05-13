#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

struct Light
{
    Light(std::istream &is) { is >> position >> color; }

    vec3 position;
    vec3 color;
};

inline std::istream& operator>>(std::istream& is, Light& l)
{
    l = Light(is);
    return is;
}

#endif
