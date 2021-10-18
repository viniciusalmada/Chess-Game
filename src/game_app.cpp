#include "game_app.h"

GameApp* GameApp::instance = nullptr;

GameApp::GameApp()
{
  initPiecesCoordinates();
}

GameApp* GameApp::getInstance()
{
  return instance;
}

void GameApp::start()
{
  if (instance == nullptr)
  {
    instance = new GameApp();
  }
}

void GameApp::forEachPiece(std::function<void(Piece, int, int)> fun)
{
  const auto& pieces = getInstance()->mPiecesPositions;
  for (const auto p : pieces)
  {
    fun(p.first, p.second.first, p.second.second);
  }
}

void GameApp::initPiecesCoordinates()
{
  if (!mPiecesPositions.empty())
    return;

  mPiecesPositions[Piece::BLACK_ROCK_LEFT] = { 0,0 };
  mPiecesPositions[Piece::BLACK_KNIGHT_LEFT] = { 1,0 };
  mPiecesPositions[Piece::BLACK_BISHOP_LEFT] = { 2,0 };
  mPiecesPositions[Piece::BLACK_QUEEN] = { 3,0 };
  mPiecesPositions[Piece::BLACK_KING] = { 4,0 };
  mPiecesPositions[Piece::BLACK_BISHOP_RIGHT] = { 5,0 };
  mPiecesPositions[Piece::BLACK_KNIGHT_RIGHT] = { 6,0 };
  mPiecesPositions[Piece::BLACK_ROCK_RIGHT] = { 7,0 };
  mPiecesPositions[Piece::BLACK_PAWN_1] = { 0,1 };
  mPiecesPositions[Piece::BLACK_PAWN_2] = { 1,1 };
  mPiecesPositions[Piece::BLACK_PAWN_3] = { 2,1 };
  mPiecesPositions[Piece::BLACK_PAWN_4] = { 3,1 };
  mPiecesPositions[Piece::BLACK_PAWN_5] = { 4,1 };
  mPiecesPositions[Piece::BLACK_PAWN_6] = { 5,1 };
  mPiecesPositions[Piece::BLACK_PAWN_7] = { 6,1 };
  mPiecesPositions[Piece::BLACK_PAWN_8] = { 7,1 };
  mPiecesPositions[Piece::WHITE_ROCK_LEFT] = { 0,7 };
  mPiecesPositions[Piece::WHITE_KNIGHT_LEFT] = { 1,7 };
  mPiecesPositions[Piece::WHITE_BISHOP_LEFT] = { 2,7 };
  mPiecesPositions[Piece::WHITE_QUEEN] = { 3,7 };
  mPiecesPositions[Piece::WHITE_KING] = { 4,7 };
  mPiecesPositions[Piece::WHITE_BISHOP_RIGHT] = { 5,7 };
  mPiecesPositions[Piece::WHITE_KNIGHT_RIGHT] = { 6,7 };
  mPiecesPositions[Piece::WHITE_ROCK_RIGHT] = { 7,7 };
  mPiecesPositions[Piece::WHITE_PAWN_1] = { 0,6 };
  mPiecesPositions[Piece::WHITE_PAWN_2] = { 1,6 };
  mPiecesPositions[Piece::WHITE_PAWN_3] = { 2,6 };
  mPiecesPositions[Piece::WHITE_PAWN_4] = { 3,6 };
  mPiecesPositions[Piece::WHITE_PAWN_5] = { 4,6 };
  mPiecesPositions[Piece::WHITE_PAWN_6] = { 5,6 };
  mPiecesPositions[Piece::WHITE_PAWN_7] = { 6,6 };
  mPiecesPositions[Piece::WHITE_PAWN_8] = { 7,6 };
}