#pragma once
#include <unordered_map>
#include "gl_utils.h"
#include "game_app.h"

class Board
{
  const int mBorderSize = 10;
  int mSideSize;

  std::unordered_map<Piece, GlUtils::Texture> mTextures;

  void loadTextures();

  void forEachSquare(std::function<void(int, int, Coordinate)> fun);

public:
  static int sBackgroundColor;
  static int sHouseDark;
  static int sHouseLight;

  Board(int sideSize);

  int getSideSize() const;

  void drawBoard();
  void drawBackground(const int& s);
};

