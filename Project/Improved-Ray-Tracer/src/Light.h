#ifndef LIGHT_H
#define LIGHT_H

#include "Object.h"

class Light : public Object {

    public:
        Light(const vec3 &_center=vec3(0,0,0), const vec3 &_color=vec3(0,0,0))
        : center(_center), color(_color)
        {}

        virtual ~Light() {}

        virtual bool isLight() override { return true; }
        virtual bool isSpotlight()      { return false; }

        vec3 getColor() { return color; }

        virtual vec3   getLightPosition(int light_index) const { return center; }
        virtual vec3   getLightIntensity() const { return color / getNumberOfLights(); }
        virtual vec3   getDirection()      const { return vec3(0); }
        virtual int    getNumberOfLights() const { return 1; }
        virtual double getSurface       () const { return 0.0; };
        virtual double getAperture      () const { return 0.0; };

    protected:
        vec3 center;
        vec3 color;
};


#endif
