#pragma once
#include <iup/iup.h>
#include <canvas.h>

class MainWindow
{
  Ihandle* mDialog = nullptr;

public:
  MainWindow() {};

  void init(Canvas& canvas);

  void show(const Canvas& cnv) const;
};