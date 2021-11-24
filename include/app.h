#pragma once
#include <filesystem>
#include <string>
#include <memory>

#include <sp_string.h>
#include <main_window.h>
#include <game_app.h>
#include <board_renderer.h>

class App
{
  static GameApp gameApp;
  static MainWindow mainWindow;
  static BoardRenderer board;

  static std::filesystem::path imagesPath;
  static std::filesystem::path shadersPath;

  void show();

public:

  App();

  static void start();

  void updateBoard();

  void processLeftClick(int x, int y);

  static std::filesystem::path getImagePath(std::string imageFileName);
  
  static std::filesystem::path getShadersPath();
};