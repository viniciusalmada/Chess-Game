#pragma once
#include <GL/glew.h>
#include "gl_utils.h"
#include "numeric_utils.h"

std::array<float, 3> GlUtils::getColorsF(int hexColors)
{
  auto rgb = NumericUtils::hexToDecColors(hexColors);

  float r = rgb[0] / (float)0xFF;
  float g = rgb[1] / (float)0xFF;
  float b = rgb[2] / (float)0xFF;
  return { r, g, b };
}

void GlUtils::uglClearColor(int hexColors)
{
  auto rgb = getColorsF(hexColors);

  glClearColor(rgb[0], rgb[1], rgb[2], 1.0f);
}

void GlUtils::uglColor3d(int hexColors)
{
  auto rgb = getColorsF(hexColors);

  glColor3d(rgb[0], rgb[1], rgb[2]);
}
