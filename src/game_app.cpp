#include "game_app.h"

void GameApp::checkSelectedPiece(SquarePosition pos)
{
  currentSelectedPiece = Piece::UNDEFINED;
  for (const auto& piece : mPiecesPositions)
  {
    if (piece.second == pos)
    {
      currentSelectedPiece = piece.first;
      break;
    }
  }
}

GameApp::GameApp()
{
  mPiecesPositions =
  {
    { Piece::BLACK_ROOK_LEFT, { File::F_A, Rank::R_8 } },
    { Piece::BLACK_KNIGHT_LEFT, { File::F_B, Rank::R_8 } },
    { Piece::BLACK_BISHOP_LEFT, { File::F_C, Rank::R_8 } },
    { Piece::BLACK_QUEEN, { File::F_D, Rank::R_8 } },
    { Piece::BLACK_KING, { File::F_E, Rank::R_8 } },
    { Piece::BLACK_BISHOP_RIGHT, { File::F_F, Rank::R_8 } },
    { Piece::BLACK_KNIGHT_RIGHT, { File::F_G, Rank::R_8 } },
    { Piece::BLACK_ROOK_RIGHT, { File::F_H, Rank::R_8 } },
    { Piece::BLACK_PAWN_1, { File::F_A, Rank::R_7 } },
    { Piece::BLACK_PAWN_2, { File::F_B, Rank::R_7 } },
    { Piece::BLACK_PAWN_3, { File::F_C, Rank::R_7 } },
    { Piece::BLACK_PAWN_4, { File::F_D, Rank::R_7 } },
    { Piece::BLACK_PAWN_5, { File::F_E, Rank::R_7 } },
    { Piece::BLACK_PAWN_6, { File::F_F, Rank::R_7 } },
    { Piece::BLACK_PAWN_7, { File::F_G, Rank::R_7 } },
    { Piece::BLACK_PAWN_8, { File::F_H, Rank::R_7 } },
    { Piece::WHITE_ROOK_LEFT, { File::F_A, Rank::R_1 } },
    { Piece::WHITE_KNIGHT_LEFT, { File::F_B, Rank::R_1 } },
    { Piece::WHITE_BISHOP_LEFT, { File::F_C, Rank::R_1 } },
    { Piece::WHITE_QUEEN, { File::F_D, Rank::R_1 } },
    { Piece::WHITE_KING, { File::F_E, Rank::R_1 } },
    { Piece::WHITE_BISHOP_RIGHT, { File::F_F, Rank::R_1 } },
    { Piece::WHITE_KNIGHT_RIGHT, { File::F_G, Rank::R_1 } },
    { Piece::WHITE_ROOK_RIGHT, { File::F_H, Rank::R_1 } },
    { Piece::WHITE_PAWN_1, { File::F_A, Rank::R_2 } },
    { Piece::WHITE_PAWN_2, { File::F_B, Rank::R_2 } },
    { Piece::WHITE_PAWN_3, { File::F_C, Rank::R_2 } },
    { Piece::WHITE_PAWN_4, { File::F_D, Rank::R_2 } },
    { Piece::WHITE_PAWN_5, { File::F_E, Rank::R_2 } },
    { Piece::WHITE_PAWN_6, { File::F_F, Rank::R_2 } },
    { Piece::WHITE_PAWN_7, { File::F_G, Rank::R_2 } },
    { Piece::WHITE_PAWN_8, { File::F_H, Rank::R_2 } },
  };
}

void GameApp::forEachPiece(const std::function<void(Piece, SquarePosition)>& fun) const
{
  for (const auto& p : mPiecesPositions)
  {
    fun(p.first, p.second);
  }
}

bool GameApp::processAction(SquarePosition pos)
{
  checkSelectedPiece(pos);
  if (currentSelectedPiece == Piece::UNDEFINED)
    return false;

  return true;
}
