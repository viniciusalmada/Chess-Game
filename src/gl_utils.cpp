//#include <gl_headers.h>
//#include "gl_utils.h"
//#include "numeric_utils.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//
//GlUtils::Color GlUtils::RED = { 0xFF0000 };
//GlUtils::Color GlUtils::WHITE = { 0xFFFFFF };
//
//static void _genBuffers(unsigned int& id)
//{
//  if (id == 0)
//  {
//    glGenBuffers(1, &id);
//    if (id == 0)
//    {
//      throw std::runtime_error("Error generating vertex buffer");
//    }
//  }
//}
//
//std::array<float, 4> GlUtils::Color::getColorsF()
//{
//  auto rgb = NumericUtils::hexTo3Dec(hexColor);
//
//  float r = rgb[0] / (float)0xFF;
//  float g = rgb[1] / (float)0xFF;
//  float b = rgb[2] / (float)0xFF;
//  float a = alpha / (float)0xFF;
//  return { r, g, b, a };
//}
//
//void GlUtils::uglClearColor(Color color)
//{
//  auto rgb = color.getColorsF();
//
//  glClearColor(rgb[0], rgb[1], rgb[2], rgb[3]);
//}
//
//void GlUtils::uglColor3f(Color color)
//{
//  auto rgb = color.getColorsF();
//
//  glColor3f(rgb[0], rgb[1], rgb[2]);
//}
//
//void GlUtils::uglColor4f(Color color)
//{
//  auto rgba = color.getColorsF();
//
//  glColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);
//}
//
//void GlUtils::uglViewportAndOrtho(int s)
//{
//  glViewport(0, 0, s, s);
//  glLoadIdentity();
//  glOrtho(0, s, s, 0, -1.0, 1.0);
//}
//
//void GlUtils::drawSquare(int x, int y, int squareSize)
//{
//  glBegin(GL_QUADS);
//  glVertex2i(x, y);
//  glVertex2i(x + squareSize, y);
//  glVertex2i(x + squareSize, y + squareSize);
//  glVertex2i(x, y + squareSize);
//  glEnd();
//}
//
//void GlUtils::draw2DTexture(int texId, int x, int y, int sq, GlUtils::Color color)
//{
//  //glBindTexture(GL_TEXTURE_2D, 0);
//  glEnable(GL_TEXTURE_2D);
//  glBindTexture(GL_TEXTURE_2D, texId);
//  GlUtils::uglColor4f(color);
//  glBegin(GL_QUADS);
//  // top-right
//  glTexCoord2f(0.0f, 1.0f); glVertex2i(x, y);
//  // top-left
//  glTexCoord2f(1.0f, 1.0f); glVertex2i(x + sq, y);
//  // bottom-left
//  glTexCoord2f(1.0f, 0.0f); glVertex2i(x + sq, y + sq);
//  // bottom-right
//  glTexCoord2f(0.0f, 0.0f); glVertex2i(x, y + sq);
//  glEnd();
//  glDisable(GL_TEXTURE_2D);
//}
//
//void GlUtils::drawElements(int totalIndices)
//{
//  glDrawElements(GL_TRIANGLES, totalIndices, GL_UNSIGNED_INT, nullptr);
//}
