#ifndef CANVAS_HPP

#define CANVAS_HPP

#include <string>

namespace cg
{

typedef long long int cp_int;

struct CanvasPixel
{
  int _r;
  int _g;
  int _b;
  CanvasPixel( 
    const int& r = 0,
    const int& g = 0,
    const int& b = 0
  ) : _r(r), _g(g), _b(b) {}
};

class Canvas
{
private:
  CanvasPixel * _data;
  cp_int _origin_x;
  cp_int _origin_y;
  const cp_int _width;
  const cp_int _height;

public:
  Canvas(const cp_int& width = 1920, const cp_int& height = 1080); 
  ~Canvas();
  void SaveToBitmap(std::string fileName = "test.bmp");
  void SetPixelColor(
    const cp_int& x = 0,
    const cp_int& y = 0,
    const int& r = 0,
    const int& g = 0,
    const int& b = 0);
  long long int GetIndex(const cp_int& x, const cp_int& y);
  cp_int GetWidth();
  cp_int GetHeight();
 };

} // namespace cg

#endif  // CANVAS_HPP

