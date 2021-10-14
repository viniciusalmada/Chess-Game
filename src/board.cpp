#include "board.h"

Board::Board(int sideSize) : mSideSize(sideSize)
{
}

int Board::getSideSize() const
{
  return mSideSize;
}
