#include "game_app.h"

std::array<Piece, 32> GameApp::piecesData{};
bool GameApp::gameChanged = true;

void GameApp::checkSelectedPiece(SquarePosition pos)
{
  if (currentSelectedPiece != nullptr)
    currentSelectedPiece->unselect();

  currentSelectedPiece = nullptr;
  for (Piece& piece : piecesData)
  {
    if (!piece.equalPosition(pos))
      continue;
    currentSelectedPiece = &piece;
    break;
  }
}

bool GameApp::checkPieceOfCurrentPlayer() const
{
  if (currentSelectedPiece == nullptr) return false;

  if (currentPlayer == Player::BLACK)
  {
    return currentSelectedPiece->isBlack();
  }
  else
  {
    return currentSelectedPiece->isWhite();
  }
}

void GameApp::confirmPieceSelected()
{
  currentSelectedPiece->select();
}

GameApp::GameApp()
{
  piecesData =
  {
    RookPiece{ Player::BLACK, { File::F_A, Rank::R_8 } },
    KnightPiece{ Player::BLACK, { File::F_B, Rank::R_8 } },
    BishopPiece{ Player::BLACK, { File::F_C, Rank::R_8 } },
    QueenPiece{ Player::BLACK, { File::F_D, Rank::R_8 } },
    KingPiece{ Player::BLACK, { File::F_E, Rank::R_8 } },
    BishopPiece{ Player::BLACK, { File::F_F, Rank::R_8 } },
    KnightPiece{ Player::BLACK, { File::F_G, Rank::R_8 } },
    RookPiece{ Player::BLACK, { File::F_H, Rank::R_8 } },
    PawnPiece{ Player::BLACK, { File::F_A, Rank::R_7 } },
    PawnPiece{ Player::BLACK, { File::F_B, Rank::R_7 } },
    PawnPiece{ Player::BLACK, { File::F_C, Rank::R_7 } },
    PawnPiece{ Player::BLACK, { File::F_D, Rank::R_7 } },
    PawnPiece{ Player::BLACK, { File::F_E, Rank::R_7 } },
    PawnPiece{ Player::BLACK, { File::F_F, Rank::R_7 } },
    PawnPiece{ Player::BLACK, { File::F_G, Rank::R_7 } },
    PawnPiece{ Player::BLACK, { File::F_H, Rank::R_7 } },
    RookPiece{ Player::WHITE, { File::F_A, Rank::R_1 } },
    KnightPiece{ Player::WHITE, { File::F_B, Rank::R_1 } },
    BishopPiece{ Player::WHITE, { File::F_C, Rank::R_1 } },
    QueenPiece{ Player::WHITE, { File::F_D, Rank::R_1 } },
    KingPiece{ Player::WHITE, { File::F_E, Rank::R_1 } },
    BishopPiece{ Player::WHITE, { File::F_F, Rank::R_1 } },
    KnightPiece{ Player::WHITE, { File::F_G, Rank::R_1 } },
    RookPiece{ Player::WHITE, { File::F_H, Rank::R_1 } },
    PawnPiece{ Player::WHITE, { File::F_A, Rank::R_2 } },
    PawnPiece{ Player::WHITE, { File::F_B, Rank::R_2 } },
    PawnPiece{ Player::WHITE, { File::F_C, Rank::R_2 } },
    PawnPiece{ Player::WHITE, { File::F_D, Rank::R_2 } },
    PawnPiece{ Player::WHITE, { File::F_E, Rank::R_2 } },
    PawnPiece{ Player::WHITE, { File::F_F, Rank::R_2 } },
    PawnPiece{ Player::WHITE, { File::F_G, Rank::R_2 } },
    PawnPiece{ Player::WHITE, { File::F_H, Rank::R_2 } },
  };
}

void GameApp::forEachPiece(const std::function<void(const Piece& p)>& fun)
{
  for (const auto& p : piecesData)
  {
    fun(p);
  }
}

void GameApp::forEachSquare(const std::function<void(const SquarePosition& p)>& fun)
{
  for (int fileId = (int)File::F_A; fileId < 8; fileId++)
  {
    for (int rankId = (int)Rank::R_1; rankId < 8; rankId++)
    {
      fun({ fileId, rankId });
    }
  }
}

bool GameApp::getChanged()
{
  return gameChanged;
}

void GameApp::setChanged(bool changed)
{
  gameChanged = changed;
}

bool GameApp::processAction(SquarePosition pos)
{
  checkSelectedPiece(pos);
  if (currentSelectedPiece == nullptr)
    return false;

  bool toContinue = checkPieceOfCurrentPlayer();
  if (!toContinue)
    return false;

  if (currentCommandType == CommandType::SHOW_OPTIONS)
    confirmPieceSelected();

  return true;
}
