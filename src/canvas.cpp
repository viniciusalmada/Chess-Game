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

static unsigned int CompileShader(unsigned int type, const std::string& src)
{
  unsigned int id = glCreateShader(type);
  auto sourceC = src.c_str();
  glShaderSource(id, 1, &sourceC, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    int len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
    char* message = new char[len];
    glGetShaderInfoLog(id, len, &len, message);
    std::cout << message << std::endl;
    glDeleteShader(id);
    delete[] message;
    return 0;
  }

  return id;
}

static unsigned int CreateProgram(const std::string& vertexShader, const std::string& fragShader)
{
  unsigned int programId = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

  glAttachShader(programId, vs);
  glAttachShader(programId, fs);
  glLinkProgram(programId);
  glValidateProgram(programId);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return programId;
}

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

  std::string vshader = R"glsl(
    #version 330 core
    layout(location = 0) in vec4 position;
    layout(location = 1) in vec3 rgbColor;
    out vec4 fragColor;
    void main()
    {
      gl_Position = position;
      fragColor = vec4(rgbColor.xyz, 1.0);
    }
    )glsl";
  std::string fshader = R"glsl(
    #version 330 core
    in vec4 fragColor;
    out vec4 color;
    void main()
    {
      color = fragColor;
    }
    )glsl";

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

  unsigned int program = CreateProgram(vshader, fshader);
  glUseProgram(program);
}