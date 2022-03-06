#include "canvas.hpp"

#include <iostream>

#include <bmp/libbmp.h>

namespace cg
{

const std::string bmp_path = "bmp-out/";

long long int Canvas::GetIndex(const cp_int& x, const cp_int& y)
{
  return (_size_x * y) + x;
}

Canvas::Canvas(const cp_int& size_x, const cp_int& size_y) : _size_x(size_x), _size_y(size_y)
{
  _data = new CanvasPixel[size_x * size_y];
}

Canvas::~Canvas()
{
  delete[] _data;
}

void Canvas::SaveToBitmap(std::string fileName)
{
  std::string path = bmp_path + fileName;

  BmpImg img (_size_x, _size_y);
  for (int y = _size_y - 1, x; y >= 0; y--)
  {
    for (x = _size_x - 1; x >= 0; x--)
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
  (_data[GetIndex(x, y)])._r = r;
  (_data[GetIndex(x, y)])._g = g;
  (_data[GetIndex(x, y)])._b = b;
}

} // namespace cg
