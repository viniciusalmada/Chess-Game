#pragma once
#include <unordered_map>
#include <coordinate.h>
#include <functional>

enum class Piece
{
  BLACK_ROCK_LEFT,
  BLACK_BISHOP_LEFT,
  BLACK_KNIGHT_LEFT,
  BLACK_QUEEN,
  BLACK_KING,
  BLACK_KNIGHT_RIGHT,
  BLACK_BISHOP_RIGHT,
  BLACK_ROCK_RIGHT,
  BLACK_PAWN_1,
  BLACK_PAWN_2,
  BLACK_PAWN_3,
  BLACK_PAWN_4,
  BLACK_PAWN_5,
  BLACK_PAWN_6,
  BLACK_PAWN_7,
  BLACK_PAWN_8,
  WHITE_ROCK_LEFT,
  WHITE_BISHOP_LEFT,
  WHITE_KNIGHT_LEFT,
  WHITE_QUEEN,
  WHITE_KING,
  WHITE_KNIGHT_RIGHT,
  WHITE_BISHOP_RIGHT,
  WHITE_ROCK_RIGHT,
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
  static GameApp* instance;

  GameApp();

  std::unordered_map<Piece, Coordinate> mPiecesPositions;

  void initPiecesCoordinates();

public:

  static GameApp* getInstance();

  static void start();

  static void forEachPiece(std::function<void(std::pair<Piece, Coordinate>)> fun);

  GameApp(GameApp& other) = delete;

  void operator=(const GameApp& other) = delete;
};
