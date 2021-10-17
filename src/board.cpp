#include "board.h"
#include <GL/glew.h>
#include <gl_utils.h>
#include <string>
#include <image_loader.h>
#include <app.h>

int Board::sBackgroundColor = 0xE8E6E4;
int Board::sHouseDark = 0xB58863;
int Board::sHouseLight = 0xF0D9B5;

Board::Board(int sideSize) : mSideSize(sideSize)
{
}

int Board::getSideSize() const
{
  return mSideSize;
}

void Board::drawBoard()
{
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

  std::string path = App::getImagePath("polygon.png");
  auto* img = ImageLoader::load(path);
  unsigned int textureId = GlUtils::createTexture2D(img);

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
        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId);
        GlUtils::uglColor3d(GlUtils::WHITE);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(x, y);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(x + sq, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(x + sq, y + sq);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(x, y + sq);
        glEnd();
        glDisable(GL_TEXTURE_2D);
      }

      useDark = !useDark;
    }
    useDark = !aux;
    aux = useDark;
  }
}
