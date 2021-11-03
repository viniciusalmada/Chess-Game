#include <GL/glew.h>
#include "gl_utils.h"
#include "numeric_utils.h"

Color GlUtils::RED = { 0xFF0000 };
Color GlUtils::WHITE = { 0xFFFFFF };

std::array<float, 4> Color::getColorsF()
{
  auto rgb = NumericUtils::hexTo3Dec(hexColor);

  float r = rgb[0] / (float)0xFF;
  float g = rgb[1] / (float)0xFF;
  float b = rgb[2] / (float)0xFF;
  float a = alpha / (float)0xFF;
  return { r, g, b, a };
}

void GlUtils::uglClearColor(Color color)
{
  auto rgb = color.getColorsF();

  glClearColor(rgb[0], rgb[1], rgb[2], rgb[3]);
}

void GlUtils::uglColor3f(Color color)
{
  auto rgb = color.getColorsF();

  glColor3f(rgb[0], rgb[1], rgb[2]);
}

void GlUtils::uglColor4f(Color color)
{
  auto rgba = color.getColorsF();

  glColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);
}

GlUtils::Texture GlUtils::createTexture2D(imImage* img)
{
  int data_type = 0;
  switch (img->data_type)
  {
  case IM_BYTE:
    data_type = GL_UNSIGNED_BYTE;
    break;
  case IM_FLOAT:
    data_type = GL_FLOAT;
    break;
  }

  /*
  * Get the data planes
  * --------------[imImage->data]------------
  * |RRR...RRR|GGG...GGG|BBB...BBB|AAA...AAA|
  * |   Red   |  Green  |   Blue  |  Alpha  |
  * |planesize|planesize|planesize|planesize|
  *
  * Each entry (R,G,B or A) of this data array has a single byte (unsigned char)
  * of color/alpha intensity varying from 0x00 to 0xFF	*/
  unsigned char* rplane = ((unsigned char**)(img->data))[0];
  unsigned char* gplane = ((unsigned char**)(img->data))[0] + 1 * (long long)img->plane_size;
  unsigned char* bplane = ((unsigned char**)(img->data))[0] + 2 * (long long)img->plane_size;
  unsigned char* aplane = ((unsigned char**)(img->data))[0] + 3 * (long long)img->plane_size;

  /*
  * To compound a OpenGL texture, the colors must be placed in following order:
  * |RGBA|RGBA|RGBA|....
  * | 1px| 1px| 1px|
  */
  int pixelsCount = img->width * img->height;

  unsigned char* imageBuffer = new unsigned char[(long long)pixelsCount * 4];

  unsigned char* bufferAuxPtr = imageBuffer;

  for (int i = 0; i < pixelsCount; i++)
  {
    bufferAuxPtr[0] = *(rplane++);
    bufferAuxPtr[1] = *(gplane++);
    bufferAuxPtr[2] = *(bplane++);
    bufferAuxPtr[3] = img->has_alpha ? *(aplane++) : 0xFF;
    bufferAuxPtr += 4;
  }

  unsigned int textureId = 0;
  glGenTextures(1, &textureId);

  glBindTexture(GL_TEXTURE_2D, textureId);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, data_type, imageBuffer);

  GlUtils::Texture tex{ img->width, img->height, textureId };

  delete[] imageBuffer;
  imImageDestroy(img);

  return tex;
}

void GlUtils::uglViewportAndOrtho(int s)
{
  glViewport(0, 0, s, s);
  glLoadIdentity();
  glOrtho(0, s, s, 0, -1.0, 1.0);
}

void GlUtils::drawSquare(int x, int y, int squareSize)
{
  glBegin(GL_QUADS);
  glVertex2i(x, y);
  glVertex2i(x + squareSize, y);
  glVertex2i(x + squareSize, y + squareSize);
  glVertex2i(x, y + squareSize);
  glEnd();
}

void GlUtils::draw2DTexture(int texId, int x, int y, int sq, Color color)
{
  //glBindTexture(GL_TEXTURE_2D, 0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texId);
  GlUtils::uglColor4f(color);
  glBegin(GL_QUADS);
  // top-right
  glTexCoord2f(0.0f, 1.0f); glVertex2i(x, y);
  // top-left
  glTexCoord2f(1.0f, 1.0f); glVertex2i(x + sq, y);
  // bottom-left
  glTexCoord2f(1.0f, 0.0f); glVertex2i(x + sq, y + sq);
  // bottom-right
  glTexCoord2f(0.0f, 0.0f); glVertex2i(x, y + sq);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
