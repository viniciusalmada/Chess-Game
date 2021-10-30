#pragma once
#include <filesystem>
#include <sp_string.h>
#include <string>
#include <memory>

class App
{
  static std::shared_ptr<App> instance;

  std::filesystem::path mImagesPath;

  App();

public:

  static int sPredefinedSize;

  static std::shared_ptr<App> getInstance();
  
  static void start();

  static std::filesystem::path getImagePath(std::string imageFileName);

  App(App& other) = delete;

  void operator=(const App& other) = delete;


};