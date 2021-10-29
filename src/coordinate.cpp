#include "coordinate.h"

Coordinate::Coordinate()
{
  pair = { 0,0 };
}

Coordinate::Coordinate(int a, int b)
{
  pair = { a, b };
}

bool Coordinate::operator!=(const Coordinate& other) const
{
  return x() != other.x() && y() != other.y() ;
}
