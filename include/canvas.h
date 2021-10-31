#pragma once
#include <iup/iup.h>
#include <board.h>
#include <string>
#include <memory>

class Canvas
{
  Ihandle* mCnv = nullptr;

  std::unique_ptr<Board> mBoard;

  static int actionCallback(Ihandle* ih);

  static int buttonCallback(Ihandle* ih, int btn, int pressed, int x, int y, char* status);

public:

  static std::string HANDLE_NAME;

  Canvas() {};

  void init();

  Ihandle* handle() const { return mCnv; }
};