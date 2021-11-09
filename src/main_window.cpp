#include <iup/iup.h>
#include <iup/iupgl.h>
#include <string>
#include "main_window.h"
#include <app.h>

void MainWindow::init(Canvas& canvas)
{
  IupOpen(nullptr, nullptr);
  IupGLCanvasOpen();

  canvas.init();

  Ihandle* box = IupHbox(canvas.handle(), nullptr);

  mDialog = IupDialog(box);
  IupSetAttribute(mDialog, IUP_TITLE, "Chess with IUP");
  IupSetAttribute(mDialog, IUP_RASTERSIZE, "100x100");
  IupSetAttribute(mDialog, IUP_RESIZE, IUP_NO);

  IupShowXY(mDialog, IUP_CENTER, IUP_CENTER);


  int ndx, ndy;
  IupGetIntInt(mDialog, "NATURALSIZE", &ndx, &ndy);
  int cdx, cdy;
  IupGetIntInt(mDialog, "CLIENTSIZE", &cdx, &cdy);

  int dx = ndx - cdx;
  int dy = ndy - cdy;
  int newX = App::PREDEFINED_SIZE + dx;
  int newY = App::PREDEFINED_SIZE + dy;
  std::string newSizeStr = std::to_string(newX) + "x" + std::to_string(newY);
  IupHide(mDialog);
  IupSetAttribute(mDialog, "RASTERSIZE", newSizeStr.c_str());

}

void MainWindow::show(Canvas& canvas) const
{
  IupShowXY(mDialog, IUP_CENTER, IUP_CENTER);
  canvas.initOGL();

  auto canvasHandle = IupGetHandle(Canvas::HANDLE_NAME.c_str());
  IupRedraw(canvasHandle, true);
  IupRedraw(canvasHandle, true);

  IupMainLoop();

  IupClose();
}
