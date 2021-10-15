#pragma once
class Board
{
  const int mBorderSize = 10;
  int mSideSize;

public:
  static int sBackgroundColor;
  static int sHouseDark;
  static int sHouseLight;

  Board(int sideSize);

  int getSideSize() const;

  void drawBoard();
};

