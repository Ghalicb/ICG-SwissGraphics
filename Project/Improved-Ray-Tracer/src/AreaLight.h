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
                   int _x_parts=1,
                   int _y_parts=1):center(_center),
                                  color(_color),
                                  x_parts(_x_parts),
                                  y_parts(_y_parts)

  {
    x_size = BLOCK_SIDE*x_parts;
    y_size = BLOCK_SIDE*y_parts;

    x_axis    = vec3(1,0,0);
    y_axis    = vec3(0,0,1);
    direction = vec3(0,1,0);

    top_left  = center;
    vec3 temp = x_size/2 * x_axis;
    top_left -= temp;
    temp      = y_size/2 * y_axis;
    top_left -= temp;

    plane = Plane(center, direction);

    std::cout << center << top_left;
  }

  AreaLight(std::istream &is) { parse(is); }

  virtual bool intersect(const Ray& _ray,
                              vec3& _intersection_point,
                              vec3& _intersection_normal,
                            double& _intersection_t) const override;


  virtual void parse(std::istream &is) override
  {
    is >> center >> color >> x_parts >> y_parts;

    x_size = BLOCK_SIDE*x_parts;
    y_size = BLOCK_SIDE*y_parts;

    x_axis    = vec3(1,0,0);
    y_axis    = vec3(0,0,1);
    direction = vec3(0,1,0);

    top_left  = center;
    vec3 temp = x_size/2 * x_axis;
    top_left -= temp;
    temp      = y_size/2 * y_axis;
    top_left -= temp;

    plane = Plane(center, direction);

    std::cout << center << top_left;
  }

  virtual bool isLight() override { return true; }

  const vec3 getColor() const { return color; }

private:
  vec3 center;
  vec3 color;

  int x_parts;
  int y_parts;

  int x_size;
  int y_size;

  vec3 x_axis;
  vec3 y_axis;
  vec3 direction;

  vec3 top_left;

  Plane plane;
};

#endif
