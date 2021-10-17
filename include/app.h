#pragma once
#include <sp_string.h>
#include <string>
class App
{
  SP::String mImagesPath;

public:
  static int sPredefinedSize;

  App(std::string executablePath);
};