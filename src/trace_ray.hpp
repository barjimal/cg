#ifndef TRACE_RAY_HPP
#define TRACE_RAY_HPP

#include "common.hpp"
#include "color.hpp"
#include "scene_object.hpp"

namespace cg
{

struct TraceRayContext
{
  point3_t O;
  point3_t D;
  double t_min = 1;
  double t_max = std::numeric_limits<double>::max();
  Color backgroundColor;
};

Color TraceRay(std::vector<SceneObject *>& objects, TraceRayContext& ctx);

} // namespace cg

#endif // #ifndef TRACE_RAY_HPP