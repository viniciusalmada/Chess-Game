#pragma once
#include <gl_headers.h>
#include <memory>
#include <functional>

class MainWindow
{
  GLFWwindow* mDialog = nullptr;


public:
  MainWindow();

  ~MainWindow();

  void actionLoop(std::function<void()> action);
};