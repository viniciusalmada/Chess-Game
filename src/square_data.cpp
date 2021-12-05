#include "square_data.h"

SquareData::SquareData(Coordinate tl, Coordinate tr, Coordinate br, Coordinate bl, Color color)
  :topLeft(tl), topRight(tr), botRight(br), botLeft(bl), color(color)
{
}

int SquareData::getBytesCount() const
{
  return topLeft.getBytesCount() +
    topRight.getBytesCount() +
    botRight.getBytesCount() +
    botLeft.getBytesCount() +
    color.getBytesCount();
}
