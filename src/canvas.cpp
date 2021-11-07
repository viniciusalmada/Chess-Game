#include "canvas.h"
#include <iup/iupgl.h>
#include <iup/iupdef.h>
#include <app.h>
#include <gl_utils.h>
#include <GL/glew.h>
#include <log.h>
#include <iostream>
#include <string>

std::string Canvas::HANDLE_NAME = "CHESS_CANVAS_HANDLE_NAME";

static Coordinate _mousePressedCoord;

int Canvas::actionCallback(Ihandle* cnv)
{
  IupGLMakeCurrent(cnv);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  IupGLSwapBuffers(cnv);

  return IUP_DEFAULT;
}

int Canvas::buttonCallback(Ihandle* ih, int btn, int pressed, int x, int y, char* status)
{
  if (!iup_isbutton1(status))
    return IUP_DEFAULT;

  if (pressed)
  {
    _mousePressedCoord = { x, y };
    return IUP_DEFAULT;
  }

  if (_mousePressedCoord != Coordinate(x, y))
    return IUP_DEFAULT;

  App::processLeftClick(x, y);

  return IUP_DEFAULT;
}

void Canvas::init()
{
  mCnv = IupGLCanvas(nullptr);
  IupSetAttribute(mCnv, IUP_EXPAND, IUP_YES);
  IupSetAttribute(mCnv, IUP_BORDER, IUP_YES);
  IupSetAttribute(mCnv, IUP_BUFFER, IUP_DOUBLE);
  IupSetHandle(HANDLE_NAME.c_str(), mCnv);

  IupSetCallback(mCnv, IUP_ACTION, (Icallback)Canvas::actionCallback);
  IupSetCallback(mCnv, IUP_BUTTON_CB, (Icallback)Canvas::buttonCallback);
}

void Canvas::initOGL() const
{
  IupGLMakeCurrent(mCnv);

  if (glewInit())
    std::cerr << "Error!" << std::endl;

  std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  float positions[] = {
    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  };

  unsigned int bufferID;
  glGenBuffers(1, &bufferID);
  glBindBuffer(GL_ARRAY_BUFFER, bufferID);
  glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); // positions attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

  auto shadersPath = App::getShadersPath();
  auto shaders = GlUtils::parseShaderString(shadersPath);

  unsigned int program = GlUtils::createProgram(shaders);
  glUseProgram(program);
}