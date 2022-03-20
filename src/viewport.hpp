#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "common.hpp"

namespace cg
{

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

} // namespace cg

#endif // #ifndef VIEWPORT_HPP