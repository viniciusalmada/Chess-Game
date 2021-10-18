#include "board.h"
#include <GL/glew.h>
#include <gl_utils.h>
#include <string>
#include <image_loader.h>
#include <app.h>

int Board::sBackgroundColor = 0xE8E6E4;
int Board::sHouseDark = 0xB58863;
int Board::sHouseLight = 0xF0D9B5;

static GlUtils::Texture _loadTexture(std::string str)
{
  std::string path = App::getImagePath(str);
  auto* img = ImageLoader::load(path);
  return GlUtils::createTexture2D(img);
}

void Board::loadTextures()
{
  if (!mTextures.empty())
    return;

  mTextures[Piece::BLACK_BISHOP_LEFT] =
    mTextures[Piece::BLACK_BISHOP_RIGHT] = _loadTexture("img_bishop_black.png");
  mTextures[Piece::BLACK_KING] = _loadTexture("img_king_black.png");
  mTextures[Piece::BLACK_KNIGHT_LEFT] =
    mTextures[Piece::BLACK_KNIGHT_RIGHT] = _loadTexture("img_knight_black.png");
  mTextures[Piece::BLACK_PAWN_1] =
    mTextures[Piece::BLACK_PAWN_2] =
    mTextures[Piece::BLACK_PAWN_3] =
    mTextures[Piece::BLACK_PAWN_4] =
    mTextures[Piece::BLACK_PAWN_5] =
    mTextures[Piece::BLACK_PAWN_6] =
    mTextures[Piece::BLACK_PAWN_7] =
    mTextures[Piece::BLACK_PAWN_8] = _loadTexture("img_pawn_black.png");
  mTextures[Piece::BLACK_QUEEN] = _loadTexture("img_queen_black.png");
  mTextures[Piece::BLACK_ROOK_LEFT] =
    mTextures[Piece::BLACK_ROOK_RIGHT] = _loadTexture("img_rook_black.png");
  mTextures[Piece::WHITE_BISHOP_LEFT] =
    mTextures[Piece::WHITE_BISHOP_RIGHT] = _loadTexture("img_bishop_white.png");
  mTextures[Piece::WHITE_KING] = _loadTexture("img_king_white.png");
  mTextures[Piece::WHITE_KNIGHT_LEFT] =
    mTextures[Piece::WHITE_KNIGHT_RIGHT] = _loadTexture("img_knight_white.png");
  mTextures[Piece::WHITE_PAWN_1] =
    mTextures[Piece::WHITE_PAWN_2] =
    mTextures[Piece::WHITE_PAWN_3] =
    mTextures[Piece::WHITE_PAWN_4] =
    mTextures[Piece::WHITE_PAWN_5] =
    mTextures[Piece::WHITE_PAWN_6] =
    mTextures[Piece::WHITE_PAWN_7] =
    mTextures[Piece::WHITE_PAWN_8] = _loadTexture("img_pawn_white.png");
  mTextures[Piece::WHITE_QUEEN] = _loadTexture("img_queen_white.png");
  mTextures[Piece::WHITE_ROOK_LEFT] =
    mTextures[Piece::WHITE_ROOK_RIGHT] = _loadTexture("img_rook_white.png");
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
      mSquaresCoordinates[{ i, j}] = { x, y };
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

void Board::drawBoard()
{
  loadTextures();

  fillCoordinates();

  GlUtils::uglViewportAndOrtho(mSideSize);

  drawBackground(mSideSize);

  drawSquares();

  drawPieces();
}

void Board::drawSquares()
{
  for (const auto& square : mSquaresCoordinates)
  {
    int i = square.first.first;
    int j = square.first.second;

    if ((i + j) % 2 == 0)
      GlUtils::uglColor3d(sHouseDark);
    else
      GlUtils::uglColor3d(sHouseLight);

    int x = square.second.x();
    int y = square.second.y();

    GlUtils::drawSquare(x, y, squareSize());
  }
}

void Board::drawPieces()
{
  GameApp::forEachPiece([this](Piece p, int i, int j)
    {
      Coordinate coords = mSquaresCoordinates[{i, j}];
      GlUtils::Texture tex = mTextures[p];
      int x = coords.x();
      int y = coords.y();
      int sq = squareSize();

      GlUtils::draw2DTexture(tex.id, x, y, sq);
    });
}

void Board::drawBackground(const int& s)
{
  GlUtils::uglColor3d(sBackgroundColor);
  GlUtils::drawSquare(0, 0, s);
}
