#include "piece.h"

Piece::Piece()
{
  this->name = PieceName::UNDEFINED;
  this->player = Player::WHITE;
  this->position = { File::F_UNDEF, Rank::R_UNDEF };
  this->isSelected = false;
}

Piece::Piece(PieceName name, Player player, SquarePosition position)
{
  this->name = name;
  this->player = player;
  this->position = position;
  this->isSelected = false;
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

std::vector<SquarePosition> Piece::possibleMovements()
{
  return std::vector<SquarePosition>();
}

RookPiece::RookPiece(Player player, SquarePosition position) : Piece(PieceName::ROOK, player, position)
{
}

std::vector<SquarePosition> RookPiece::possibleMovements()
{

  return std::vector<SquarePosition>();
}

BishopPiece::BishopPiece(Player player, SquarePosition position) : Piece(PieceName::BISHOP, player, position)
{
}

std::vector<SquarePosition> BishopPiece::possibleMovements()
{
  return std::vector<SquarePosition>();
}

KnightPiece::KnightPiece(Player player, SquarePosition position) : Piece(PieceName::KNIGHT, player, position)
{
}

std::vector<SquarePosition> KnightPiece::possibleMovements()
{
  return std::vector<SquarePosition>();
}

QueenPiece::QueenPiece(Player player, SquarePosition position) : Piece(PieceName::QUEEN, player, position)
{
}

std::vector<SquarePosition> QueenPiece::possibleMovements()
{
  return std::vector<SquarePosition>();
}

KingPiece::KingPiece(Player player, SquarePosition position) : Piece(PieceName::KING, player, position)
{
}

std::vector<SquarePosition> KingPiece::possibleMovements()
{
  return std::vector<SquarePosition>();
}

PawnPiece::PawnPiece(Player player, SquarePosition position) : Piece(PieceName::PAWN, player, position)
{
}

std::vector<SquarePosition> PawnPiece::possibleMovements()
{
  return std::vector<SquarePosition>();
}
