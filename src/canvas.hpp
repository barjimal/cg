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
public:
  const cp_int _size_x;
  const cp_int _size_y;

  Canvas(const cp_int& size_x = 1280 , const cp_int& size_y = 720); 
  ~Canvas();
  void SaveToBitmap(std::string fileName = "test.bmp");
  void SetPixelColor(
    const cp_int& x = 0,
    const cp_int& y = 0,
    const int& r = 0,
    const int& g = 0,
    const int& b = 0);
  long long int GetIndex(const cp_int& x, const cp_int& y);
 };

} // namespace cg

#endif  // CANVAS_HPP

