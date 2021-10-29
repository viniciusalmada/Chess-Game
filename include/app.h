#pragma once
#include <filesystem>
#include <sp_string.h>
#include <string>
class App
{
  static App* instance;

  std::filesystem::path mImagesPath;

  App();

public:

  static int sPredefinedSize;

  static App* getInstance();
  
  static void start();

  static std::filesystem::path getImagePath(std::string imageFileName);

  App(App& other) = delete;

  void operator=(const App& other) = delete;


};