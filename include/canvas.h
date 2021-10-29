#pragma once
#include <iup/iup.h>
#include <board.h>
#include <string>

class Canvas
{
  Ihandle* mCnv;

  Board* mBoard;

  static Canvas* instance;

  static int actionCallback(Ihandle* ih);

  static int buttonCallback(Ihandle* ih, int btn, int pressed, int x, int y, char* status);

  Canvas();

  ~Canvas();

public:

  static Canvas* getInstance();

  static void build();

  Canvas(Canvas& other) = delete;

  void operator=(const Canvas& other) = delete;

  Ihandle* handle() const { return mCnv; }

  void redraw() const;
};