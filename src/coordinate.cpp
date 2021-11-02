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

SquarePosition SquarePosition::neighbor(Direction direction) const
{
  switch (direction)
  {
  case N:
    return neighborN();
  case E:
    return neighborE();
  case W:
    return neighborW();
  case S:
    return neighborS();
  case NE:
    return neighborNE();
  case SE:
    return neighborSE();
  case SW:
    return neighborSW();
  case NW:
    return neighborNW();
  }
  return SquarePosition();
}

SquarePosition SquarePosition::neighborN() const
{
  if (isOnNSide()) return *this;
  return { (int)file, (int)rank + 1 };
}

SquarePosition SquarePosition::neighborE() const
{
  if (isOnESide()) return *this;
  return { (int)file + 1, (int)rank };
}

SquarePosition SquarePosition::neighborS() const
{
  if (isOnSSide()) return *this;
  return { (int)file, (int)rank - 1 };
}

SquarePosition SquarePosition::neighborW() const
{
  if (isOnWSide()) return *this;
  return { (int)file - 1, (int)rank };
}

SquarePosition SquarePosition::neighborNE() const
{
  if (isOnNSide() || isOnESide()) return *this;
  return { (int)file + 1, (int)rank + 1 };
}

SquarePosition SquarePosition::neighborSE() const
{
  if (isOnSSide() || isOnESide()) return *this;
  return { (int)file + 1, (int)rank - 1 };
}

SquarePosition SquarePosition::neighborSW() const
{
  if (isOnSSide() || isOnWSide()) return *this;
  return { (int)file - 1, (int)rank - 1 };
}

SquarePosition SquarePosition::neighborNW() const
{
  if (isOnNSide() || isOnWSide()) return *this;
  return { (int)file - 1, (int)rank + 1 };
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

std::set<SquarePosition> SquarePosition::getAllOnSWtoNE() const
{
  if (isOnNWCorner())
    return std::set<SquarePosition>{*this};

  if (isOnSECorner())
    return std::set<SquarePosition>{*this};

  std::set<SquarePosition> allOnSWtoNE;
  SquarePosition auxPositionNE = *this;
  SquarePosition auxPositionSW = *this;
  for (int i = 0; i < 4; i++)
  {
    auxPositionNE = auxPositionNE.neighborNE();
    auxPositionSW = auxPositionSW.neighborSW();
    allOnSWtoNE.insert(auxPositionNE);
    allOnSWtoNE.insert(auxPositionSW);
  }

  return allOnSWtoNE;
}

std::set<SquarePosition> SquarePosition::getAllOnNWtoSE() const
{
  if (isOnNECorner())
    return std::set<SquarePosition>{*this};

  if (isOnSWCorner())
    return std::set<SquarePosition>{*this};

  std::set<SquarePosition> allOnNWtoSE;
  SquarePosition auxPositionNW = *this;
  SquarePosition auxPositionSE = *this;
  for (int i = 0; i < 4; i++)
  {
    auxPositionNW = auxPositionNW.neighborNW();
    auxPositionSE = auxPositionSE.neighborSE();
    allOnNWtoSE.insert(auxPositionNW);
    allOnNWtoSE.insert(auxPositionSE);
  }

  return allOnNWtoSE;
}

SquarePosition SquarePosition::fromRelativePath(int fileSteps, int rankSteps) const
{
  int newFileId = (int)file + fileSteps;
  if (newFileId < (int)File::F_A || newFileId >(int)File::F_H)
    return {};

  int newRankId = (int)rank + rankSteps;
  if (newRankId < (int)Rank::R_1 || newRankId >(int)Rank::R_8)
    return {};

  return { (int)file + fileSteps, (int)(rank)+rankSteps };
}
