#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <vector>

#include "common.hpp"
#include  "scene_object.hpp"

namespace cg
{

class Sphere: public SceneObject
{
private:
  double _radius;
  point3_t _center;
public:
  Sphere(double radius, point3_t center, Color color) : _radius(radius), _center(center) {
    _color = color;
  }
  std::vector<double> IntersectRay(point3_t O, point3_t D, double t_min, double t_max) {
    double r = _radius;
    point3_t CO = O;
    boost::geometry::subtract_point(CO, _center);

    double a = boost::geometry::dot_product(D, D);
    double b = 2.0 * boost::geometry::dot_product(CO, D);
    double c = boost::geometry::dot_product(CO, CO) - (r * r);

    std::vector<double> result;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
      double inf = std::numeric_limits<double>::max();
      result = {inf, inf};
    }

    double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    result = {t1, t2};
    return result;
  }
};

} // namespace cg

#endif // #ifndef SPHERE_HPP