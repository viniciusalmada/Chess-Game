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

  mTextures[Piece::BLACK_BISHOP] = _loadTexture("img_bishop_black.png");
  mTextures[Piece::BLACK_KING] = _loadTexture("img_king_black.png");
  mTextures[Piece::BLACK_KNIGHT] = _loadTexture("img_knight_black.png");
  mTextures[Piece::BLACK_PAWN] = _loadTexture("img_pawn_black.png");
  mTextures[Piece::BLACK_QUEEN] = _loadTexture("img_queen_black.png");
  mTextures[Piece::BLACK_ROCK] = _loadTexture("img_rock_black.png");
  mTextures[Piece::WHITE_BISHOP] = _loadTexture("img_bishop_white.png");
  mTextures[Piece::WHITE_KING] = _loadTexture("img_knight_white.png");
  mTextures[Piece::WHITE_KNIGHT] = _loadTexture("img_king_white.png");
  mTextures[Piece::WHITE_PAWN] = _loadTexture("img_pawn_white.png");
  mTextures[Piece::WHITE_QUEEN] = _loadTexture("img_queen_white.png");
  mTextures[Piece::WHITE_ROCK] = _loadTexture("img_rock_white.png");
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

  const int& s = mSideSize;

  glViewport(0, 0, s, s);
  glLoadIdentity();
  glOrtho(0, s, s, 0, -1.0, 1.0);

  glBegin(GL_QUADS);
  GlUtils::uglColor3d(sBackgroundColor);
  glVertex2d(0, 0);
  glVertex2d(s, 0);
  glVertex2d(s, s);
  glVertex2d(0, s);
  glEnd();

  int ib = mSideSize - 2 * mBorderSize;
  bool useDark = true;
  for (int i = 0; i < 8; i++)
  {
    bool aux = useDark;
    for (int j = 0; j < 8; j++)
    {
      int sq = ib / 8;
      int x = i * sq + mBorderSize;
      int y = j * sq + mBorderSize;

      GlUtils::uglColor3d(useDark ? sHouseDark : sHouseLight);

      glBegin(GL_QUADS);
      glVertex2i(x, y);
      glVertex2i(x + sq, y);
      glVertex2i(x + sq, y + sq);
      glVertex2i(x, y + sq);
      glEnd();

      if (i == 0 && j == 0)
      {
        int gap = sq * 1.0 / 24.0;
        glBindTexture(GL_TEXTURE_2D, 0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mTextures[Piece::BLACK_QUEEN].id);
        GlUtils::uglColor3d(GlUtils::WHITE);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(x + gap, y + gap);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(x + sq - gap, y + gap);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(x + sq - gap, y + sq - gap);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(x + gap, y + sq - gap);
        glEnd();
        glDisable(GL_TEXTURE_2D);
      }

      useDark = !useDark;
    }
    useDark = !aux;
    aux = useDark;
  }
}
