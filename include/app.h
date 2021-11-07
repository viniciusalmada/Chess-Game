#pragma once
#include <filesystem>
#include <string>
#include <memory>

#include <sp_string.h>
#include <main_window.h>
#include <game_app.h>
#include <board.h>

class App
{
  static App* instance;

  GameApp mGame;
  MainWindow mMainWindow;
  Canvas mCanvas;
  Board mBoard;

  std::filesystem::path mImagesPath;
  std::filesystem::path mShadersPath;

  static void show();

public:

  App();

  static void start();

  const static int PREDEFINED_SIZE = 600;

  static void updateBoard();

  static void processLeftClick(int x, int y);

  static std::filesystem::path getImagePath(std::string imageFileName);
  
  static std::filesystem::path getShadersPath();

  App(App& other) = delete;

  void operator=(const App& other) = delete;
};