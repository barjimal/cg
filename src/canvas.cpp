#include "canvas.hpp"

#include <iostream>
#include <cmath>

#include <bmp/libbmp.h>

namespace cg
{

const std::string bmp_path = "bmp-out/";

long long int Canvas::GetIndex(const cp_int& x, const cp_int& y)
{
  return (_width * y) + x;
}

Canvas::Canvas(const cp_int& width, const cp_int& height) : _width(width), _height(height)
{
  _data = new CanvasPixel[width * _height];
  _origin_x = - cp_int(std::floor(_width / 2.0));
  _origin_y = cp_int(std::floor(_height / 2.0));
}

Canvas::~Canvas()
{
  delete[] _data;
}

void Canvas::SaveToBitmap(std::string fileName)
{
  std::string path = bmp_path + fileName;

  BmpImg img (_width, _height);
  for (int y = _height - 1, x; y >= 0; y--)
  {
    for (x = _width - 1; x >= 0; x--)
    {
      CanvasPixel pixel = _data[GetIndex(x,y)];
      img.set_pixel (x, y, pixel._r, pixel._g, pixel._b);
    }
  }

  img.write (path);
  std::cout << path << std::endl;
}

void Canvas::SetPixelColor(
  const cp_int& x,
  const cp_int& y,
  const int& r,
  const int& g,
  const int& b) {

  cp_int _x = x - _origin_x;
  cp_int _y = _origin_y - y;
  if (_x < 0 || _x >= _width) return;
  if (_y < 0 || _y >= _height) return;

  (_data[GetIndex(_x, _y)])._r = r;
  (_data[GetIndex(_x, _y)])._g = g;
  (_data[GetIndex(_x, _y)])._b = b;
}

cp_int Canvas::GetWidth()
{
  return _width;
}

cp_int Canvas::GetHeight()
{
  return _height;
}

point3_t CanvasToViewPort(Canvas& canvas, Viewport& viewport, int x, int y)
{
  double Cw = canvas.GetWidth();
  double Ch = canvas.GetHeight();
  double Vw = viewport.GetWidth();
  double Vh = viewport.GetHeight();
  double d = viewport.GetDistance();
  return point3_t(x*Vw/Cw, y*Vh/Ch, d);
}


} // namespace cg
