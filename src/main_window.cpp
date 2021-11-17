#include <GL/glew.h>
#include <string>
#include "main_window.h"
#include <app.h>
#include <iostream>

void MainWindow::initOGL()
{
  glfwMakeContextCurrent(mDialog);
  if (glewInit())
    std::cerr << "Error!" << std::endl;

  std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  auto shadersPath = App::getShadersPath();

  GlUtils::Program program(shadersPath);
  program.use();
}

MainWindow::MainWindow()
{
  if (!glfwInit())
    return;

  mDialog = glfwCreateWindow(App::PREDEFINED_SIZE, App::PREDEFINED_SIZE, "Chess Game", nullptr, nullptr);
}

MainWindow::~MainWindow()
{
  glfwDestroyWindow(mDialog);
}

void MainWindow::actionLoop(std::function<void()> drawAction)
{
  int secs = 0;

  while (!glfwWindowShouldClose(mDialog))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAction();

    glfwSwapBuffers(mDialog);

    glfwPollEvents();
    
  }
}
