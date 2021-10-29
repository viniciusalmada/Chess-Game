#include "numeric_utils.h"

std::array<int, 3> NumericUtils::hexTo3Dec(int hexColor)
{
  if (hexColor > 0xFFFFFF)
    return { 0xFF, 0xFF, 0xFF };

  if (hexColor < 0x000000)
    return { 0x00, 0x00, 0x00 };

  int b = hexColor % 0x100;
  int g = (hexColor - b) / 0x100 % 0x100;
  int r = (hexColor - (g * 0x100 + b)) / 0x10000;

  return { r, g, b };
}
std::array<int, 4> NumericUtils::hexTo4Dec(unsigned long hexColor)
{
  if (hexColor > 0xFFFFFFFF)
    return { 0xFF, 0xFF, 0xFF, 0xFF };

  int b = hexColor % 0x100;
  int g = (hexColor - b) / 0x100 % 0x100;
  int r = ((hexColor - (g * 0x100 + b)) / 0x10000) % 0x100;
  int a = (hexColor - (r * 0x1000 + g * 0x100 + b)) / 0x1000000;

  return { r, g, b, a };
}
