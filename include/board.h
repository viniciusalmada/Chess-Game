#pragma once
#include <unordered_map>
#include "gl_utils.h"

class Board
{
  const int mBorderSize = 10;
  int mSideSize;

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

  std::unordered_map<Piece, GlUtils::Texture> mTextures;

  void loadTextures();

public:
  static int sBackgroundColor;
  static int sHouseDark;
  static int sHouseLight;

  Board(int sideSize);

  int getSideSize() const;

  void drawBoard();
};

