#pragma once
#include <tuple>
#include <color.h>
#include <coordinate.h>

enum class Corner { TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT };

class Square : public Countable
{
public:
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
    int isBlack;
  };

private:
  Coordinate topLeft;
  Coordinate topRight;
  Coordinate botRight;
  Coordinate botLeft;
  Color color;

public:
  Square() {}
  Square(Coordinate tl, Coordinate tr, Coordinate br, Coordinate bl, Color color);

  void setMargin(float size)
  {
    topLeft += {size, -size};
    topRight += {-size, -size};
    botRight += {-size, size};
    botLeft += {size, size};
  }

  int getBytesCount() const override;

  VertexData getSquareVertexData(Corner corner) const;
  TextureData getSquareTextureData(Corner corner, int id, bool isBlack) const;
};

