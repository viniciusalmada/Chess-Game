#include "square_data.h"

int SquareData::getBytesCount() const
{
  return topLeft.getBytesCount() +
    topRight.getBytesCount() +
    botRight.getBytesCount() +
    botLeft.getBytesCount() +
    color.getBytesCount();
}
