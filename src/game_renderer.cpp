#include "game_renderer.h"
#include <string>
#include <image_loader.h>
#include <app.h>
#include <log.h>
#include <numeric_utils.h>

Color GameRenderer::backgroundColor = { 0xE8, 0xE6, 0xE4 };
Color GameRenderer::squareDark = { 0xB5, 0x88, 0x63 };
Color GameRenderer::squareLight = { 0xF0, 0xD9, 0xB5 };
Color GameRenderer::highlightPiece = { 0xfc, 0x4d, 0x02 };

const std::string GameRenderer::TEX_NAME_BISHOP = "bishopTex";
const std::string GameRenderer::TEX_NAME_KING = "kingTex";
const std::string GameRenderer::TEX_NAME_KNIGHT = "knightTex";
const std::string GameRenderer::TEX_NAME_PAWN = "pawnTex";
const std::string GameRenderer::TEX_NAME_QUEEN = "queenTex";
const std::string GameRenderer::TEX_NAME_ROOK = "rookTex";

const float GameRenderer::BORDER_SIZE_RELATIVE = 0.02F;
const float GameRenderer::PIECE_MARGIN = 0.02F;

static GLObj::Texture _loadTex(std::string str)
{
  std::string path = App::getImagePath(str).generic_string();
  return { path };
}

void GameRenderer::loadTextures()
{
  if (!textures.empty())
    return;

  textures[PieceName::BISHOP] = { _loadTex("img_king.png"), TEX_NAME_BISHOP, 1 };
  textures[PieceName::KING] = { _loadTex("img_bishop.png"), TEX_NAME_KING, 2 };
  textures[PieceName::KNIGHT] = { _loadTex("img_knight.png"), TEX_NAME_KNIGHT, 3 };
  textures[PieceName::PAWN] = { _loadTex("img_pawn.png"), TEX_NAME_PAWN, 4 };
  textures[PieceName::QUEEN] = { _loadTex("img_queen.png"), TEX_NAME_QUEEN, 5 };
  textures[PieceName::ROOK] = { _loadTex("img_rook.png"), TEX_NAME_ROOK, 6 };
}

std::vector<GameRenderer::SquareData> GameRenderer::fillCoordinates()
{
  std::vector<GameRenderer::SquareData> coordinates{};
  if (!squaresCoordinates.empty()) return coordinates;

  bool useDark = false;
  float step = squareSize();
  float startPos = -1.0F + innerBorder();
  float endPos = 1.0F - innerBorder();
  int fileId = (int)File::F_A;
  for (float x = startPos; x < endPos; x += step)
  {
    int rankId = (int)Rank::R_1;
    for (float y = startPos; y < endPos; y += step)
    {
      Coordinate topLeft{ x, y };
      Coordinate topRight{ x + step, y };
      Coordinate botRight{ x + step, y + step };
      Coordinate botLeft{ x, y + step };
      auto color = useDark ? squareDark : squareLight;
      auto colorsF = color.getColorsNormalized();
      Color colorRGB{ colorsF[0], colorsF[1], colorsF[2] };

      SquareVertexData vTopLeft{ topLeft, colorRGB };
      SquareVertexData vTopRight{ topRight, colorRGB };
      SquareVertexData vBotRight{ botRight, colorRGB };
      SquareVertexData vBotLeft{ botLeft, colorRGB };

      SquarePosition position{ fileId, rankId };
      SquareData square{ vTopLeft, vTopRight, vBotRight, vBotLeft };

      squaresCoordinates.insert({ position, square });
      coordinates.push_back(square);

      useDark = !useDark;
      rankId++;
    }
    useDark = !useDark;
    fileId++;
  }

  return coordinates;
}

GameRenderer::GameRenderer(std::filesystem::path shadersPath) :
  boardRenderer(generateBoardRendererData(shadersPath)),
  piecesRenderer(generatePiecesRendererData(shadersPath))
{
}

void GameRenderer::draw()
{
  drawBoard();
  drawPieces();
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
  this->boardRenderer.draw();
}

void GameRenderer::drawPieces()
{
  updatePieces();
  this->piecesRenderer.draw();
}

