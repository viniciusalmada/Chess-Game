#include "piece.h"

Piece::Piece()
{
  this->name = PieceName::UNDEFINED;
  this->player = Player::WHITE;
  this->position = { File::F_UNDEF, Rank::R_UNDEF };
}

Piece::Piece(PieceName name, Player player, SquarePosition position)
{
  this->name = name;
  this->player = player;
  this->position = position;
}

bool Piece::operator<(const Piece& other) const
{
  return this->name < other.getName();
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
