#include "canvas.hpp"

#include <vector>

#include "canvas.hpp"
#include "color.hpp"
#include "common.hpp"
#include "scene_object.hpp"
#include "sphere.hpp"
#include "trace_ray.hpp"
#include "viewport.hpp"

namespace cg
{

class Scene
{
public:
  Canvas canvas;
  Viewport viewport;
  TraceRayContext context;
  std::vector<SceneObject *> sceneObjects;
  std::vector<SceneLight *>sceneLights;

  Scene();
  ~Scene();

  void RenderScene();
};

} //namespace cg
