#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H

#include "Object.h"
#include "Plane.h"
#include "vec3.h"

#define BLOCK_SIDE 5

class AreaLight : public Object
{
public:
  AreaLight(const vec3 &_center=vec3(0,0,0),
            const vec3 &_color=vec3(0,0,0),
                    int _x_size=0,
                    int _y_size=0):center(_center),
                                   color(_color),
                                   x_size(_x_size),
                                   y_size(_y_size){}

  AreaLight(std::istream &is) { parse(is); }

  virtual bool intersect(const Ray& _ray,
                              vec3& _intersection_point,
                              vec3& _intersection_normal,
                            double& _intersection_t) const override;


  virtual void parse(std::istream &is) override
  {
    is >> center >> color >> x_size >> y_size;

    x_size = BLOCK_SIDE*x_size;
    y_size = BLOCK_SIDE*y_size;

    x_axis    = vec3(1,0, 0);
    y_axis    = vec3(0,1, 0);
    direction = vec3(0,0,-1);

    plane = Plane(center, direction);
  }

private:
  vec3 center;
  vec3 color;

  int x_size;
  int y_size;

  vec3 x_axis;
  vec3 y_axis;
  vec3 direction;

  Plane plane;
};

#endif
