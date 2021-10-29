#include "canvas.h"
#include <iup/iupgl.h>
#include <iup/iupdef.h>
#include <app.h>
#include <gl_utils.h>
#include <GL/glew.h>

Canvas* Canvas::instance = nullptr;

std::string Canvas::ATTR_BOARD = "ATTR_BOARD";

int Canvas::actionCallback(Ihandle* cnv)
{
  IupGLMakeCurrent(cnv);
  GlUtils::uglClearColor(GlUtils::WHITE);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (getInstance()->mBoard)
    getInstance()->mBoard->drawBoard();

  glFlush();

  return IUP_DEFAULT;
}

Canvas::Canvas()
{
  mCnv = IupGLCanvas(nullptr);
  IupSetAttribute(mCnv, IUP_EXPAND, IUP_YES);
  IupSetAttribute(mCnv, IUP_BORDER, IUP_YES);

  mBoard = new Board(App::sPredefinedSize);
}

Canvas::~Canvas()
{
  delete mBoard;
}

Canvas* Canvas::getInstance()
{
  return instance;
}

void Canvas::build()
{
  if (instance == nullptr)
  {
    instance = new Canvas();
    IupSetCallback(instance->mCnv, IUP_ACTION, (Icallback)Canvas::actionCallback);
  }
}

void Canvas::redraw() const
{
  IupRedraw(mCnv, true);
}
