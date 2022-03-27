#include "trace_ray.hpp"

#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>

namespace cg
{

point3_t ComputeL(SceneLight *light, point3_t P)
{
  point3_t L;
  auto* pointLight = dynamic_cast<PointLight *>(light);
  if (pointLight) {
      L = pointLight->position;
      boost::geometry::subtract_point(L, P);
  } 
  auto* directionalLight = dynamic_cast<DirectionalLight *>(light);
  if (directionalLight) {
      L = directionalLight->direction;
  }
  return L;
}

double ComputeDiffuseIntensity(
  SceneLight *light,
  point3_t N,
  point3_t L
  )
{
  double i = 0.0;
  double n_dot_l =  boost::geometry::dot_product(N, L);
  if (n_dot_l > 0) {
    double length_N = std::sqrt(boost::geometry::dot_product(N, N));
    double length_L = std::sqrt(boost::geometry::dot_product(L, L));
    i = light->intensity * (n_dot_l / (length_N * length_L)); 
  } 
  return i;
}

double ComputeSpecularIntensity(
  SceneLight *light,
  point3_t N, // normal
  point3_t L, // light
  point3_t V, // view
  int s
)
{
  double i = 0.0;
  if (s >= 0) {
    point3_t R = N;
    double n_dot_l = boost::geometry::dot_product(N, L); // normal and light
    boost::geometry::multiply_value(R, 2 * n_dot_l);
    boost::geometry::subtract_point(R, L); // reflection = 2 * normal * (normal cross light) minus light 
    double r_dot_v = boost::geometry::dot_product(R, V); 

    if (r_dot_v > 0)
    {
      double length_R = std::sqrt(boost::geometry::dot_product(R, R));
      double length_V = std::sqrt(boost::geometry::dot_product(V, V));
      double temp = r_dot_v / (length_R * length_V);
      i = light->intensity * std::pow(temp,s);
    }
  }
  return i;
}

SceneObject *ComputeClosestIntersection(
  std::vector<SceneObject *>& objects,
  double& closest_t,
  point3_t O,
  point3_t D,
  double t_min,
  double t_max
)
{
  closest_t = std::numeric_limits<double>::max();
  SceneObject *closest_object = nullptr;

  for (SceneObject * object : objects) {
    std::vector<double>t1t2 = object->IntersectRay(O, D, t_min, t_max);
    double t1 = t1t2[0];
    double t2 = t1t2[1];
    if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
      closest_t = t1;
      closest_object = object;
    }
    if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
      closest_t = t2;
      closest_object = object;
    }
  }
  
  return closest_object;
}

Color FixColor(const Color& color) {
  Color fixed_color;
  fixed_color.r = color.r < 255 ? color.r : 255;
  fixed_color.g = color.g < 255 ? color.g : 255;
  fixed_color.b = color.b < 255 ? color.b : 255;
  return fixed_color;
}

double ComputeLighting(
    std::vector<SceneObject *>& objects,
    point3_t P,
    point3_t N,
    point3_t V,
    std::vector<SceneLight *>sceneLights,
    int s
)
{
    double i = 0.0;
    for(SceneLight * light : sceneLights) {
        auto* ambientLight = dynamic_cast<AmbientLight *>(light);
        if (ambientLight) {
            i += ambientLight->intensity;
            continue;
        }

        point3_t L = ComputeL(light, P);

        double shadow_t;
        
        SceneObject *shadow_object = 
          ComputeClosestIntersection(objects, shadow_t, P, L, 0.001, std::numeric_limits<double>::max());
        
        if (shadow_object != nullptr) { continue; }

        i += ComputeDiffuseIntensity(light, N, L); 
        i += ComputeSpecularIntensity(light, N, L, V, s);
    }

    return i;
}

SceneObject *ComputeClosestObject(
  std::vector<SceneObject *>& objects, 
  double& closest_t,
  TraceRayContext& ctx
)
{
  return ComputeClosestIntersection(objects, closest_t, ctx.O, ctx.D, ctx.t_min, ctx.t_max);
}

point3_t ReflectRay(point3_t R, point3_t N) 
{
  point3_t res = N;
  boost::geometry::multiply_value(res, 2);
  double n_dot_r = boost::geometry::dot_product(N, R);
  boost::geometry::multiply_value(res, n_dot_r);
  boost::geometry::subtract_point(res, R);
  return res;
}

Color TraceRay(
  std::vector<SceneObject *>& objects, 
  std::vector<SceneLight *>sceneLights,
  TraceRayContext& ctx,
  int recursion_depth)
{
  double closest_t; 
  SceneObject *closest_object = ComputeClosestObject(objects, closest_t, ctx);

  if(closest_object == nullptr) {
    return ctx.backgroundColor;
  }

  point3_t P = ctx.D;
  boost::geometry::multiply_value(P, closest_t);
  boost::geometry::add_point(P, ctx.O);
  point3_t N = closest_object->getNormal(ctx.O, ctx.D, P);
  point3_t V = ctx.D;
  boost::geometry::multiply_value(V, -1); 
  double i = ComputeLighting(objects, P, N, V, sceneLights, closest_object->getSpecular());

  Color local_color = closest_object->getColor();
  local_color.r = local_color.r * i;
  local_color.g = local_color.g * i;
  local_color.b = local_color.b * i;

  local_color = FixColor(local_color);

  double r = closest_object->getReflective();
  if (recursion_depth <= 0 || r <= 0.0) {
    return local_color;
  }

  point3_t minus_D = ctx.D;
  boost::geometry::multiply_value(minus_D, -1); 
  point3_t R = ReflectRay(minus_D, N);

  TraceRayContext ctx_r = ctx;
  ctx_r.t_min = 0.001;
  ctx_r.O = P;
  ctx_r.D = R;
  Color reflected_color = TraceRay(objects, sceneLights, ctx_r, recursion_depth - 1);

  local_color.r = (local_color.r * (1 - r)) + (reflected_color.r * r);
  local_color.g = (local_color.g * (1 - r)) + (reflected_color.g * r);
  local_color.b = (local_color.b * (1 - r)) + (reflected_color.b * r);

  local_color = FixColor(local_color);

  return local_color;
}

} // namespace cg