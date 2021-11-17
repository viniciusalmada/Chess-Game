#include "board.h"
#include <GL/glew.h>
#include <gl_utils.h>
#include <string>
#include <image_loader.h>
#include <app.h>
#include <log.h>

GlUtils::Color Board::backgroundColor = { 0xE8E6E4 };
GlUtils::Color Board::squareDark = { 0xB58863 };
GlUtils::Color Board::squareLight = { 0xF0D9B5 };
GlUtils::Color Board::highlightPiece = { 0xfc4d02 };

static GlUtils::Texture _loadTexture(std::string str)
{
  std::string path = App::getImagePath(str).generic_string();
  auto* img = ImageLoader::load(path);
  return GlUtils::createTexture2D(img);
}

void Board::loadTextures()
{
  if (!texturesBlack.empty() && !texturesWhite.empty())
    return;

  texturesBlack[PieceName::BISHOP] = _loadTexture("img_bishop_black.png");
  texturesBlack[PieceName::KING] = _loadTexture("img_king_black.png");
  texturesBlack[PieceName::KNIGHT] = _loadTexture("img_knight_black.png");
  texturesBlack[PieceName::PAWN] = _loadTexture("img_pawn_black.png");
  texturesBlack[PieceName::QUEEN] = _loadTexture("img_queen_black.png");
  texturesBlack[PieceName::ROOK] = _loadTexture("img_rook_black.png");
  texturesWhite[PieceName::BISHOP] = _loadTexture("img_bishop_white.png");
  texturesWhite[PieceName::KING] = _loadTexture("img_king_white.png");
  texturesWhite[PieceName::KNIGHT] = _loadTexture("img_knight_white.png");
  texturesWhite[PieceName::PAWN] = _loadTexture("img_pawn_white.png");
  texturesWhite[PieceName::QUEEN] = _loadTexture("img_queen_white.png");
  texturesWhite[PieceName::ROOK] = _loadTexture("img_rook_white.png");
}

void Board::fillCoordinates()
{
  if (!squaresCoordinates.empty()) return;

  bufferData.addSquare({
    Coordinate{ 0, 0 },
    Coordinate{ WINDOW_SIZE, 0 },
    Coordinate{ WINDOW_SIZE, WINDOW_SIZE },
    Coordinate{ 0, WINDOW_SIZE },
    backgroundColor
    });

  bool useDark = true;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      int sq = innerBorder() / 8;
      int x = i * sq + BORDER_SIZE;
      int y = j * sq + BORDER_SIZE;
      Coordinate topLeft{ x, y };
      Coordinate topRight{ x + sq, y };
      Coordinate botRight{ x + sq, y + sq };
      Coordinate botLeft{ x, y + sq };
      auto color = useDark ? squareDark : squareLight;
      int id = bufferData.addSquare({ topLeft, topRight, botRight, botLeft, color });
      squaresCoordinates[{i, 7 - j}] = id;
      useDark = !useDark;
    }
    useDark = !useDark;
  }
}

Board::Board()
{
  fillCoordinates();
}

void Board::drawBoard()
{
  bufferData.loadBuffers(WINDOW_SIZE);

  draw();
}

SquarePosition Board::getSelectedSquare(int x, int y)
{
  int fileId = 0;
  while (fileId < 8)
  {
    if (x < squareSize())
      break;
    x -= squareSize();
    fileId++;
  }

  int rankId = 0;
  while (rankId < 8)
  {
    if (y < squareSize())
      break;
    y -= squareSize();
    rankId++;
  }
  rankId = 7 - rankId;

  return SquarePosition(fileId, rankId);
}

void Board::draw()
{
  GlUtils::drawElements(bufferData.getIndicesSize());
}
