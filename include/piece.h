#pragma once
#include <set>
#include <string>
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
  bool isFirstPawnMovement = true;

  std::set<SquarePosition> rookPossibleMovements() const;
  std::set<SquarePosition> bishopPossibleMovements() const;
  std::set<SquarePosition> knightPossibleMovements() const;
  std::set<SquarePosition> queenPossibleMovements() const;
  std::set<SquarePosition> kingPossibleMovements() const;
  std::set<SquarePosition> pawnPossibleMovements() const;

public:
  Piece();

  Piece(PieceName name, Player player, SquarePosition position);

  bool operator<(const Piece& other) const;

  bool operator==(const Piece& other) const;

  bool equalPosition(SquarePosition pos) const;

  bool isUndefined() const;

  bool isBlack() const;

  bool isWhite() const;

  SquarePosition getPosition() const;

  PieceName getName() const;

  bool isSelected() const;

  void select() { selected = true; }

  void unselect() { selected = false; }

  virtual std::set<SquarePosition> possibleMovements() const;

  std::string generateTitle() const;
};

