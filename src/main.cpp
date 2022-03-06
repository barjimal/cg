#include <iostream>
#include <string>

#include <boost/geometry.hpp>

#include "canvas.hpp"

using namespace cg;
namespace bg = boost::geometry;

int main ()
{
  typedef bg::model::point<double, 2, bg::cs::cartesian> point_t;
  typedef bg::model::box<point_t> box_t;

  point_t point3;
  point3.set<0>(50.0); 
  point3.set<1>(100.0);

  point_t point4;
  point4.set<0>(250.0); 
  point4.set<1>(300.0);

  box_t box1(point3, point4);

  Canvas canvas;

  for (int y = canvas._size_y - 1, x; y >= 0; y--)
  {
    for (x = canvas._size_x - 1; x >= 0; x--)
    {
      canvas.SetPixelColor(x, y, 200,200,200);
      point_t cpt(x, y);
      if (bg::within(cpt, box1)) {
        canvas.SetPixelColor(x, y, 80,80,255);
      }
    }
  }
  
  canvas.SaveToBitmap();
  
  return 0;
}