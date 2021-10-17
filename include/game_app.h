#pragma once

enum class Piece
{
  BLACK_BISHOP,
  BLACK_KING,
  BLACK_KNIGHT,
  BLACK_PAWN,
  BLACK_QUEEN,
  BLACK_ROCK,
  WHITE_BISHOP,
  WHITE_KING,
  WHITE_KNIGHT,
  WHITE_PAWN,
  WHITE_QUEEN,
  WHITE_ROCK,
};

class GameApp
{
  static GameApp* instance;

  GameApp();

public:

  static GameApp* getInstance();

  static void start();

  GameApp(GameApp& other) = delete;

  void operator=(const GameApp& other) = delete;


};
