#include "canvas.hpp"

namespace cg
{

class Camera
{
private:
  double _pos_x;
  double _pos_y;
  double _pos_z;
public:
  Camera(
      double pos_x = 0,
      double pos_y = 0,
      double pos_z = 0) :
    _pos_x(pos_x),
    _pos_y(pos_y),
    _pos_z(pos_z) {};
  double[3] O;
};

class Viewport
{
public:
  double _width;
  double _height;
  double _distance;
  Viewport(
      double width = 1, 
      double height = 1, 
      double distance = 1) :
    _width(width),
    _height(height),
    _distance(distance) {};
};

class SceneObject
{
public:
  virtual 
}

class Scene
{
private:
  Camera camera();
  Viewport viewport();
  Canvas canvas();
  double[3] CanvasToViewport(double[3] O, dobule[3] D, double t_min);
  void TraceRay();

public:
  void RenderScene();
};

} //namespace cg
