#include "app.h"
#include <game_app.h>
#include <iostream>

void App::show()
{
  board.draw();
}

std::filesystem::path App::getWorkingDir()
{
  std::filesystem::path currentPath;
#ifdef WORKING_DIR
  currentPath = std::filesystem::path{ WORKING_DIR };
#else
  currentPath = std::filesystem::current_path();
#endif
  return currentPath;
}

App::App() : gameApp(), board(getShadersPath())
{
  
}

void App::updateBoard()
{
  board.draw();
}

void App::processLeftClick(int x, int y)
{
  SquarePosition squareSelected = board.getSelectedSquare(x, y);
  bool toRedraw = gameApp.processAction(squareSelected);
  if (toRedraw) updateBoard();
}

std::filesystem::path App::getImagePath(std::string imageFileName)
{
  auto currentPath = getWorkingDir();
  return std::filesystem::path{ currentPath }.append("res").append("images").append(imageFileName);
}

std::filesystem::path App::getShadersPath()
{
  auto currentPath = getWorkingDir();
  return std::filesystem::path{ currentPath }.append("res").append("shaders");
}
