#include <gl_headers.h>
#include <im/im.h>
#include <im/im_image.h>

#include "image_loader.h"
#include <stdexcept>

imImage* ImageLoader::loadImage(std::string path)
{
  int error;
  imImage* img = imFileImageLoad(path.c_str(), 0, &error);
  if (error)
  {
    throw std::runtime_error("Error loading image from path \"" + path + "\"");
  }
  return img;
}

unsigned char* ImageLoader::loadTexture(const std::string& path, int& width, int& height)
{
  imImage* img = loadImage(path);
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
  width = img->width;
  height = img->height;

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
  return imageBuffer;
}