GLObj::RendererData GameRenderer::generateBoardRendererData(std::filesystem::path shadersPath)
{
  GLObj::VertexBufferLayout vbl{};
  vbl.pushFloat(2); // positions
  vbl.pushFloat(3); // colors

  std::vector<GameRenderer::SquareData> data = fillCoordinates();
  unsigned int totalSize = (int)data.size() * sizeof(GameRenderer::SquareData);
  GLObj::VertexBuffer vb{ data.data(), totalSize };

  GLObj::VertexArray va{ vb, vbl };

  GLObj::Shader shader{ shadersPath, "boardVertex.glsl", "boardFragment.glsl" };

  unsigned int currentIndex = 0;
  std::vector<unsigned int> indexData = NumericUtils::genIndices(64);

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

  return { va, ib, shader };
}

GLObj::RendererData GameRenderer::generatePiecesRendererData(std::filesystem::path shadersPath)
{
  loadTextures();

  GLObj::VertexBufferLayout vbl{};
  vbl.pushFloat(2); // positions
  vbl.pushFloat(3); // color
  vbl.pushFloat(2); // tex
  vbl.pushInt(1); // id
  vbl.pushInt(1); // isBlack

  const auto& squareA8 = squaresCoordinates[{File::F_A, Rank::R_8}];
  const auto& squareA7 = squaresCoordinates[{File::F_A, Rank::R_7}];
  const float s = BORDER_SIZE_RELATIVE;
  /*std::vector<PieceVertexData> data;
  data.push_back({ squareA8.topLeft, 1.0f, 0.0f, 0 });
  data.push_back({ squareA8.topRight, 0.0f, 0.0f, 0 });
  data.push_back({ squareA8.botRight,0.0f, 1.0f, 0 });
  data.push_back({ squareA8.botLeft,1.0f, 1.0f, 0 });

  data.push_back({ squareA7.topLeft, 1.0f, 0.0f, 1 });
  data.push_back({ squareA7.topRight, 0.0f, 0.0f, 1 });
  data.push_back({ squareA7.botRight,0.0f, 1.0f, 1 });
  data.push_back({ squareA7.botLeft,1.0f, 1.0f, 1 });*/
  //unsigned int totalSize = (int)data.size() * sizeof(GameRenderer::PieceVertexData);
  const unsigned int numPieces = 32;
  const unsigned int verticesPerPiece = 4;
  const unsigned int vbSize = numPieces * verticesPerPiece * sizeof(GameRenderer::PieceVertexData);

  GLObj::VertexBuffer vb{ nullptr, vbSize };

  GLObj::VertexArray va{ vb, vbl };

  GLObj::Shader shader{ shadersPath, "piecesVertex.glsl", "piecesFragment.glsl" };

  std::vector<unsigned int> indexData = NumericUtils::genIndices(numPieces);

  GLObj::IndexBuffer ib{ indexData.data(), (unsigned int)indexData.size() };

  textures[PieceName::BISHOP].texture.bind(GL_TEXTURE0);
  textures[PieceName::KING].texture.bind(GL_TEXTURE1);
  textures[PieceName::KNIGHT].texture.bind(GL_TEXTURE2);
  textures[PieceName::PAWN].texture.bind(GL_TEXTURE3);
  textures[PieceName::QUEEN].texture.bind(GL_TEXTURE4);
  textures[PieceName::ROOK].texture.bind(GL_TEXTURE5);

  shader.bind();
  shader.setUniform1i(TEX_NAME_BISHOP, 0);
  shader.setUniform1i(TEX_NAME_KING, 1);
  shader.setUniform1i(TEX_NAME_KNIGHT, 2);
  shader.setUniform1i(TEX_NAME_PAWN, 3);
  shader.setUniform1i(TEX_NAME_QUEEN, 4);
  shader.setUniform1i(TEX_NAME_ROOK, 5);
  shader.unbind();

  return { va, ib, shader };
}

void GameRenderer::updatePieces()
{
  if (!GameApp::getChanged()) return;

  std::vector<PieceVertexData> data;
  GameApp::forEachPiece([&](const Piece& piece)
    {
      SquareData piecePosition = squaresCoordinates[piece.getPosition()];
      piecePosition.setMargin(PIECE_MARGIN);
      data.push_back({ piecePosition.topLeft, {1.0f, 0.0f},  textures[piece.getName()].id, piece.isBlack() });
      data.push_back({ piecePosition.topRight, {0.0f, 0.0f},  textures[piece.getName()].id, piece.isBlack() });
      data.push_back({ piecePosition.botRight, {0.0f, 1.0f},  textures[piece.getName()].id, piece.isBlack() });
      data.push_back({ piecePosition.botLeft, {1.0f, 1.0f},  textures[piece.getName()].id, piece.isBlack() });
    });
  GameApp::setChanged(false);
  piecesRenderer.updateVertexBuffer(data.data());
}
