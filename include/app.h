#pragma once
#include <GL/glew.h>
#include <filesystem>
#include <string>
#include <memory>

#include <sp_string.h>
#include <main_window.h>
#include <game_app.h>
#include <game_renderer.h>

class App
{
  GameApp gameApp;
  GameRenderer board;

  static std::filesystem::path getWorkingDir();

  static std::filesystem::path getShadersPath();

public:
  App();

  void show();

  void updateBoard();

  void processLeftClick(int x, int y);

  static std::filesystem::path getImagePath(std::string imageFileName);
};