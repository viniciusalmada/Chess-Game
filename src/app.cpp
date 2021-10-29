#include "app.h"
#include <game_app.h>
#include <iostream>

App *App::instance = nullptr;

int App::sPredefinedSize = 600;

App::App()
{
  std::filesystem::path currentPath;
#ifdef WORKING_DIR
  currentPath = std::filesystem::path{WORKING_DIR};
#else
  currentPath = std::filesystem::current_path();
#endif
  this->mImagesPath = currentPath.append("images");

  GameApp::start();
}

App *App::getInstance()
{
  return instance;
}

void App::start()
{
  if (instance == nullptr)
  {
    instance = new App();
  }
}

std::filesystem::path App::getImagePath(std::string imageFileName)
{
  auto imagesPath = getInstance()->mImagesPath;
  return imagesPath.append(imageFileName);
}
