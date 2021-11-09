#include "board.h"
#include <GL/glew.h>
#include <gl_utils.h>
#include <string>
#include <image_loader.h>
#include <app.h>
#include <log.h>

GlUtils::Color Board::sBackgroundColor = { 0xE8E6E4 };
GlUtils::Color Board::sSquareDark = { 0xB58863 };
GlUtils::Color Board::sSquareLight = { 0xF0D9B5 };
GlUtils::Color Board::sHighlightPiece = { 0xfc4d02 };

static GlUtils::Texture _loadTexture(std::string str)
{
  std::string path = App::getImagePath(str).generic_string();
  auto* img = ImageLoader::load(path);
  return GlUtils::createTexture2D(img);
}

void Board::loadTextures()
{
  if (!mTexturesBlack.empty() && !mTexturesWhite.empty())
    return;

  mTexturesBlack[PieceName::BISHOP] = _loadTexture("img_bishop_black.png");
  mTexturesBlack[PieceName::KING] = _loadTexture("img_king_black.png");
  mTexturesBlack[PieceName::KNIGHT] = _loadTexture("img_knight_black.png");
  mTexturesBlack[PieceName::PAWN] = _loadTexture("img_pawn_black.png");
  mTexturesBlack[PieceName::QUEEN] = _loadTexture("img_queen_black.png");
  mTexturesBlack[PieceName::ROOK] = _loadTexture("img_rook_black.png");
  mTexturesWhite[PieceName::BISHOP] = _loadTexture("img_bishop_white.png");
  mTexturesWhite[PieceName::KING] = _loadTexture("img_king_white.png");
  mTexturesWhite[PieceName::KNIGHT] = _loadTexture("img_knight_white.png");
  mTexturesWhite[PieceName::PAWN] = _loadTexture("img_pawn_white.png");
  mTexturesWhite[PieceName::QUEEN] = _loadTexture("img_queen_white.png");
  mTexturesWhite[PieceName::ROOK] = _loadTexture("img_rook_white.png");
}

void Board::fillCoordinates()
{
  if (!mSquaresCoordinates.empty()) return;

  mBufferData.addSquare({
    { 0, 0 },
    { getSideSize(), 0 },
    { getSideSize(), getSideSize() },
    { 0, getSideSize() },
    sBackgroundColor
    });

  bool useDark = true;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; i < 8; i++)
    {
      int sq = innerBorder() / 8;
      int x = i * sq + mBorderSize;
      int y = j * sq + mBorderSize;
      Coordinate topLeft{ x, y };
      Coordinate topRight{ x + sq, y };
      Coordinate botRight{ x + sq, y + sq };
      Coordinate botLeft{ x, y + sq };
      auto color = useDark ? sSquareDark : sSquareLight;
      int id = mBufferData.addSquare({ topLeft, topRight, botRight, botLeft, color });
      mSquaresCoordinates[{i, 7 - j}] = id;
      useDark = !useDark;
    }
  }
}

Board::Board(int sideSize) : mSideSize(sideSize)
{
}

int Board::getSideSize() const
{
  return mSideSize;
}

void Board::drawBoard(const GameApp& game)
{
  loadTextures();

  fillCoordinates();

  glViewport(0, 0, mSideSize, mSideSize);

  draw();

  //drawSquares();

  //drawPieces(game);
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
  
}
