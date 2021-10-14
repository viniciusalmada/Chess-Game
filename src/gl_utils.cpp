#pragma once
#include <GL/glew.h>
#include "gl_utils.h"
#include "numeric_utils.h"

void GlUtils::uglClearColor(int hexColor)
{
  auto rgb = NumericUtils::hexToDecColors(hexColor);

  float r = rgb[0] / (float)0xFF;
  float g = rgb[1] / (float)0xFF;
  float b = rgb[2] / (float)0xFF;

  glClearColor(r, g, b, 1.0f);
}