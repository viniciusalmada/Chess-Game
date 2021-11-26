#pragma once
#include <string>
#include <im/im_image.h>

class ImageLoader
{
private:
  static imImage* loadImage(std::string path);

public:
  static unsigned char* loadTexture(const std::string& path, int& width, int& height);
};