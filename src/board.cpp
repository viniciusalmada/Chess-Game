#include "board.h"
#include <GL/glew.h>
#include <gl_utils.h>

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
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, s, s, 0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glShadeModel(GL_SMOOTH);

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

      glBegin(GL_QUADS);
      GlUtils::uglColor3d(useDark ? sHouseDark : sHouseLight);
      glVertex2i(x, y);
      glVertex2i(x + sq, y);
      glVertex2i(x + sq, y + sq);
      glVertex2i(x, y + sq);
      glEnd();
      
      useDark = !useDark;
    }
    useDark = !aux;
    aux = useDark;
  }
}
