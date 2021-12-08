#pragma once
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include <hash_utl.h>
#include "game_app.h"
#include <renderer.h>
#include <texture.h>
#include <color.h>
#include <square_data.h>
#include <texture_data.h>

class GameRenderer
{
private:  
  const static int POSITION_NUM_COUNT;
  const static int COLOR_NUM_COUNT;
  const static int TEXTURE_NUM_COUNT;
  const static int TEXTURE_ID_NUM_COUNT;
  const static int PIECE_COLOR_NUM_COUNT;
  const static int POSITIONS_PER_SQUARE;

  const static float BORDER_SIZE_RELATIVE;
  const static float PIECE_MARGIN;

  const static std::string TEX_NAME_BISHOP;
  const static std::string TEX_NAME_KING;
  const static std::string TEX_NAME_KNIGHT;
  const static std::string TEX_NAME_PAWN;
  const static std::string TEX_NAME_QUEEN;
  const static std::string TEX_NAME_ROOK;

  std::unordered_map<PieceName, TextureData> textures;
  std::unordered_map<SquarePosition, Square, SquarePositionHash, SquarePositionEqual> squaresCoordinates;

  GLObj::Renderer boardRenderer;
  GLObj::Renderer piecesRenderer;

  void loadTextures();

  void fillCoordinates();

  float innerBorder() const { return WINDOW_SIZE * BORDER_SIZE_RELATIVE / (WINDOW_SIZE / 2.0F); }
  float squareSize() const { return (2.0F - (2 * innerBorder())) / 8.0F; }

  void drawBoard();
  void drawPieces();

  GLObj::RendererData generateBoardRendererData(std::filesystem::path shadersPath);
  GLObj::RendererData generatePiecesRendererData(std::filesystem::path shadersPath);

  void setBoardPositions();
  void updatePieces();

public:
  const static int WINDOW_SIZE = 600;

  static Color backgroundColor;
  static Color squareDark;
  static Color squareLight;
  static Color highlightPiece;

  explicit GameRenderer(std::filesystem::path shadersPath);

  void draw();

  SquarePosition getSelectedSquare(int x, int y);
};

