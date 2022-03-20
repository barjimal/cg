#include "scene.hpp"

namespace cg
{

Scene::Scene()
{
    canvas = Canvas(1200, 1200);
    viewport = Viewport();
}

void Scene::RenderScene()
{
  double Cw = canvas.GetWidth();
  double Ch = canvas.GetHeight();
  point3_t O(0, 0, 0);
  for (int x = -(int)Cw/2; x < (int)Cw/2; x++){
    for (int y = -(int)Ch/2; y < (int)Ch/2; y++){
      point3_t D = CanvasToViewPort(canvas, viewport, x, y);
      TraceRayContext ctx {
        .O = O,
        .D = D,
        .backgroundColor = Color(200, 200, 200),
      };
      Color color = TraceRay(sceneObjects, ctx);
      canvas.SetPixelColor(x, y, color.r, color.g, color.b);
    }
  }
  canvas.SaveToBitmap();
}

Scene::~Scene() {
    for (auto o : sceneObjects) {
        delete o;
    }
}

} //namespace cg
