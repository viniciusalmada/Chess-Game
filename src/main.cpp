#include <iup/iup.h>
#include <iup/iupgl.h>
#include <GL/glew.h>

#include "gl_utils.h"

int canvas_action_cb(Ihandle* ih, float posx, float posy)
{
  IupGLMakeCurrent(ih);
  GlUtils::uglClearColor(0xE8E6E4);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

  IupRedraw(dlg, true);

  IupMainLoop();

  IupClose();

  return 0;
}