#pragma once
#include <iup/iup.h>
#include <board.h>
#include <string>
#include <memory>

class Canvas
{
  Ihandle* mCnv;

  std::unique_ptr<Board> mBoard;

  static std::shared_ptr<Canvas> instance;

  static int actionCallback(Ihandle* ih);

  static int buttonCallback(Ihandle* ih, int btn, int pressed, int x, int y, char* status);

  Canvas();

public:

  static std::shared_ptr<Canvas> getInstance();

  static void build();

  Canvas(Canvas& other) = delete;

  void operator=(const Canvas& other) = delete;

  Ihandle* handle() const { return mCnv; }

  void redraw() const;
};