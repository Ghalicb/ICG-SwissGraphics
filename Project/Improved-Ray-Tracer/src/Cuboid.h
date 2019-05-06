#ifndef CUBOID_H
#define CUBOID_H

#include "Object.h"
#include "vec3.h"

class Cuboid : public Object
{
public:
  Cuboid(const vec3 &_center = vec3(0,0,0),
         const vec3 &_x_axis = vec3(1,0,0),
         const vec3 &_y_axis = vec3(0,1,0),
              double _x_size = 1,
              double _y_size = 1,
              double _z_size = 1): center(_center), x_axis(_x_axis), y_axis(_y_axis),
                                   x_size(_x_size), y_size(_y_size), z_size(_z_size)
  {
    z_axis = normalize(cross(x_axis, y_axis));

    faces.emplace_back{center + x_size/2,  x_axis};
    faces.emplace_back{center - x_size/2, -x_axis};
    faces.emplace_back{center + y_size/2,  y_axis};
    faces.emplace_back{center - y_size/2, -y_axis};
    faces.emplace_back{center + z_size/2,  z_axis};
    faces.emplace_back{center - z_size/2, -z_axis};
  }

  Cuboid(std::istream &is) { parse(is); }

  virtual bool intersect(const Ray& _ray,
                              vec3& _intersection_point,
                              vec3& _intersection_normal,
                            double& _intersection_t) const override;

  virtual void parse(std::istream &is) override
  {
    is >> center >> x_axis >> y_axis >> x_size >> y_size >> z_size >> material;
    x_axis = normalize(x_axis);
    y_axis = normalize(y_axis);
  }

private:
  vec3 center;

  vec3 x_axis;
  vec3 y_axis;
  vec3 z_axis;

  double x_size;
  double y_size;
  double z_size;

  std::vector<Plane> faces;
};

#endif
