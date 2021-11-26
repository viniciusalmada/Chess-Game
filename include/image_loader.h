#pragma once
#include <string>
#include <im/im.h>
#include <im/im_image.h>

class ImageLoader
{
private:

public:
  static imImage* loadImage(std::string path);
  static unsigned char* loadTexture(const std::string& path, int& width, int& height);
};