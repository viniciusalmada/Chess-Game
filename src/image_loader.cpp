#include <GL/glew.h>
#include <im/im.h>
#include <im/im_image.h>

#include "image_loader.h"
#include <stdexcept>

imImage* ImageLoader::load(std::string path)
{
  int error;
  imImage* img = imFileImageLoad(path.c_str(), 0, &error);
  if (error) {
    throw std::runtime_error("Error loading image from path \"" + path + "\"");
  }
  return img;
}
