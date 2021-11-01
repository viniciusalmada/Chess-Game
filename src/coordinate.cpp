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
