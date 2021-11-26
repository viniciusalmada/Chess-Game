#include <GL/glew.h>
#include "game_renderer.h"
#include <gl_utils.h>
#include <string>
#include <image_loader.h>
#include <app.h>
#include <log.h>

GlUtils::Color GameRenderer::backgroundColor = { 0xE8E6E4 };
GlUtils::Color GameRenderer::squareDark = { 0xB58863 };
GlUtils::Color GameRenderer::squareLight = { 0xF0D9B5 };
GlUtils::Color GameRenderer::highlightPiece = { 0xfc4d02 };

const float GameRenderer::BORDER_SIZE_RELATIVE = 0.02F;

static GLObj::Texture _loadTexture(std::string str, unsigned int slot)
{
  std::string path = App::getImagePath(str).generic_string();
  return { path, slot};
}

void GameRenderer::loadTextures()
{
  if (!textures.empty())
    return;

  textures[PieceName::BISHOP] = _loadTexture("img_bishop_black.png", GL_TEXTURE0);
  textures[PieceName::KING] = _loadTexture("img_king_black.png", GL_TEXTURE1);
  textures[PieceName::KNIGHT] = _loadTexture("img_knight_black.png", GL_TEXTURE2);
  textures[PieceName::PAWN] = _loadTexture("img_pawn_black.png", GL_TEXTURE3);
  textures[PieceName::QUEEN] = _loadTexture("img_queen_black.png", GL_TEXTURE4);
  textures[PieceName::ROOK] = _loadTexture("img_rook_black.png", GL_TEXTURE5);
}

std::vector<GameRenderer::SquareData> GameRenderer::fillCoordinates()
{
  //if (!squaresCoordinates.empty()) return;

  std::vector<GameRenderer::SquareData> coordinates{};

  bool useDark = false;
  float step = squareSize();
  float startPos = -1.0F + innerBorder();
  float endPos = 1.0F - innerBorder();
  int count = 0;
  for (float x = startPos; x < endPos; x += step)
  {
    for (float y = startPos; y < endPos; y += step)
    {
      Coordinate topLeft{ x, y };
      Coordinate topRight{ x + step, y };
      Coordinate botRight{ x + step, y + step };
      Coordinate botLeft{ x, y + step };
      auto color = useDark ? squareDark : squareLight;
      auto colorsF = color.getColorsF();
      coordinates.push_back({ topLeft.getX(), topLeft.getY(), colorsF[0], colorsF[1], colorsF[2] });
      coordinates.push_back({ topRight.getX(), topRight.getY(), colorsF[0], colorsF[1], colorsF[2] });
      coordinates.push_back({ botRight.getX(), botRight.getY(), colorsF[0], colorsF[1], colorsF[2] });
      coordinates.push_back({ botLeft.getX(), botLeft.getY(), colorsF[0], colorsF[1], colorsF[2] });
      useDark = !useDark;
      count++;
    }
    useDark = !useDark;
  }

  return coordinates;
}

GameRenderer::GameRenderer(std::filesystem::path shadersPath) : renderer(generateData(shadersPath))
{
}

void GameRenderer::draw()
{
  //bufferData.loadBuffers(WINDOW_SIZE);

  drawBoard();
}

SquarePosition GameRenderer::getSelectedSquare(int x, int y)
{
  int fileId = 0;
  /* while (fileId < 8)
   {
     if (x < squareSize())
       break;
     x -= squareSize();
     fileId++;
   }*/

  int rankId = 0;
  /* while (rankId < 8)
   {
     if (y < squareSize())
       break;
     y -= squareSize();
     rankId++;
   }*/
  rankId = 7 - rankId;

  return SquarePosition(fileId, rankId);
}

void GameRenderer::drawBoard()
{
  this->renderer.draw();
  //GlUtils::drawElements(bufferData.getIndicesSize());
}

GLObj::RendererData GameRenderer::generateData(std::filesystem::path shadersPath)
{
  GLObj::VertexBufferLayout vbl{};
  vbl.pushFloat(2); // positions
  vbl.pushFloat(3); // colors

  std::vector<GameRenderer::SquareData> data = fillCoordinates();
  unsigned int totalSize = (int)data.size() * 5 * sizeof(float);
  GLObj::VertexBuffer vb{ data.data(), totalSize };

  GLObj::VertexArray va{ vb, vbl };

  GLObj::Shader shader{ shadersPath, "vertex.glsl", "fragment.glsl" };

  unsigned int currentIndex = 0;
  std::vector<unsigned int> indexData{};
  for (int i = 0; i < 64; i++)
  {
    unsigned int i0 = currentIndex;
    unsigned int i1 = currentIndex + 1;
    unsigned int i2 = currentIndex + 2;
    unsigned int i3 = currentIndex + 3;
    indexData.push_back(i0);
    indexData.push_back(i1);
    indexData.push_back(i2);

    indexData.push_back(i2);
    indexData.push_back(i3);
    indexData.push_back(i0);
    currentIndex += 4;
  }

  GLObj::IndexBuffer ib{ indexData.data(), (unsigned int)indexData.size() };

  //GLObj::VertexBufferLayout vbl{};
  //vbl.pushFloat(2); // positions
  //vbl.pushFloat(3); // colors

  //std::vector<float> positions = {
  //   -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
  //  0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
  //  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  //};
  //unsigned int totalSize = 3 * 5 * sizeof(float);
  //GLObj::VertexBuffer vb{ positions.data(), totalSize };

  //GLObj::VertexArray va;
  //va.addBuffer(vb, vbl);

  //GLObj::Shader shader{ shadersPath };

  //std::vector<unsigned int> indexData = { 0, 1, 2 };
  //GLObj::IndexBuffer ib{ indexData.data(), (unsigned int)indexData.size() };

  return { backgroundColor, va, ib, shader };
}
