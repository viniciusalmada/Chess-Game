#pragma once
#include <array>
#include <coordinate.h>
#include <functional>
#include "piece.h"

enum class CommandType { SHOW_OPTIONS, CONFIRM };

class GameApp
{
  static std::array<Piece, 32> piecesData;

  static bool gameChanged;

  Player currentPlayer = Player::WHITE;

  CommandType currentCommandType = CommandType::SHOW_OPTIONS;

  Piece* currentSelectedPiece = nullptr;

  void checkSelectedPiece(SquarePosition pos);

  bool checkPieceOfCurrentPlayer() const;

  void confirmPieceSelected(); 

public:
  const static int SQUARES_COUNT = 64;
  const static int PIECES_COUNT = 32;

  GameApp();

  static void forEachPiece(const std::function<void(const Piece& p)>& fun);

  static bool getChanged();

  static void setChanged(bool changed);

  bool processAction(SquarePosition pos);
};