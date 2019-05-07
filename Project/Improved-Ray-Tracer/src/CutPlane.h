//
//  CutPlane.h
//  raytrace
//
//  Created by Samuel Chassot on 07.05.19.
//

#include "Object.h"
#include "vec3.h"
#include "Plane.h"
//== CLASS DEFINITION =========================================================


/// \class CutPlane CutPlane.h
/// This class implements a plane object with a cut-out around its center.
/// A cutplane is specified by a center point, a normal vector and the cut-out radius.
/// This class overrides the intersection method Object::intersect().
class CutPlane : public Object
{
public:
    /// constructor
    CutPlane(const vec3& _center=vec3(0,0,0), const vec3& _normal=vec3(0,1,0), const double _hole_radius=0.0);

    /// Construct a plane with parameters parsed from an input stream.
    CutPlane(std::istream &is) { parse(is); }

    /// Compute the intersection of the plane light with \c _ray. Return whether
    /// there is an intersection. If there is one, return the intersection data.
    /// This function overrides Object::intersect().
    /// \param[in] _ray the ray to intersect the planeLight with
    /// \param[out] _intersection_point position of the intersection
    /// \param[out] _intersection_normal normal vector at the intersection point
    /// \param[out] _intersection_t ray parameter at the intesection point
    virtual bool intersect(const Ray&  _ray,
                           vec3&       _intersection_point,
                           vec3&       _intersection_normal,
                           double&     _intersection_t) const override;

    /// parse plane light from an input stream
    virtual void parse(std::istream &is) override {
        is >> center >> normal >> hole_radius >> material;
        normal = normalize(normal);
        plane = new Plane(center, normal);
    }

private:
  /// center point on the plane
  vec3 center;
  /// normal vector of the plane
  vec3 normal;
  /// cut-out radius
  double hole_radius;
  /// plane object without the cut-out
  Plane* plane;
};
