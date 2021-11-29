#include <color.h>
#include <numeric_utils.h>

Color::Color(Byte r, Byte g, Byte b, Byte a) : red(r), green(g), blue(b), alpha(a)
{
}

std::array<float, 4> Color::getColorsNormalized() const
{
  float r = red / (float)0xFF;
  float g = green / (float)0xFF;
  float b = blue / (float)0xFF;
  float a = alpha / (float)0xFF;
  return { r, g, b, a };
}
