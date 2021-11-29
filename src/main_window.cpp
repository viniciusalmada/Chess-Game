#include <string>
#include "main_window.h"
#include <app.h>
#include <iostream>
#include <shader.h>

MainWindow::MainWindow()
{
  if (!glfwInit())
    return;

  mDialog = glfwCreateWindow(GameRenderer::WINDOW_SIZE, GameRenderer::WINDOW_SIZE, "Chess Game", nullptr, nullptr);

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

    glfwPollEvents();
  }
}
