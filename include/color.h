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

  int getBytesCount() override;
};