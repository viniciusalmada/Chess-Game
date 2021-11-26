#pragma once
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include <hash_utl.h>
#include "game_app.h"
#include "gl_utils.h"
#include <renderer.h>
#include <texture.h>

class GameRenderer
{
private:

  struct SquareData
  {
    float x;
    float y;
    float r;
    float g;
    float b;
  };

  const static float BORDER_SIZE_RELATIVE;

  std::unordered_map<PieceName, GLObj::Texture> textures;
  std::unordered_map<SquarePosition, SquareCoordinates, SquarePositionHash, SquarePositionEqual> squaresCoordinates;

  GLObj::Renderer renderer;

  void loadTextures();

  std::vector<SquareData> fillCoordinates();

  float innerBorder() const { return WINDOW_SIZE * BORDER_SIZE_RELATIVE / (WINDOW_SIZE / 2.0F); }
  float squareSize() const { return (2.0F - (2*innerBorder())) / 8.0F; }

  void drawBoard();

  GLObj::RendererData generateData(std::filesystem::path shadersPath);

public:
  const static int WINDOW_SIZE = 600;

  static GlUtils::Color backgroundColor;
  static GlUtils::Color squareDark;
  static GlUtils::Color squareLight;
  static GlUtils::Color highlightPiece;

  explicit GameRenderer(std::filesystem::path shadersPath);

  void draw();

  SquarePosition getSelectedSquare(int x, int y);
};

