#include "app.h"
#include <sp_string.h>

App::App(std::string executablePath)
{
  SP::String spPath(executablePath);
  auto pathDivided = spPath.split("\\");
  pathDivided.pop_back();
  pathDivided.pop_back();

  pathDivided.push_back({ "images" });
  this->mImagesPath = SP::String().appendAll(pathDivided, "\\");
}