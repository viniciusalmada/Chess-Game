#include "game_renderer.h"
#include <string>
#include <image_loader.h>
#include <app.h>
#include <log.h>
#include <numeric_utils.h>

static float _normalize(const int& num)
{
  return (num * 2.0F) / static_cast<float>(GameRenderer::WINDOW_SIZE);
}

const int GameRenderer::POSITION_NUM_COUNT = 2;
const int GameRenderer::COLOR_NUM_COUNT = 4;
const int GameRenderer::TEXTURE_NUM_COUNT = 2;
const int GameRenderer::TEXTURE_ID_NUM_COUNT = 1;
const int GameRenderer::PIECE_COLOR_NUM_COUNT = 1;
const int GameRenderer::POSITIONS_PER_SQUARE = 4;

const float GameRenderer::BORDER_SIZE_RELATIVE = 0.02F;
const float GameRenderer::PIECE_MARGIN = 0.02F;

const std::string GameRenderer::TEX_NAME_BISHOP = "bishopTex";
const std::string GameRenderer::TEX_NAME_KING = "kingTex";
const std::string GameRenderer::TEX_NAME_KNIGHT = "knightTex";
const std::string GameRenderer::TEX_NAME_PAWN = "pawnTex";
const std::string GameRenderer::TEX_NAME_QUEEN = "queenTex";
const std::string GameRenderer::TEX_NAME_ROOK = "rookTex";

Color GameRenderer::backgroundColor = { 0xE8, 0xE6, 0xE4 };
Color GameRenderer::squareDark = { 0xB5, 0x88, 0x63 };
Color GameRenderer::squareLight = { 0xF0, 0xD9, 0xB5 };
Color GameRenderer::highlightPiece = { 0xfc, 0x4d, 0x02 };

void GameRenderer::loadTextures()
{
  if (!textures.empty())
    return;
  std::unordered_map<PieceName, TextureData> _textures({
    { PieceName::BISHOP, { "img_king.png", TEX_NAME_BISHOP, 1 } },
    { PieceName::KING, { "img_bishop.png", TEX_NAME_KING, 2 } },
    { PieceName::KNIGHT, { "img_knight.png", TEX_NAME_KNIGHT, 3 } },
    { PieceName::PAWN, { "img_pawn.png", TEX_NAME_PAWN, 4 } },
    { PieceName::QUEEN, { "img_queen.png", TEX_NAME_QUEEN, 5 } },
    { PieceName::ROOK, { "img_rook.png", TEX_NAME_ROOK, 6 } }
    });
  textures = std::move(_textures);
}

void GameRenderer::fillCoordinates()
{
  if (!squaresCoordinates.empty()) return;

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
      Coordinate botLeft{ x, y };
      Coordinate botRight{ x + step, y };
      Coordinate topRight{ x + step, y + step };
      Coordinate topLeft{ x, y + step };
      Color color = useDark ? squareDark : squareLight;

      Square square{ topLeft, topRight, botRight, botLeft, color };
      SquarePosition position{ fileId, rankId };

      squaresCoordinates[position] = square;

      useDark = !useDark;
      rankId++;
    }
    useDark = !useDark;
    fileId++;
  }
}

GameRenderer::GameRenderer(std::filesystem::path shadersPath) :
  boardRenderer(generateBoardRendererData(shadersPath)),
  piecesRenderer(generatePiecesRendererData(shadersPath))
{
  fillCoordinates();
  setBoardPositions();
}

void GameRenderer::draw()
{
  drawBoard();
  drawPieces();
}

