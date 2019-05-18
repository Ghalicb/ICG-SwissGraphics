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

        vec3 getColor() { return color; }

        virtual vec3 getLightIntensity() const = 0;

        int getNumberOfLights() const = 0;


    protected:
        vec3 center;
        vec3 color;
};


#endif
