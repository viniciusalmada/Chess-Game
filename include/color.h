#pragma once
#include <array>

class Color
{
  using Byte = unsigned __int8;
private:
  Byte red;
  Byte green;
  Byte blue;
  Byte alpha;
public:
  Color(Byte r, Byte g, Byte b, Byte a = 0xFF);

  std::array<float, 4> getColorsNormalized() const;
};