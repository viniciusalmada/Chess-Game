#include "game_app.h"

GameApp::GameApp()
{
  mPiecesPositions =
  {
    { Piece::BLACK_ROOK_LEFT, { 0 ,0 } },
    { Piece::BLACK_KNIGHT_LEFT, { 1 ,0 } },
    { Piece::BLACK_BISHOP_LEFT, { 2 ,0 } },
    { Piece::BLACK_QUEEN, { 3 ,0 } },
    { Piece::BLACK_KING, { 4 ,0 } },
    { Piece::BLACK_BISHOP_RIGHT, { 5 ,0 } },
    { Piece::BLACK_KNIGHT_RIGHT, { 6 ,0 } },
    { Piece::BLACK_ROOK_RIGHT, { 7 ,0 } },
    { Piece::BLACK_PAWN_1, { 0 ,1 } },
    { Piece::BLACK_PAWN_2, { 1 ,1 } },
    { Piece::BLACK_PAWN_3, { 2 ,1 } },
    { Piece::BLACK_PAWN_4, { 3 ,1 } },
    { Piece::BLACK_PAWN_5, { 4 ,1 } },
    { Piece::BLACK_PAWN_6, { 5 ,1 } },
    { Piece::BLACK_PAWN_7, { 6 ,1 } },
    { Piece::BLACK_PAWN_8, { 7 ,1 } },
    { Piece::WHITE_ROOK_LEFT, { 0 ,7 } },
    { Piece::WHITE_KNIGHT_LEFT, { 1 ,7 } },
    { Piece::WHITE_BISHOP_LEFT, { 2 ,7 } },
    { Piece::WHITE_QUEEN, { 3 ,7 } },
    { Piece::WHITE_KING, { 4 ,7 } },
    { Piece::WHITE_BISHOP_RIGHT, { 5 ,7 } },
    { Piece::WHITE_KNIGHT_RIGHT, { 6 ,7 } },
    { Piece::WHITE_ROOK_RIGHT, { 7 ,7 } },
    { Piece::WHITE_PAWN_1, { 0 ,6 } },
    { Piece::WHITE_PAWN_2, { 1 ,6 } },
    { Piece::WHITE_PAWN_3, { 2 ,6 } },
    { Piece::WHITE_PAWN_4, { 3 ,6 } },
    { Piece::WHITE_PAWN_5, { 4 ,6 } },
    { Piece::WHITE_PAWN_6, { 5 ,6 } },
    { Piece::WHITE_PAWN_7, { 6 ,6 } },
    { Piece::WHITE_PAWN_8, { 7 ,6 } },
  };
}

void GameApp::forEachPiece(const std::function<void(Piece, int, int)>& fun) const
{
  for (const auto& p : mPiecesPositions)
  {
    fun(p.first, p.second.first, p.second.second);
  }
}