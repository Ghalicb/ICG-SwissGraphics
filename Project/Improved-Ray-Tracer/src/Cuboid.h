#ifndef CUBOID_H
#define CUBOID_H

#include "Object.h"
#include "Plane.h"
#include "vec3.h"

#include <array>
#include <math.h>

#define PI 3.14159265

class Cuboid : public Object
{
public:
  Cuboid(const vec3 &_center=vec3(0,0,0),
              double _x_size=1,
              double _y_size=1,
              double _z_size=1,
              double _rotation_angle=0):center(_center),
                                        x_size(_x_size),
                                        y_size(_y_size),
                                        z_size(_z_size),
                                        rotation_angle(_rotation_angle){}

  Cuboid(std::istream &is) { parse(is); }

  virtual bool intersect(const Ray& _ray,
                              vec3& _intersection_point,
                              vec3& _intersection_normal,
                            double& _intersection_t) const override;

  virtual void parse(std::istream &is) override
  {
    is >> center >> x_size >> y_size >> z_size >> rotation_angle >> material;

    max_size = norm(vec3(x_size/2, y_size/2, z_size/2));

    double c = cos(rotation_angle * PI / 180.0);
    double s = sin(rotation_angle * PI / 180.0);

    x_axis = vec3( c,0,s);
    y_axis = vec3( 0,1,0);
    z_axis = vec3(-s,0,c);

    faces[0] = Plane(center + x_axis*x_size/2,  x_axis);
    faces[1] = Plane(center - x_axis*x_size/2, -x_axis);
    faces[2] = Plane(center + y_axis*y_size/2,  y_axis);
    faces[3] = Plane(center - y_axis*y_size/2, -y_axis);
    faces[4] = Plane(center + z_axis*z_size/2,  z_axis);
    faces[5] = Plane(center - z_axis*z_size/2, -z_axis);
  }

private:
  vec3 center;

  double x_size;
  double y_size;
  double z_size;

  vec3 x_axis;
  vec3 y_axis;
  vec3 z_axis;

  double rotation_angle;

  double max_size;

  std::array<Plane, 6> faces;
};

#endif
