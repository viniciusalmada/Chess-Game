#pragma once
#include <utility>
#include <set>
#include <string>
#include "countable.h"

enum class Direction
{
  N, E, W, S, NE, SE, SW, NW
};

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

  bool isValid() const { return rank != Rank::R_UNDEF && file != File::F_UNDEF; };

  bool isOnNSide() const { return rank == Rank::R_8; }
  bool isOnESide() const { return file == File::F_H; }
  bool isOnSSide() const { return rank == Rank::R_1; }
  bool isOnWSide() const { return file == File::F_A; }
  bool isOnNECorner() const { return isOnNSide() && isOnESide(); }
  bool isOnSECorner() const { return isOnSSide() && isOnESide(); }
  bool isOnSWCorner() const { return isOnSSide() && isOnWSide(); }
  bool isOnNWCorner() const { return isOnNSide() && isOnWSide(); }

  SquarePosition neighbor(Direction direction) const;
  SquarePosition neighborN() const;
  SquarePosition neighborE() const;
  SquarePosition neighborS() const;
  SquarePosition neighborW() const;
  SquarePosition neighborNE() const;
  SquarePosition neighborSE() const;
  SquarePosition neighborSW() const;
  SquarePosition neighborNW() const;

  std::set<SquarePosition> getAllOnFile() const;
  std::set<SquarePosition> getAllOnRank() const;
  std::set<SquarePosition> getAllOnSWtoNE() const;
  std::set<SquarePosition> getAllOnNWtoSE() const;

  SquarePosition fromRelativePath(int fileSteps, int rankSteps) const;

  std::string toString() const;
};

template<typename T>
class Coordinate : public Countable
{
  T x;
  T y;

public:

  static double distance(const Coordinate& rhs, const Coordinate& lhs);

  Coordinate();

  Coordinate(T x, T y);

  bool operator!=(const Coordinate& other) const;

  Coordinate& operator+=(const Coordinate& rhs);

  T getX() const { return x; }
  T getY() const { return y; }

  int getBytesCount() const override;
};

template<typename T>
inline double Coordinate<T>::distance(const Coordinate& rhs, const Coordinate& lhs)
{
  double squareX2X1 = (lhs.getX() - rhs.getX()) * (lhs.getX() - rhs.getX());
  double squareY2Y1 = (lhs.getY() - rhs.getY()) * (lhs.getY() - rhs.getY());
  return sqrt(squareX2X1 + squareY2Y1);
}

template<typename T>
inline Coordinate<T>::Coordinate() : x(), y()
{
}

template<typename T>
Coordinate<T>::Coordinate(T x, T y) : x(x), y(y)
{
};

template<typename T>
bool Coordinate<T>::operator!=(const Coordinate& other) const
{
  return getX() != other.getX() && getY() != other.getY();
}

template<typename T>
Coordinate<T>& Coordinate<T>::operator+=(const Coordinate& rhs)
{
  this->x += rhs.getX();
  this->y += rhs.getY();

  return *this;
}

template<typename T>
int Coordinate<T>::getBytesCount() const
{
  return sizeof(x) + sizeof(y);
}

using CoordinateI = Coordinate<int>;
using CoordinateF = Coordinate<float>;