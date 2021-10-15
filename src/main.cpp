#include <iup/iup.h>
#include <iup/iupgl.h>
#include <GL/glew.h>
#include <cstdio>
#include <string>

#include "gl_utils.h"
#include "board.h"

Board* board;

int canvas_action_cb(Ihandle* ih, float posx, float posy)
{
  IupGLMakeCurrent(ih);
  GlUtils::uglClearColor(GlUtils::WHITE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_LINE_SMOOTH);

  if (board)
    board->drawBoard();

  IupGLSwapBuffers(ih);

  return IUP_DEFAULT;
}

int redraw_canvas_cb(Ihandle* ih)
{
  printf(" called ");
  IupRedraw(ih, true);

  return IUP_DEFAULT;
}

int main(int argc, char* argv[])
{
  int x = 600;
  board = new Board(x);

  IupOpen(&argc, &argv);
  IupGLCanvasOpen();

  Ihandle* canvas = IupGLCanvas(nullptr);
  IupSetHandle("canvas", canvas);
  IupSetAttribute(canvas, "EXPAND", "YES");
  IupSetAttribute(canvas, "BORDERS", "YES");
  IupSetCallback(canvas, "K_s", redraw_canvas_cb);
  IupSetCallback(canvas, "ACTION", (Icallback)canvas_action_cb);

  Ihandle* box = IupHbox(canvas, nullptr);

  Ihandle* dlg = IupDialog(box);
  IupSetAttribute(dlg, "TITLE", "Chess with IUP");
  IupSetAttribute(dlg, "RASTERSIZE", "100x100"); // 16 hor / 39 ver
  IupSetAttribute(dlg, "RESIZE", "NO");

  IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

  int ndx, ndy;
  IupGetIntInt(dlg, "NATURALSIZE", &ndx, &ndy);
  int cdx, cdy;
  IupGetIntInt(dlg, "CLIENTSIZE", &cdx, &cdy);

  int userPredefined = 600;
  int dx = ndx - cdx;
  int dy = ndy - cdy;
  int newX = userPredefined + dx;
  int newY = userPredefined + dy;
  std::string str = std::to_string(newX) + "x" + std::to_string(newY);
  IupHide(dlg);
  IupSetAttribute(dlg, "RASTERSIZE", str.c_str());
  IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

  IupRedraw(canvas, true);
  IupRedraw(canvas, true);

  IupMainLoop();

  IupClose();

  delete board;

  return 0;
}