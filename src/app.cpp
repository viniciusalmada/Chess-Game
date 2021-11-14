#include "app.h"
#include <game_app.h>
#include <iostream>

App* App::instance = nullptr;

void App::show()
{
  instance->mMainWindow.initOGL();
  instance->mMainWindow.actionLoop([]()
    {
      instance->mBoard.drawBoard();
    });
  glfwTerminate();
}

App::App()
{
  std::filesystem::path currentPath;
#ifdef WORKING_DIR
  currentPath = std::filesystem::path{ WORKING_DIR };
#else
  currentPath = std::filesystem::current_path();
#endif
  this->mImagesPath = std::filesystem::path{ currentPath }.append("res").append("images");
  this->mShadersPath = std::filesystem::path{ currentPath }.append("res").append("shaders");

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
  instance->mBoard.drawBoard();
}

void App::processLeftClick(int x, int y)
{
  SquarePosition squareSelected = instance->mBoard.getSelectedSquare(x, y);
  bool toRedraw = instance->mGame.processAction(squareSelected);
  if (toRedraw) updateBoard();
}

std::filesystem::path App::getImagePath(std::string imageFileName)
{
  auto imagesPath = instance->mImagesPath;
  return imagesPath.append(imageFileName);
}

std::filesystem::path App::getShadersPath()
{
  return instance->mShadersPath;
}
