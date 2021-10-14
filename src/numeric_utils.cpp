#include "numeric_utils.h"

std::array<int, 3> NumericUtils::hexToDecColors(int hexColor)
{
  int b = hexColor % 0x100;
  int g = (hexColor - b) / 0x100 % 0x100;
  int r = (hexColor - (g * 0x100 + b)) / 0x10000;

  return { r, g, b };
}
