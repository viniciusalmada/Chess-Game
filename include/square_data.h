#pragma once
#include <tuple>
#include <color.h>
#include <coordinate.h>

enum class Corner { TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT };

class Square : public Countable
{
public:
  enum class TexFilter { BLACK = 0, WHITE = 1, SELECTED = 2, OPTION = 3, NO_SELECTED = 4 };

  struct VertexData
  {
    float x;
    float y;
    float red;
    float green;
    float blue;
    float alpha;
  };

  struct TextureData
  {
    VertexData square;
    float s;
    float t;
    int texId;
    TexFilter texPieceColor;
    TexFilter texSelectedOption;
  };

private:
  CoordinateF topLeft;
  CoordinateF topRight;
  CoordinateF botRight;
  CoordinateF botLeft;
  Color color;

public:
  Square() {}
  Square(CoordinateF tl, CoordinateF tr, CoordinateF br, CoordinateF bl, Color color);

  void setMargin(float size)
  {
    topLeft += {size, -size};
    topRight += {-size, -size};
    botRight += {-size, size};
    botLeft += {size, size};
  }

  int getBytesCount() const override;

  VertexData getSquareVertexData(Corner corner) const;
  TextureData getSquareTextureData(Corner corner, int id, TexFilter pieceColor, TexFilter selectedOption) const;
};

