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
public:
  virtual Color getColor() { return _color; }
  virtual std::vector<double> IntersectRay(point3_t O, point3_t D, double t_min, double t_max) = 0;
};

} // namespace cg

#endif // #ifndef SCENE_OBJECT_HPP