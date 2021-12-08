#include <string>
#include "main_window.h"
#include <iostream>
#include <shader.h>

static App* appPtr = nullptr;

static CoordinateI _positionPressed{};

CoordinateI _getGLFWCursorPos(GLFWwindow* win)
{
  double xpos, ypos;
  glfwGetCursorPos(win, &xpos, &ypos);
  int xi = static_cast<int>(floor(xpos));
  int yi = static_cast<int>(floor(ypos));
  return { xi, yi };
}

MainWindow::MainWindow()
{
  if (!glfwInit())
    return;

  mDialog = glfwCreateWindow(GameRenderer::WINDOW_SIZE, GameRenderer::WINDOW_SIZE, "Chess Game", nullptr, nullptr);

  glfwSetMouseButtonCallback(mDialog, [](GLFWwindow* w, int b, int a, int m)
    {
      if (b == GLFW_MOUSE_BUTTON_LEFT && a == GLFW_PRESS)
      {
        _positionPressed = _getGLFWCursorPos(w);
        return;
      }

      if (b == GLFW_MOUSE_BUTTON_LEFT && a == GLFW_RELEASE)
      {
        auto currentPos = _getGLFWCursorPos(w);
        if (CoordinateI::distance(currentPos, _positionPressed) < 0.02 * GameRenderer::WINDOW_SIZE)
        {
          onLeftMouseClicked(currentPos);
        }
      }
    });

  glfwMakeContextCurrent(mDialog);
  if (glewInit())
    std::cerr << "Error!" << std::endl;

  std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

MainWindow::~MainWindow()
{
  glfwTerminate();
  glfwDestroyWindow(mDialog);
}

void MainWindow::setApp(App* app)
{
  appPtr = app;
}

void MainWindow::actionLoop(std::function<void()> drawAction)
{
  auto clearColors = GameRenderer::backgroundColor.getColorsNormalized();
  float red = clearColors[0];
  float green = clearColors[1];
  float blue = clearColors[2];
  float alpha = clearColors[3];
  while (!glfwWindowShouldClose(mDialog))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(red, green, blue, alpha);

    drawAction();

    glfwSwapBuffers(mDialog);

    glfwWaitEvents();
  }
}

void MainWindow::onLeftMouseClicked(CoordinateI position)
{
  if (!appPtr)
    return;

  appPtr->processLeftClick(position);
}
