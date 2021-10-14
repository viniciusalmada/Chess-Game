#pragma once
#include <array>

class GlUtils
{
  static std::array<float, 3> getColorsF(int hexColors);

public:
  static void uglClearColor(int hexColors);

  static void uglColor3d(int hexColors);
};