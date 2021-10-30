#pragma once
#include <unordered_map>
#include <coordinate.h>
#include <functional>
#include <memory>

enum class Piece
{
  BLACK_ROOK_LEFT,
  BLACK_BISHOP_LEFT,
  BLACK_KNIGHT_LEFT,
  BLACK_QUEEN,
  BLACK_KING,
  BLACK_KNIGHT_RIGHT,
  BLACK_BISHOP_RIGHT,
  BLACK_ROOK_RIGHT,
  BLACK_PAWN_1,
  BLACK_PAWN_2,
  BLACK_PAWN_3,
  BLACK_PAWN_4,
  BLACK_PAWN_5,
  BLACK_PAWN_6,
  BLACK_PAWN_7,
  BLACK_PAWN_8,
  WHITE_ROOK_LEFT,
  WHITE_BISHOP_LEFT,
  WHITE_KNIGHT_LEFT,
  WHITE_QUEEN,
  WHITE_KING,
  WHITE_KNIGHT_RIGHT,
  WHITE_BISHOP_RIGHT,
  WHITE_ROOK_RIGHT,
  WHITE_PAWN_1,
  WHITE_PAWN_2,
  WHITE_PAWN_3,
  WHITE_PAWN_4,
  WHITE_PAWN_5,
  WHITE_PAWN_6,
  WHITE_PAWN_7,
  WHITE_PAWN_8,
};

class GameApp
{
  static std::shared_ptr<GameApp> instance;

  GameApp();
   
  std::unordered_map<Piece, std::pair<int, int>> mPiecesPositions;

  void initPiecesCoordinates();

public:

  static void start();

  static std::shared_ptr<GameApp> getInstance();

  static void forEachPiece(const std::function<void(Piece, int, int)>& fun);

  GameApp(GameApp& other) = delete;

  void operator=(const GameApp& other) = delete;
};