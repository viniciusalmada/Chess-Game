#include "board.h"
#include <GL/glew.h>
#include <gl_utils.h>
#include <string>
#include <image_loader.h>
#include <app.h>
#include <log.h>

Color Board::sBackgroundColor = { 0xE8E6E4 };
Color Board::sHouseDark = { 0xB58863 };
Color Board::sHouseLight = { 0xF0D9B5 };
Color Board::sHighlightPiece = { 0xfc4d02 };

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

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      int sq = innerBorder() / 8;
      int x = i * sq + mBorderSize;
      int y = j * sq + mBorderSize;
      mSquaresCoordinates[{ i, 7 - j }] = { x, y };
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

  GlUtils::uglViewportAndOrtho(mSideSize);

  drawBackground(mSideSize);

  drawSquares();

  drawPieces(game);
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

void Board::drawSquares()
{
  for (const auto& square : mSquaresCoordinates)
  {
    int i = square.first.rankId();
    int j = square.first.fileId();

    if ((i + j) % 2 == 0)
      GlUtils::uglColor3f(sHouseDark);
    else
      GlUtils::uglColor3f(sHouseLight);

    int x = square.second.x();
    int y = square.second.y();

    GlUtils::drawSquare(x, y, squareSize());
  }
}

void Board::drawPieces(const GameApp& game)
{
  game.forEachPiece([this](const Piece& piece)
    {
      Coordinate coords = mSquaresCoordinates[piece.getPosition()];
      GlUtils::Texture tex;
      if (piece.isBlack())
        tex = mTexturesBlack[piece.getName()];
      else
        tex = mTexturesWhite[piece.getName()];
      int x = coords.x();
      int y = coords.y();
      int sq = squareSize();

      if (!piece.isSelected())
        GlUtils::draw2DTexture(tex.id, x, y, sq);
      else
      {
        //GlUtils::draw2DTexture(tex.id, x, y, sq, sHighlightPiece);
        //GlUtils::draw2DTexture(tex.id, x, y, sq, sHighlightPiece);
        //Log::logDebug("Piece " + piece.generateTitle() + " is selected");
      }
    });
}

void Board::drawBackground(const int& s)
{
  GlUtils::uglColor3f(sBackgroundColor);
  GlUtils::drawSquare(0, 0, s);
}
