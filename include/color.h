#pragma once
#include <array>
#include "countable.h"

class Color : public Countable
{
  using Byte = unsigned __int8;
private:
  Byte red;
  Byte green;
  Byte blue;
  Byte alpha;
public:
  Color();

  Color(Byte r, Byte g, Byte b, Byte a = 0xFF);

  std::array<float, 4> getColorsNormalized() const;

  int getBytesCount() const override;

  float redF() const { return red / (float)0xFF; };
  float greenF() const { return green / (float)0xFF; };
  float blueF() const { return blue / (float)0xFF; };
  float alphaF() const { return alpha / (float)0xFF; };
};