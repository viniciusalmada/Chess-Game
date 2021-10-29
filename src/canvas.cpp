#include "canvas.h"
#include <iup/iupgl.h>
#include <iup/iupdef.h>
#include <app.h>
#include <gl_utils.h>
#include <GL/glew.h>
#include <log.h>

static Coordinate _mousePressedCoord;

Canvas* Canvas::instance = nullptr;

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

  Log::logDebug({ "pressed?" + std::to_string(btn) + "x = " + std::to_string(x) + ",y = " + std::to_string(y) });
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
    IupSetCallback(instance->mCnv, IUP_BUTTON_CB, (Icallback)Canvas::buttonCallback);
  }
}

void Canvas::redraw() const
{
  IupRedraw(mCnv, true);
}
