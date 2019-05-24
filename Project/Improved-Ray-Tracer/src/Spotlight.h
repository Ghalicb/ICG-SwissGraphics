#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"
#include "vec3.h"
#include "Plane.h"

#define APERTURE 0.98

class Spotlight : public Light
{
public:
  Spotlight(const vec3 &_center   =vec3(0),
            const vec3 &_color    =vec3(0),
            const vec3 &_direction=vec3(0,1,0),
                 double _radius   =0,
                 double _angle    =0):Light(_center, _color),
                                      direction(_direction),
                                      radius(_radius)
  {
    if (radius <= 0)
    {
      radius = 0;
    }

    direction = normalize(direction);
  }

  Spotlight(std::istream &is) { parse(is); }

  virtual bool intersect(const Ray& _ray,
                              vec3& _intersection_point,
                              vec3& _intersection_normal,
                            double& _intersection_t) const override;

  virtual void parse(std::istream &is) override
  {
    is >> center >> color >> direction >> radius;
    direction = normalize(direction);

    plane = Plane(center, direction);
  }

  bool   isSpotlight()                           override { return true; }
  double getAperture()                     const override { return APERTURE; }
  vec3   getLightPosition(int light_index) const override;
  double getSurface()                      const override;

private:
  vec3   direction;
  double radius;

  Plane plane;
};

#endif
