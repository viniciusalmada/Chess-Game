#pragma once
#include <sp_string.h>
#include <string>
class App
{
  static App* instance;

  SP::String mImagesPath;

  App(std::string executablePath);

public:

  static int sPredefinedSize;

  static App* getInstance();
  
  static void start(std::string executablePath);

  App(App& other) = delete;

  void operator=(const App& other) = delete;


};