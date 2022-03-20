#include "trace_ray.hpp"

namespace cg
{

Color TraceRay(std::vector<SceneObject *>& objects, TraceRayContext& ctx)
{
  double closest_t = std::numeric_limits<double>::max(); 
  SceneObject *closest_object = nullptr;

  for (SceneObject * object : objects) {
    std::vector<double>t1t2 = object->IntersectRay(ctx.O, ctx.D, ctx.t_min, ctx.t_max);
    double t1 = t1t2[0];
    double t2 = t1t2[0];
    if (t1 >= ctx.t_min && t1 <= ctx.t_max && t1 < closest_t) {
      closest_t = t1;
      closest_object = object;
    }
    if (t2 >= ctx.t_min && t2 <= ctx.t_max && t2 < closest_t) {
      closest_t = t2;
      closest_object = object;
    }
  }
  if(closest_object == nullptr) {
    return ctx.backgroundColor;
  }
  return closest_object->getColor();
}

} // namespace cg