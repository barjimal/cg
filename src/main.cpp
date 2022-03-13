#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <boost/geometry.hpp>

#include "canvas.hpp"

using namespace cg;
namespace bg = boost::geometry;

void testCanvas()
{

  typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
  typedef bg::model::box<point_t> box_t;

  point_t point3;
  point3.set<0>(-100.0); 
  point3.set<1>(-100.0);

  point_t point4;
  point4.set<0>(100.0); 
  point4.set<1>(100.0);

  box_t box1(point3, point4);

  Canvas canvas;
  for (int y = canvas.GetHeight() - 1, x; y >= - canvas.GetHeight(); y--)
  {
    for (x = canvas.GetWidth() - 1; x >= - canvas.GetWidth(); x--)
    {
      canvas.SetPixelColor(x, y, 200,200,200);
      point_t cpt(x, y);
      if (bg::within(cpt, box1)) {
        canvas.SetPixelColor(x, y, 80,80,255);
      }
    }
  }
  
  canvas.SetPixelColor(0, 0, 0,255,0);
  
  canvas.SaveToBitmap();
}

typedef bg::model::point<double, 3, bg::cs::cartesian> point3_t;

struct Color
{
  int r;
  int g;
  int b;
  Color(int _r = 0, int _g = 0, int _b = 0): r(_r), g(_g), b(_b) {};
  std::string ToString() {
    std::string color = std::string("R:") + 
      std::to_string(r) +
      std::string("G:") +
      std::to_string(g) + 
      std::string("B:") + 
      std::to_string(b);
    return color;
  }  
};

class SceneObject
{
protected:
  Color _color = Color(0,0,0);
public:
  virtual Color getColor() { return _color; }
  virtual std::vector<double> IntersectRay(point3_t O, point3_t D, double t_min, double t_max) = 0;
};

class Sphere: public SceneObject
{
private:
  double _radius;
  point3_t _center;
public:
  Sphere(double radius, point3_t center, Color color) : _radius(radius), _center(center) {
    _color = color;
  }
  std::vector<double> IntersectRay(point3_t O, point3_t D, double t_min, double t_max) {
    double r = _radius;
    point3_t CO = O;
    bg::subtract_point(CO, _center);

    double a = bg::dot_product(D, D);
    double b = 2.0 * bg::dot_product(CO, D);
    double c = bg::dot_product(CO, CO) - (r * r);

    std::vector<double> result;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
      double inf = std::numeric_limits<double>::max();
      result = {inf, inf};
    }

    double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    result = {t1, t2};
    return result;
  }
};

class Viewport
{
private:
  double _width;
  double _height;
  double _distance;
public:
  Viewport(
      double width = 1, 
      double height = 1, 
      double distance = 1) :
    _width(width),
    _height(height),
    _distance(distance) {};
  double GetWidth() {return _width; }
  double GetHeight() {return _height; }
  double GetDistance() {return _distance; }
};

point3_t CanvasToViewPort(Canvas& canvas, Viewport& viewport, int x, int y)
{
  double Cw = canvas.GetWidth();
  double Ch = canvas.GetHeight();
  double Vw = viewport.GetWidth();
  double Vh = viewport.GetHeight();
  double d = viewport.GetDistance();
  return point3_t(x*Vw/Cw, y*Vh/Ch, d);
}

struct TraceRayContext
{
  point3_t O;
  point3_t D;
  double t_min = 1;
  double t_max = std::numeric_limits<double>::max();
  Color backgroundColor;
};

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

int main ()
{
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
  
  // testCanvas();
  return 0;
}
