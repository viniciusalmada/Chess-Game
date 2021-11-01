#pragma once
#include <utility>
#include <array>

enum class File
{
  F_A = 0,
  F_B = 1,
  F_C = 2,
  F_D = 3,
  F_E = 4,
  F_F = 5,
  F_G = 6,
  F_H = 7,
  F_UNDEF = -1,
};
enum class Rank
{
  R_1 = 0,
  R_2 = 1,
  R_3 = 2,
  R_4 = 3,
  R_5 = 4,
  R_6 = 5,
  R_7 = 6,
  R_8 = 7,
  R_UNDEF = -1,
};

class SquarePosition
{
  File file;
  Rank rank;

public:
  SquarePosition();

  SquarePosition(File file, Rank rank);

  SquarePosition(int fileId, int rankId);

  int fileId() const;

  int rankId() const;

  File getFile() const { return file; }

  Rank getRank() const { return rank; }

  bool operator==(const SquarePosition& other) const;
  
  bool operator!=(const SquarePosition& other) const;

  bool operator<(const SquarePosition& other) const;
};

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