#ifndef SCENE_OBJECT_HPP
#define SCENE_OBJECT_HPP

#include "common.hpp"
#include "color.hpp"

namespace cg
{

class SceneObject
{
protected:
  Color _color = Color(0,0,0);
  int _specular = -1;
  double _reflective = 0.0;
public:
  int getSpecular() { return _specular; }
  double getReflective() { return _reflective; }
  virtual Color getColor() { return _color; }
  virtual point3_t getNormal(point3_t O, point3_t D, point3_t P) = 0;
  virtual std::vector<double> IntersectRay(point3_t O, point3_t D, double t_min, double t_max) = 0;
  virtual ~SceneObject() {};
};

} // namespace cg

#endif // #ifndef SCENE_OBJECT_HPP