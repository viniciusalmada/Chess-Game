#pragma once
#include <GL/glew.h>
#include "gl_utils.h"
#include "numeric_utils.h"

int GlUtils::RED = 0xFF0000;
int GlUtils::WHITE = 0xFFFFFF;

std::array<float, 3> GlUtils::getColorsF(int hexColors)
{
  auto rgb = NumericUtils::hexTo3Dec(hexColors);

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
