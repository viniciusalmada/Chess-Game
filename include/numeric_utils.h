#pragma once
#include <array>

class NumericUtils
{
public:
  static std::array<int, 3> hexTo3Dec(int hexColor);
  static std::array<int, 4> hexTo4Dec(unsigned long hexColor);
};
