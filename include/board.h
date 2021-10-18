#pragma once
#include <unordered_map>
#include "gl_utils.h"
#include "game_app.h"
#include <vector>

class Board
{
  struct SquareCoordinate
  {
    int i;
    int j;
    Coordinate c;
  };

  const int mBorderSize = 10;
  int mSideSize;

  std::unordered_map<Piece, GlUtils::Texture> mTextures;
  std::vector<SquareCoordinate> mSquaresCoordinates;

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

