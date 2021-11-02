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

std::set<SquarePosition> Piece::possibleMovements()
{
  return std::set<SquarePosition>();
}

RookPiece::RookPiece(Player player, SquarePosition position) : Piece(PieceName::ROOK, player, position)
{
}

std::set<SquarePosition> RookPiece::possibleMovements()
{
  std::set<SquarePosition> moves;
  auto squaresHor = position.getAllOnRank();
  auto squaresVer = position.getAllOnFile();
  moves.insert(squaresHor.begin(), squaresHor.end());
  moves.insert(squaresVer.begin(), squaresVer.end());
  moves.erase(position);
  return moves;
}

BishopPiece::BishopPiece(Player player, SquarePosition position) : Piece(PieceName::BISHOP, player, position)
{
}

std::set<SquarePosition> BishopPiece::possibleMovements()
{
  std::set<SquarePosition> moves;
  auto allOnSWtoNE = position.getAllOnSWtoNE();
  auto allOnNWtoSE = position.getAllOnNWtoSE();
  moves.insert(allOnSWtoNE.begin(), allOnSWtoNE.end());
  moves.insert(allOnNWtoSE.begin(), allOnNWtoSE.end());
  moves.erase(position);
  return moves;
}

KnightPiece::KnightPiece(Player player, SquarePosition position) : Piece(PieceName::KNIGHT, player, position)
{
}

std::set<SquarePosition> KnightPiece::possibleMovements()
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

QueenPiece::QueenPiece(Player player, SquarePosition position) : Piece(PieceName::QUEEN, player, position)
{
}

std::set<SquarePosition> QueenPiece::possibleMovements()
{
  RookPiece rookAuxiliar{ Player::WHITE, position };
  BishopPiece bishopAuxiliar{ Player::WHITE, position };
  auto rookMovements = rookAuxiliar.possibleMovements();
  auto bishopMovements = bishopAuxiliar.possibleMovements();
  std::set<SquarePosition> moves;
  moves.insert(rookMovements.begin(), rookMovements.end());
  moves.insert(bishopMovements.begin(), bishopMovements.end());
  moves.erase(position);
  return moves;
}

KingPiece::KingPiece(Player player, SquarePosition position) : Piece(PieceName::KING, player, position)
{
}

std::set<SquarePosition> KingPiece::possibleMovements()
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

PawnPiece::PawnPiece(Player player, SquarePosition position) : Piece(PieceName::PAWN, player, position)
{
}

std::set<SquarePosition> PawnPiece::possibleMovements()
{
  return std::set<SquarePosition>();
}
