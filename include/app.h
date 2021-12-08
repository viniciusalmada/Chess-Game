#pragma once
#include <filesystem>
#include <string>
#include <memory>

#include <sp_string.h>
#include <game_app.h>
#include <game_renderer.h>

class App
{
  GameApp gameApp;
  GameRenderer gameRenderer;

  static std::filesystem::path getWorkingDir();

  static std::filesystem::path getShadersPath();

public:
  App();

  void show();

  void updateBoard();

  void processLeftClick(int x, int y);

  static std::filesystem::path getImagePath(std::string imageFileName);
};