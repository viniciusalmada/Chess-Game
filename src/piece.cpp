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
  for (int i = 0; i < 8; i++)
  {
    moves.insert({ static_cast<File>(i), position.getRank() });
    moves.insert({ position.getFile(), static_cast<Rank>(i) });
  }
  moves.erase(position);
  return moves;
}

BishopPiece::BishopPiece(Player player, SquarePosition position) : Piece(PieceName::BISHOP, player, position)
{
}

std::set<SquarePosition> BishopPiece::possibleMovements()
{
  std::set<SquarePosition> moves;
  return std::set<SquarePosition>();
}

KnightPiece::KnightPiece(Player player, SquarePosition position) : Piece(PieceName::KNIGHT, player, position)
{
}

std::set<SquarePosition> KnightPiece::possibleMovements()
{
  return std::set<SquarePosition>();
}

QueenPiece::QueenPiece(Player player, SquarePosition position) : Piece(PieceName::QUEEN, player, position)
{
}

std::set<SquarePosition> QueenPiece::possibleMovements()
{
  return std::set<SquarePosition>();
}

KingPiece::KingPiece(Player player, SquarePosition position) : Piece(PieceName::KING, player, position)
{
}

std::set<SquarePosition> KingPiece::possibleMovements()
{
  return std::set<SquarePosition>();
}

PawnPiece::PawnPiece(Player player, SquarePosition position) : Piece(PieceName::PAWN, player, position)
{
}

std::set<SquarePosition> PawnPiece::possibleMovements()
{
  return std::set<SquarePosition>();
}
