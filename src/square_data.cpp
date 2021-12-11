#include "square_data.h"

Square::Square(CoordinateF tl, CoordinateF tr, CoordinateF br, CoordinateF bl, Color color)
  :topLeft(tl), topRight(tr), botRight(br), botLeft(bl), color(color)
{
}

int Square::getBytesCount() const
{
  return topLeft.getBytesCount() +
    topRight.getBytesCount() +
    botRight.getBytesCount() +
    botLeft.getBytesCount() +
    color.getBytesCount();
}

Square::VertexData Square::getSquareVertexData(Corner corner) const
{
  switch (corner)
  {
  case Corner::TOP_LEFT:
    return { topLeft.getX(), topLeft.getY(), color.redF(), color.greenF(), color.blueF(), color.alphaF() };
  case Corner::TOP_RIGHT:
    return { topRight.getX(), topRight.getY(), color.redF(), color.greenF(), color.blueF(), color.alphaF() };
  case Corner::BOT_LEFT:
    return { botLeft.getX(), botLeft.getY(), color.redF(), color.greenF(), color.blueF(), color.alphaF() };
  case Corner::BOT_RIGHT:
    return { botRight.getX(), botRight.getY(), color.redF(), color.greenF(), color.blueF(), color.alphaF() };
  default:
    return {};
  }
}

Square::TextureData Square::getSquareTextureData(Corner corner, int id, TexFilter pieceColor, TexFilter selectedOption) const
{
  switch (corner)
  {
  case Corner::TOP_LEFT:
    return { getSquareVertexData(corner), 0.0f, 1.0f, id, pieceColor, selectedOption };
  case Corner::TOP_RIGHT:
    return { getSquareVertexData(corner), 1.0f, 1.0f, id,  pieceColor, selectedOption };
  case Corner::BOT_LEFT:
    return { getSquareVertexData(corner), 0.0f, 0.0f, id,  pieceColor, selectedOption };
  case Corner::BOT_RIGHT:
    return { getSquareVertexData(corner), 1.0f, 0.0f, id,  pieceColor, selectedOption };
  default:
    return {};
  }
}
