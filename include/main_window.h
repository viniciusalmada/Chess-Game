#pragma once
#include <iup/iup.h>
#include <canvas.h>

class MainWindow
{
  Ihandle* mDialog;

public:
  MainWindow();

  void show() const;
};