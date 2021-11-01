#pragma once
#include <set>
#include <coordinate.h>
#include <functional>
#include "piece.h"

enum class CommandType { SHOW_OPTIONS, CONFIRM };

class GameApp
{
  std::set<Piece> mPieces;

  Player currentPlayer = Player::WHITE;

  CommandType currentCommandType = CommandType::SHOW_OPTIONS;

  Piece currentSelectedPiece{};

  void checkSelectedPiece(SquarePosition pos);

  bool checkPieceOfCurrentPlayer();

public:

  GameApp();

  void forEachPiece(const std::function<void(Piece)>& fun) const;

  bool processAction(SquarePosition pos);
};