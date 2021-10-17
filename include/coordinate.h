#pragma once
#include <utility>

class Coordinate
{
  std::pair<int, int> pair;

public:

  Coordinate();

  Coordinate(int a, int b);

  int x() const { return pair.first; };
  int y() const { return pair.second; };
};