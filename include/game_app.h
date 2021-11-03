#pragma once
#include <array>
#include <coordinate.h>
#include <functional>
#include "piece.h"

enum class CommandType { SHOW_OPTIONS, CONFIRM };

class GameApp
{
  std::array<Piece, 32> mPieces;

  Player currentPlayer = Player::WHITE;

  CommandType currentCommandType = CommandType::SHOW_OPTIONS;

  Piece* currentSelectedPiece = nullptr;

  void checkSelectedPiece(SquarePosition pos);

  bool checkPieceOfCurrentPlayer() const;

  void confirmPieceSelected(); 

public:

  GameApp();

  void forEachPiece(const std::function<void(const Piece& p)>& fun) const;

  bool processAction(SquarePosition pos);
};