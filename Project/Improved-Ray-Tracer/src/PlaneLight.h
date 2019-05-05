//
//  PlaneLight.h
//  raytrace
//
//  Created by Samuel Chassot on 05.05.19.
//

//== INCLUDES =================================================================

#include "vec3.h"


//== CLASS DEFINITION =========================================================

/// The class represents a surface light source and stores position and color and shape.
struct PlaneLight
{
    Light(std::istream &is) { is >> center_position >> normal >> size >> color; }
    
    /// position of the center of the plane light source
    vec3 center_position;
    
    /// normal of the plane light
    vec3 normal;
    
    /// size of a side of the plane light
    double size;
    
    /// color of the light source
    vec3 color;
};


//-----------------------------------------------------------------------------


/// read light data from stream
inline std::istream& operator>>(std::istream& is, Light& l)
{
    l = Light(is);
    return is;
}


//=============================================================================
#endif // LIGHT_H defined
//=============================================================================
