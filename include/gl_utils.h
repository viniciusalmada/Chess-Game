#pragma once
#include <array>
#include <im/im.h>
#include <im/im_image.h>

class GlUtils
{
  static std::array<float, 3> getColorsF(int hexColors);

public:

  struct Texture
  {
    int width;
    int height;
    unsigned int id;
  };

  static int RED;
  static int WHITE;

  static void uglClearColor(int hexColors);

  static void uglColor3d(int hexColors);

  static Texture createTexture2D(imImage* im);

  static void uglViewportAndOrtho(int size);

  static void drawSquare(int x, int y, int squareSize);
};