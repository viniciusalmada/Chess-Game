#include <GL/glew.h>
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
}

MainWindow::~MainWindow()
{
  glfwTerminate();
  glfwDestroyWindow(mDialog);
}

void MainWindow::actionLoop(std::function<void()> drawAction)
{
  while (!glfwWindowShouldClose(mDialog))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    GlUtils::uglClearColor(GameRenderer::backgroundColor);

    drawAction();

    glfwSwapBuffers(mDialog);

    glfwPollEvents();
  }
}