SquarePosition GameRenderer::getSelectedSquare(CoordinateI position)
{
  float x = _normalize(position.getX());
  float y = _normalize(position.getY());
  float ss = squareSize();

  int fileId = 0;
  while (fileId < 8)
  {
    if (x < ss)
      break;
    x -= ss;
    fileId++;
  }

  int rankId = 0;
  while (rankId < 8)
  {
    if (y < ss)
      break;
    y -= ss;
    rankId++;
  }
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
  GLObj::VertexBufferLayout vbl = GLObj::VertexBufferLayoutBuilder{}
    .pushFloat(POSITION_NUM_COUNT)
    .pushFloat(COLOR_NUM_COUNT)
    .getLayout();

  unsigned int totalSize = GameApp::SQUARES_COUNT * POSITIONS_PER_SQUARE * vbl.getBytesCount();
  GLObj::VertexBuffer vb{ nullptr, totalSize };

  GLObj::VertexArray va{ vb, vbl };

  GLObj::Shader shader{ shadersPath, "boardVertex.glsl", "boardFragment.glsl" };

  unsigned int currentIndex = 0;
  std::vector<unsigned int> indexData = NumericUtils::genIndices(GameApp::SQUARES_COUNT);

  GLObj::IndexBuffer ib{ indexData.data(), (unsigned int)indexData.size() };

  return { va, ib, shader };
}

GLObj::RendererData GameRenderer::generatePiecesRendererData(std::filesystem::path shadersPath)
{
  loadTextures();

  GLObj::VertexBufferLayout vbl = GLObj::VertexBufferLayoutBuilder{}
    .pushFloat(POSITION_NUM_COUNT)
    .pushFloat(COLOR_NUM_COUNT)
    .pushFloat(TEXTURE_NUM_COUNT)
    .pushInt(TEXTURE_ID_NUM_COUNT)
    .pushInt(PIECE_COLOR_NUM_COUNT)
    .getLayout();


  const unsigned int vbSize = GameApp::PIECES_COUNT * POSITIONS_PER_SQUARE * vbl.getBytesCount();

  GLObj::VertexBuffer vb{ nullptr, vbSize };

  GLObj::VertexArray va{ vb, vbl };

  GLObj::Shader shader{ shadersPath, "piecesVertex.glsl", "piecesFragment.glsl" };

  std::vector<unsigned int> indexData = NumericUtils::genIndices(GameApp::PIECES_COUNT);

  GLObj::IndexBuffer ib{ indexData.data(), (unsigned int)indexData.size() };

  textures[PieceName::BISHOP].bindTexture(GL_TEXTURE0);
  textures[PieceName::KING].bindTexture(GL_TEXTURE1);
  textures[PieceName::KNIGHT].bindTexture(GL_TEXTURE2);
  textures[PieceName::PAWN].bindTexture(GL_TEXTURE3);
  textures[PieceName::QUEEN].bindTexture(GL_TEXTURE4);
  textures[PieceName::ROOK].bindTexture(GL_TEXTURE5);

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

void GameRenderer::setBoardPositions()
{
  std::vector<Square::VertexData> data;
  GameApp::forEachSquare([&](const SquarePosition& position)
    {
      Square square = squaresCoordinates[position];
      data.push_back(square.getSquareVertexData(Corner::TOP_LEFT));
      data.push_back(square.getSquareVertexData(Corner::TOP_RIGHT));
      data.push_back(square.getSquareVertexData(Corner::BOT_RIGHT));
      data.push_back(square.getSquareVertexData(Corner::BOT_LEFT));
    });
  boardRenderer.updateVertexBuffer(data.data());
}

void GameRenderer::updatePieces()
{
  if (!GameApp::getChanged()) return;

  std::vector<Square::TextureData> data;
  GameApp::forEachPiece([&](const Piece& piece)
    {
      Square piecePosition = squaresCoordinates[piece.getPosition()];
      piecePosition.setMargin(PIECE_MARGIN);
      int texId = textures[piece.getName()].getId();
      bool isBlack = piece.isBlack();
      data.push_back(piecePosition.getSquareTextureData(Corner::TOP_LEFT, texId, isBlack));
      data.push_back(piecePosition.getSquareTextureData(Corner::TOP_RIGHT, texId, isBlack));
      data.push_back(piecePosition.getSquareTextureData(Corner::BOT_RIGHT, texId, isBlack));
      data.push_back(piecePosition.getSquareTextureData(Corner::BOT_LEFT, texId, isBlack));
    });
  GameApp::setChanged(false);
  piecesRenderer.updateVertexBuffer(data.data());
}
