#pragma once
#include <unordered_map>
#include "gl_utils.h"
#include "game_app.h"
#include <vector>
#include <unordered_set>
#include <hash_utl.h>

class Board
{

  const int mBorderSize = 10;
  int mSideSize;

  std::unordered_map<Piece, GlUtils::Texture> mTextures;
  std::unordered_map<std::pair<int, int>, Coordinate, PairIntIntHash> mSquaresCoordinates;

  void loadTextures();

  void fillCoordinates();

public:
  static int sBackgroundColor;
  static int sHouseDark;
  static int sHouseLight;

  Board(int sideSize);

  int getSideSize() const;

  void drawBoard();
  void drawSquares();
  void drawBackground(const int& s);
};

