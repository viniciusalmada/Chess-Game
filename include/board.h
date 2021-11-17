#pragma once
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include <hash_utl.h>
#include "game_app.h"
#include "gl_utils.h"

class Board
{
  const static int BORDER_SIZE = 10;

  std::unordered_map<PieceName, GlUtils::Texture> texturesBlack;
  std::unordered_map<PieceName, GlUtils::Texture> texturesWhite;
  std::unordered_map<SquarePosition, int, SquarePositionHash, SquarePositionEqual> squaresCoordinates;

  GlUtils::BufferData bufferData;

  void loadTextures();

  void fillCoordinates();

  int innerBorder() { return WINDOW_SIZE - 2 * BORDER_SIZE; }
  int squareSize() { return innerBorder() / 8; }

  void draw();

public:
  const static int WINDOW_SIZE = 600;

  static GlUtils::Color backgroundColor;
  static GlUtils::Color squareDark;
  static GlUtils::Color squareLight;
  static GlUtils::Color highlightPiece;

  explicit Board();

  void drawBoard();

  SquarePosition getSelectedSquare(int x, int y);
};

