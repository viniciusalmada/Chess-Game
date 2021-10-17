#include "app.h"
#include <sp_string.h>

App* App::instance = nullptr;

int App::sPredefinedSize = 600;

App::App(std::string executablePath)
{
  SP::String spPath(executablePath);
  auto pathDivided = spPath.split("\\");
  pathDivided.pop_back();
  pathDivided.pop_back();

  pathDivided.push_back({ "images" });
  this->mImagesPath = SP::String().appendAll(pathDivided, "\\");
}

App* App::getInstance()
{
  return instance;
}

void App::start(std::string executablePath)
{
  if (instance == nullptr)
  {
    instance = new App(executablePath);
  }
}

std::string App::getImagePath(std::string imageFileName)
{
  return getInstance()->mImagesPath
    .append(imageFileName)
    .getStr();
}
