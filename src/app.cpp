#include "app.h"
#include <game_app.h>
#include <iostream>

App* App::instance = nullptr;

void App::show()
{
  instance->mMainWindow.show();
}

App::App()
{
  std::filesystem::path currentPath;
#ifdef WORKING_DIR
  currentPath = std::filesystem::path{WORKING_DIR};
#else
  currentPath = std::filesystem::current_path();
#endif
  this->mImagesPath = currentPath.append("images");

  mMainWindow.init(mCanvas);

  mBoard = Board(600);
}

void App::start()
{
  if (instance == nullptr)
    instance = new App();
  show();
}

void App::updateBoard()
{
  if (instance == nullptr) return;
  instance->mBoard.drawBoard(instance->mGame);
}

std::filesystem::path App::getImagePath(std::string imageFileName)
{
  auto imagesPath = instance->mImagesPath;
  return imagesPath.append(imageFileName);
}
