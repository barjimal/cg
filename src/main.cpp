#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <boost/geometry.hpp>

#include "canvas.hpp"
#include "color.hpp"
#include "common.hpp"
#include "scene_object.hpp"
#include "sphere.hpp"
#include "trace_ray.hpp"
#include "viewport.hpp"

int main ()
{
  using namespace cg;
  namespace bg = boost::geometry;

  Sphere * sphere1 = new Sphere(
    1,
    point3_t(0.0, -1.0, 3.0),
    Color(255, 0, 0)
  );
  Sphere * sphere2 = new Sphere(
    1,
    point3_t(2.0, 0.0, 4.0),
    Color(0, 0, 255)
  );
  Sphere * sphere3 = new Sphere(
    1,
    point3_t(-2.0, 0.0, 4.0),
    Color(0, 255, 0)
  );

  Canvas canvas (1200, 1200);
  Viewport viewport;
  double Cw = canvas.GetWidth();
  double Ch = canvas.GetHeight();

  std::vector<SceneObject *>sceneObjects = {sphere1, sphere2, sphere3};

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

  sceneObjects = {};
  delete sphere1;
  delete sphere2;
  delete sphere3;
  
  // testCanvas();
  return 0;
}
