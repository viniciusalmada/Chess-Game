#pragma once
#include <set>
#include "player.h"
#include "coordinate.h"

enum class PieceName
{
  ROOK,
  BISHOP,
  KNIGHT,
  QUEEN,
  KING,
  PAWN,
  UNDEFINED,
};

class Piece
{
protected:
  PieceName name;
  Player player;
  SquarePosition position;
  bool selected;

  Piece(PieceName name, Player player, SquarePosition position);

public:
  Piece();

  bool operator<(const Piece& other) const;

  bool operator==(const Piece& other) const;

  bool equalPosition(SquarePosition pos) const;

  bool isUndefined() const;

  bool isBlack() const;

  bool isWhite() const;

  SquarePosition getPosition() const;

  PieceName getName() const;

  bool isSelected() const;

  virtual std::set<SquarePosition> possibleMovements();
};

class RookPiece : public Piece
{
public:
  RookPiece(Player player, SquarePosition position);

  std::set<SquarePosition> possibleMovements() override;
};

class BishopPiece : public Piece
{
public:
  BishopPiece(Player player, SquarePosition position);

  std::set<SquarePosition> possibleMovements() override;
};

class KnightPiece : public Piece
{
public:
  KnightPiece(Player player, SquarePosition position);

  std::set<SquarePosition> possibleMovements() override;
};

class QueenPiece : public Piece
{
public:
  QueenPiece(Player player, SquarePosition position);

  std::set<SquarePosition> possibleMovements() override;
};

class KingPiece : public Piece
{
public:
  KingPiece(Player player, SquarePosition position);

  std::set<SquarePosition> possibleMovements() override;
};

class PawnPiece : public Piece
{
public:
  PawnPiece(Player player, SquarePosition position);

  std::set<SquarePosition> possibleMovements() override;
};