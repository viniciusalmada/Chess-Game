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
    { PieceName::BLACK_ROOK_LEFT, Player::BLACK, { File::F_A, Rank::R_8 } },
    { PieceName::BLACK_KNIGHT_LEFT, Player::BLACK, { File::F_B, Rank::R_8 } },
    { PieceName::BLACK_BISHOP_LEFT, Player::BLACK, { File::F_C, Rank::R_8 } },
    { PieceName::BLACK_QUEEN, Player::BLACK, { File::F_D, Rank::R_8 } },
    { PieceName::BLACK_KING, Player::BLACK, { File::F_E, Rank::R_8 } },
    { PieceName::BLACK_BISHOP_RIGHT, Player::BLACK, { File::F_F, Rank::R_8 } },
    { PieceName::BLACK_KNIGHT_RIGHT, Player::BLACK, { File::F_G, Rank::R_8 } },
    { PieceName::BLACK_ROOK_RIGHT, Player::BLACK, { File::F_H, Rank::R_8 } },
    { PieceName::BLACK_PAWN_1, Player::BLACK, { File::F_A, Rank::R_7 } },
    { PieceName::BLACK_PAWN_2, Player::BLACK, { File::F_B, Rank::R_7 } },
    { PieceName::BLACK_PAWN_3, Player::BLACK, { File::F_C, Rank::R_7 } },
    { PieceName::BLACK_PAWN_4, Player::BLACK, { File::F_D, Rank::R_7 } },
    { PieceName::BLACK_PAWN_5, Player::BLACK, { File::F_E, Rank::R_7 } },
    { PieceName::BLACK_PAWN_6, Player::BLACK, { File::F_F, Rank::R_7 } },
    { PieceName::BLACK_PAWN_7, Player::BLACK, { File::F_G, Rank::R_7 } },
    { PieceName::BLACK_PAWN_8, Player::BLACK, { File::F_H, Rank::R_7 } },
    { PieceName::WHITE_ROOK_LEFT, Player::WHITE, { File::F_A, Rank::R_1 } },
    { PieceName::WHITE_KNIGHT_LEFT, Player::WHITE, { File::F_B, Rank::R_1 } },
    { PieceName::WHITE_BISHOP_LEFT, Player::WHITE, { File::F_C, Rank::R_1 } },
    { PieceName::WHITE_QUEEN, Player::WHITE, { File::F_D, Rank::R_1 } },
    { PieceName::WHITE_KING, Player::WHITE, { File::F_E, Rank::R_1 } },
    { PieceName::WHITE_BISHOP_RIGHT, Player::WHITE, { File::F_F, Rank::R_1 } },
    { PieceName::WHITE_KNIGHT_RIGHT, Player::WHITE, { File::F_G, Rank::R_1 } },
    { PieceName::WHITE_ROOK_RIGHT, Player::WHITE, { File::F_H, Rank::R_1 } },
    { PieceName::WHITE_PAWN_1, Player::WHITE, { File::F_A, Rank::R_2 } },
    { PieceName::WHITE_PAWN_2, Player::WHITE, { File::F_B, Rank::R_2 } },
    { PieceName::WHITE_PAWN_3, Player::WHITE, { File::F_C, Rank::R_2 } },
    { PieceName::WHITE_PAWN_4, Player::WHITE, { File::F_D, Rank::R_2 } },
    { PieceName::WHITE_PAWN_5, Player::WHITE, { File::F_E, Rank::R_2 } },
    { PieceName::WHITE_PAWN_6, Player::WHITE, { File::F_F, Rank::R_2 } },
    { PieceName::WHITE_PAWN_7, Player::WHITE, { File::F_G, Rank::R_2 } },
    { PieceName::WHITE_PAWN_8, Player::WHITE, { File::F_H, Rank::R_2 } },
  };
}

void GameApp::forEachPiece(const std::function<void(Piece)>& fun) const
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
