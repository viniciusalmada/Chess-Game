#include "piece.h"

Piece::Piece()
{
  this->name = PieceName::UNDEFINED;
  this->player = Player::WHITE;
  this->position = { File::F_UNDEF, Rank::R_UNDEF };
  this->selected = false;
}

Piece::Piece(PieceName name, Player player, SquarePosition position)
{
  this->name = name;
  this->player = player;
  this->position = position;
  this->selected = false;
}

std::set<SquarePosition> Piece::rookPossibleMovements() const
{
  std::set<SquarePosition> moves;
  auto squaresHor = position.getAllOnRank();
  auto squaresVer = position.getAllOnFile();
  moves.insert(squaresHor.begin(), squaresHor.end());
  moves.insert(squaresVer.begin(), squaresVer.end());
  moves.erase(position);
  return moves;
}

std::set<SquarePosition> Piece::bishopPossibleMovements() const
{
  std::set<SquarePosition> moves;
  auto allOnSWtoNE = position.getAllOnSWtoNE();
  auto allOnNWtoSE = position.getAllOnNWtoSE();
  moves.insert(allOnSWtoNE.begin(), allOnSWtoNE.end());
  moves.insert(allOnNWtoSE.begin(), allOnNWtoSE.end());
  moves.erase(position);
  return moves;
}

std::set<SquarePosition> Piece::knightPossibleMovements() const
{
  int filesSteps[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
  int ranksSteps[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
  std::set<SquarePosition> moves;
  for (int i = 0; i < 8; i++)
  {
    auto positionFromRelative = position.fromRelativePath(filesSteps[i], ranksSteps[i]);
    if (positionFromRelative.isValid())
      moves.insert(positionFromRelative);
  }
  return moves;
}

std::set<SquarePosition> Piece::queenPossibleMovements() const
{
  Piece rookAuxiliar{ PieceName::ROOK, Player::WHITE, position };
  Piece bishopAuxiliar{ PieceName::BISHOP, Player::WHITE, position };
  auto rookMovements = rookAuxiliar.possibleMovements();
  auto bishopMovements = bishopAuxiliar.possibleMovements();
  std::set<SquarePosition> moves;
  moves.insert(rookMovements.begin(), rookMovements.end());
  moves.insert(bishopMovements.begin(), bishopMovements.end());
  moves.erase(position);
  return moves;
}

std::set<SquarePosition> Piece::kingPossibleMovements() const
{
  std::set<SquarePosition> moves;
  moves.insert(position.neighborN());
  moves.insert(position.neighborE());
  moves.insert(position.neighborS());
  moves.insert(position.neighborW());
  moves.insert(position.neighborNE());
  moves.insert(position.neighborSE());
  moves.insert(position.neighborSW());
  moves.insert(position.neighborNW());
  moves.erase(position);
  return moves;
}

std::set<SquarePosition> Piece::pawnPossibleMovements() const
{
  std::set<SquarePosition> moves;
  moves.insert(position.neighborN());
  moves.erase(position);
  return moves;
}

bool Piece::operator<(const Piece& other) const
{
  return this->position < other.getPosition();
}

bool Piece::operator==(const Piece& other) const
{
  return position == other.position;
}

bool Piece::equalPosition(SquarePosition pos) const
{
  return this->position == pos;
}

bool Piece::isUndefined() const
{
  return name == PieceName::UNDEFINED;
}

bool Piece::isBlack() const
{
  return player == Player::BLACK;
}

bool Piece::isWhite() const
{
  return player == Player::WHITE;
}

SquarePosition Piece::getPosition() const
{
  return position;
}

PieceName Piece::getName() const
{
  return name;
}

bool Piece::isSelected() const
{
  return this->selected;
}

std::set<SquarePosition> Piece::possibleMovements() const
{
  switch (name)
  {
  case PieceName::ROOK:
    return rookPossibleMovements();
  case PieceName::BISHOP:
    return bishopPossibleMovements();
  case PieceName::KNIGHT:
    return knightPossibleMovements();
  case PieceName::QUEEN:
    return queenPossibleMovements();
  case PieceName::KING:
    return kingPossibleMovements();
  case PieceName::PAWN:
    return pawnPossibleMovements();
  case PieceName::UNDEFINED:
    break;
  default:
    break;
  }
  return std::set<SquarePosition>();
}

std::string Piece::generateTitle() const
{
  std::string title;
  switch (name)
  {
  case PieceName::ROOK:
    title.append("Rook ");
    break;
  case PieceName::BISHOP:
    title.append("Bishop ");
    break;
  case PieceName::KNIGHT:
    title.append("Knight ");
    break;
  case PieceName::QUEEN:
    title.append("Queen ");
    break;
  case PieceName::KING:
    title.append("King ");
    break;
  case PieceName::PAWN:
    title.append("Pawn ");
    break;
  case PieceName::UNDEFINED:
    break;
  default:
    break;
  }

  if (this->player == Player::BLACK)
    title.append("Black");
  else
    title.append("White");

  title.append(" (").append(position.toString()).append(")");

  return title;
}
