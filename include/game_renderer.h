#pragma once
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include <hash_utl.h>
#include "game_app.h"
#include <renderer.h>
#include <texture.h>

class GameRenderer
{
private:

  struct Coordinate
  {
    float x;
    float y;
  };

  struct Color
  {
    float red;
    float green;
    float blue;
  };

  struct TexCoords
  {
    float s;
    float t;
  };

  struct SquareVertexData
  {
    Coordinate coord;
    Color color;
  };

  struct SquareData
  {
    SquareVertexData topLeft;
    SquareVertexData topRight;
    SquareVertexData botRight;
    SquareVertexData botLeft;

    void setMargin(float size)
    {
      topLeft.coord.x += size;
      topLeft.coord.y += size;

      topRight.coord.x -= size;
      topRight.coord.y += size;

      botRight.coord.x -= size;
      botRight.coord.y -= size;

      botLeft.coord.x += size;
      botLeft.coord.y -= size;
    }
  };

  struct PieceVertexData
  {
    SquareVertexData square;
    TexCoords texCoords;
    int id;
    int isBlack;
  };

  struct TextureData
  {
    GLObj::Texture texture;
    std::string name;
    int id;
  };

  const static float BORDER_SIZE_RELATIVE;
  const static float PIECE_MARGIN;

  const static std::string TEX_NAME_BISHOP;
  const static std::string TEX_NAME_KING;
  const static std::string TEX_NAME_KNIGHT;
  const static std::string TEX_NAME_PAWN;
  const static std::string TEX_NAME_QUEEN;
  const static std::string TEX_NAME_ROOK;

  std::unordered_map<PieceName, TextureData> textures;
  std::unordered_map<SquarePosition, SquareData, SquarePositionHash, SquarePositionEqual> squaresCoordinates;

  GLObj::Renderer boardRenderer;
  GLObj::Renderer piecesRenderer;

  void loadTextures();

  std::vector<SquareData> fillCoordinates();

  float innerBorder() const { return WINDOW_SIZE * BORDER_SIZE_RELATIVE / (WINDOW_SIZE / 2.0F); }
  float squareSize() const { return (2.0F - (2 * innerBorder())) / 8.0F; }

  void drawBoard();
  void drawPieces();

  GLObj::RendererData generateBoardRendererData(std::filesystem::path shadersPath);
  GLObj::RendererData generatePiecesRendererData(std::filesystem::path shadersPath);

  void updatePieces();

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

