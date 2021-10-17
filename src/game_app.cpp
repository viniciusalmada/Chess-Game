#include "game_app.h"

GameApp* GameApp::instance = nullptr;

GameApp::GameApp()
{
}

GameApp* GameApp::getInstance()
{
  return instance;
}

void GameApp::start()
{
  if (instance == nullptr)
  {
    instance = new GameApp();
  }
}
