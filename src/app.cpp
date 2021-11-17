#include "app.h"
#include <game_app.h>
#include <iostream>

GameApp App::gameApp{};
MainWindow App::mainWindow{};
Board App::board{};
std::filesystem::path App::imagesPath{};
std::filesystem::path App::shadersPath{};

void App::show()
{
  mainWindow.initOGL();
  mainWindow.actionLoop([]()
    {
      board.drawBoard();
    });
  glfwTerminate();
}

App::App()
{

}

void App::start()
{
  auto app = App();
  std::filesystem::path currentPath;
#ifdef WORKING_DIR
  currentPath = std::filesystem::path{ WORKING_DIR };
#else
  currentPath = std::filesystem::current_path();
#endif
  app.imagesPath = std::filesystem::path{ currentPath }.append("res").append("images");
  app.shadersPath = std::filesystem::path{ currentPath }.append("res").append("shaders");
  app.show();
}

void App::updateBoard()
{
  board.drawBoard();
}

void App::processLeftClick(int x, int y)
{
  SquarePosition squareSelected = board.getSelectedSquare(x, y);
  bool toRedraw = gameApp.processAction(squareSelected);
  if (toRedraw) updateBoard();
}

std::filesystem::path App::getImagePath(std::string imageFileName)
{
  App app{};
  std::filesystem::path imagesPath = app.imagesPath;
  return imagesPath.append(imageFileName);
}

std::filesystem::path App::getShadersPath()
{
  App app{};
  return app.shadersPath;
}
