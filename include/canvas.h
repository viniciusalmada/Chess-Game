#pragma once
#include <iup/iup.h>
#include <board.h>
#include <string>

class Canvas
{
  Ihandle* mCnv;

  Board* mBoard;

  static Canvas* instance;

  static std::string ATTR_BOARD;

  static int actionCallback(Ihandle* ih);

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