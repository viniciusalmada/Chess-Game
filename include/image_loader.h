#pragma once
#include <string>
#include <im/im_image.h>

class ImageLoader
{
public:
  static imImage* load(std::string path);
};