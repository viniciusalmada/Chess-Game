#pragma once
#include <utility>

class Coordinate
{
  std::pair<int, int> pair;

public:

  Coordinate();

  Coordinate(int a, int b);

  bool operator!=(const Coordinate& other) const;

  int x() const { return pair.first; };
  int y() const { return pair.second; };
};