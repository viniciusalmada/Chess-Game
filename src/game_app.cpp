#include "game_app.h"

void GameApp::checkSelectedPiece(SquarePosition pos)
{
  currentSelectedPiece = Piece();
  for (const auto& piece : mPieces)
  {
    if (!piece.equalPosition(pos))
      continue;
    currentSelectedPiece = piece;
    break;
  }
}

bool GameApp::checkPieceOfCurrentPlayer()
{
  if (currentSelectedPiece.isUndefined()) return false;

  if (currentPlayer == Player::BLACK)
  {
    return currentSelectedPiece.isBlack();
  }
  else
  {
    return currentSelectedPiece.isWhite();
  }
}

GameApp::GameApp()
{
  mPieces =
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

void GameApp::forEachPiece(const std::function<void(const Piece& p)>& fun) const
{
  for (const auto& p : mPieces)
  {
    fun(p);
  }
}

bool GameApp::processAction(SquarePosition pos)
{
  checkSelectedPiece(pos);
  if (currentSelectedPiece.isUndefined())
    return false;

  bool toContinue = checkPieceOfCurrentPlayer();
  if (!toContinue)
    return false;

  return true;
}
