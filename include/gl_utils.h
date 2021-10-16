#pragma once
#include <array>
#include <im/im.h>
#include <im/im_image.h>

class GlUtils
{
  static std::array<float, 3> getColorsF(int hexColors);

public:
  static int RED;
  static int WHITE;

  static void uglClearColor(int hexColors);

  static void uglColor3d(int hexColors);

  static int createTexture2D(imImage* im);
};