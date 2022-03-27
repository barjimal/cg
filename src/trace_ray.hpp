#ifndef TRACE_RAY_HPP
#define TRACE_RAY_HPP

#include <limits>

#include "common.hpp"
#include "color.hpp"
#include "scene_object.hpp"
#include "scene_light.hpp"

namespace cg
{

struct TraceRayContext
{
  point3_t O;
  point3_t D;
  double t_min = 1;
  double t_max = std::numeric_limits<double>::max();
  Color backgroundColor;
  int recursion_depth = 3;
};

Color TraceRay(
    std::vector<SceneObject *>& objects, 
    std::vector<SceneLight *>sceneLights,
    TraceRayContext& ctx,
    int recursion_depth
    );

} // namespace cg

#endif // #ifndef TRACE_RAY_HPP