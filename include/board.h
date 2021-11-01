#pragma once
#include <unordered_map>
#include "gl_utils.h"
#include <vector>
#include <unordered_set>

#include <hash_utl.h>
#include "game_app.h"

class Board
{
  int mBorderSize = 10;
  int mSideSize;

  std::unordered_map<PieceName, GlUtils::Texture> mTextures;
  std::unordered_map<SquarePosition, Coordinate, SquarePositionHash, SquarePositionEqual> mSquaresCoordinates;

  void loadTextures();

  void fillCoordinates();

  int innerBorder() { return mSideSize - 2 * mBorderSize; }
  int squareSize() { return innerBorder() / 8; }

  int getSideSize() const;

  void drawSquares();
  void drawBackground(const int& s);
  void drawPieces(const GameApp& game);

public:
  static int sBackgroundColor;
  static int sHouseDark;
  static int sHouseLight;

  explicit Board(int sideSize = 600);

  void drawBoard(const GameApp& game);

  SquarePosition getSelectedSquare(int x, int y);
};

