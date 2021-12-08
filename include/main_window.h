#pragma once
#include <gl_headers.h>
#include <memory>
#include <functional>
#include <coordinate.h>
#include <app.h>

class MainWindow
{
  GLFWwindow* mDialog = nullptr;

public:
  MainWindow();

  ~MainWindow();

  void setApp(App* app);

  void actionLoop(std::function<void()> action);

  static void onLeftMouseClicked(CoordinateI position);
};