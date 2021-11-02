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
  return x() != other.x() && y() != other.y();
}

SquarePosition::SquarePosition()
{
  file = File::F_UNDEF;
  rank = Rank::R_UNDEF;
}

SquarePosition::SquarePosition(File file, Rank rank)
{
  this->file = file;
  this->rank = rank;
}

SquarePosition::SquarePosition(int fileId, int rankId)
{
  this->file = static_cast<File>(fileId);
  this->rank = static_cast<Rank>(rankId);
}

int SquarePosition::fileId() const
{
  return static_cast<int>(file);
}

int SquarePosition::rankId() const
{
  return static_cast<int>(rank);
}

bool SquarePosition::operator==(const SquarePosition& other) const
{
  return fileId() == other.fileId() &&
    rankId() == other.rankId();;
}

bool SquarePosition::operator!=(const SquarePosition& other) const
{
  return !(*this == other);
}

bool SquarePosition::operator<(const SquarePosition& other) const
{
  return file < other.file || (file == other.file && rank < other.rank);
}

std::set<SquarePosition> SquarePosition::getAllOnFile() const
{
  std::set<SquarePosition> squares;
  for (int i = 0; i < 8; i++)
  {
    squares.insert({ getFile(), (Rank)i });
  }
  return squares;
}

std::set<SquarePosition> SquarePosition::getAllOnRank() const
{
  std::set<SquarePosition> squares;
  for (int i = 0; i < 8; i++)
  {
    squares.insert({ (File)(i), getRank() });
  }
  return squares;
}

SquarePosition SquarePosition::getEastOrSouthBorderSquare() const
{
  if ((int)file == (int)rank)
    return { File::F_A, Rank::R_1 };

  if (file == File::F_A && rank == Rank::R_8)
    return *this;

  if (file == File::F_H && rank == Rank::R_1)
    return *this;

  if ((int)file > (int)rank) // border on south
  {
    int diffToFirstRank = (int)rank;
    return { (int)file - diffToFirstRank, (int)Rank::R_1 };
  }

  int diffToFirstFile = (int)file;
  return { (int)File::F_A, (int)rank - diffToFirstFile };
}

std::set<SquarePosition> SquarePosition::getAllInSWtoNE() const
{
  if (isOnWestSide() && isOnNorthSide())
    return std::set<SquarePosition>{*this};

  if (isOnEastSide() && isOnSouthSide())
    return std::set<SquarePosition>{*this};



  return std::set<SquarePosition>();
}
