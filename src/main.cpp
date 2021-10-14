#include <iup/iup.h>
#include <iup/iupgl.h>
#include <GL/glew.h>

#include "gl_utils.h"
#include "board.h"

Board* board;

int canvas_action_cb(Ihandle* ih, float posx, float posy)
{
  IupGLMakeCurrent(ih);
  GlUtils::uglClearColor(0xE8E6E4);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_LINE_SMOOTH);

  int x = 0;
  if (board)
    x = board->getSideSize();
  glViewport(0, 0, x, x);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, x, x, 0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glShadeModel(GL_SMOOTH);

  glBegin(GL_TRIANGLES);
  GlUtils::uglColor3d(0xFF0000);
  glVertex2d(x * 0.5, x * 0.1);
  GlUtils::uglColor3d(0x00FF00);
  glVertex2d(x * 0.1, x * 0.9);
  GlUtils::uglColor3d(0x0000FF);
  glVertex2d(x * 0.9, x * 0.9);
  glEnd();

   glBegin(GL_QUADS);
   GlUtils::uglColor3d(0x314FAB);
   glVertex2d(x * 0.3, x * 0.3);
   glVertex2d(x * 0.6, x * 0.3);
   glVertex2d(x * 0.6, x * 0.6);
   glVertex2d(x * 0.3, x * 0.6);
   glEnd();

  IupGLSwapBuffers(ih);

  return IUP_DEFAULT;
}

int redraw_canvas_cb(Ihandle* ih)
{
  IupRedraw(IupGetHandle("canvas"), true);

  return IUP_DEFAULT;
}

int main(int argc, char* argv[])
{
  IupOpen(&argc, &argv);
  IupGLCanvasOpen();

  Ihandle* canvas = IupGLCanvas(nullptr);
  IupSetHandle("canvas", canvas);
  IupSetAttribute(canvas, "EXPAND", "YES");
  IupSetAttribute(canvas, "BORDERS", "NO");
  IupSetCallback(canvas, "ACTION", (Icallback)canvas_action_cb);

  Ihandle* box = IupHbox(canvas, nullptr);

  Ihandle* dlg = IupDialog(box);
  IupSetAttribute(dlg, "TITLE", "Chess with IUP");
  IupSetAttribute(dlg, "RASTERSIZE", "600x600");
  IupSetAttribute(dlg, "RESIZE", "NO");
  IupSetCallback(dlg, "K_s", redraw_canvas_cb);

  IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

  int x;
  IupGetIntInt(canvas, "DRAWSIZE", &x, nullptr);
  board = new Board(x);

  IupRedraw(canvas, true);

  IupMainLoop();

  IupClose();

  delete board;

  return 0;
}