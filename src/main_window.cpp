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

  float positions[] = {
    -0.75f, -0.75f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.75f, 1.0f, 1.0f, 0.0f,
    0.75f, -0.75f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
  };

  unsigned int bufferID;
  glGenBuffers(1, &bufferID);
  glBindBuffer(GL_ARRAY_BUFFER, bufferID);
  glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); // positions attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

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

void MainWindow::actionLoop(std::function<void()> action)
{
	while (!glfwWindowShouldClose(mDialog))
	{
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(mDialog);

    glfwPollEvents();
		action();
	}
}
