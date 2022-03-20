#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

namespace cg
{

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

} // namespace cg

#endif // #ifndef COLOR_HPP