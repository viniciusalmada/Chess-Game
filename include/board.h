#pragma once
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include <hash_utl.h>
#include "game_app.h"
#include "gl_utils.h"

class Board
{
  int mBorderSize = 10;
  int mSideSize;

  std::unordered_map<PieceName, GlUtils::Texture> mTexturesBlack;
  std::unordered_map<PieceName, GlUtils::Texture> mTexturesWhite;
  std::unordered_map<SquarePosition, int, SquarePositionHash, SquarePositionEqual> mSquaresCoordinates;

  GlUtils::BufferData mBufferData;

  void loadTextures();

  void fillCoordinates();

  int innerBorder() { return mSideSize - 2 * mBorderSize; }
  int squareSize() { return innerBorder() / 8; }

  int getSideSize() const;

  void draw();

public:
  const static int PREDEFINED_SIZE = 600;

  static GlUtils::Color sBackgroundColor;
  static GlUtils::Color sSquareDark;
  static GlUtils::Color sSquareLight;
  static GlUtils::Color sHighlightPiece;

  explicit Board();

  void drawBoard();

  SquarePosition getSelectedSquare(int x, int y);
};

