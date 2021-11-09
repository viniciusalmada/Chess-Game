#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <functional>

class MainWindow
{
  GLFWwindow* mDialog = nullptr;


public:
  MainWindow();

  ~MainWindow();

  void initOGL();

  void actionLoop(std::function<void()> action);
};