#include <color.h>
#include <numeric_utils.h>

Color::Color() : red(0x00), green(0x00), blue(0x00), alpha(0x00)
{
}

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

int Color::getBytesCount() const
{
  return sizeof(float) * 4;
}