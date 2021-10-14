#pragma once
class Board
{
  const int mBorderSize = 10;
  int mSideSize;

public:
  Board(int sideSize);

  int getSideSize() const;
};

