#pragma once
#include <color.h>
#include <coordinate.h>

class SquareData : public Countable
{
private:
  Coordinate topLeft;
  Coordinate topRight;
  Coordinate botRight;
  Coordinate botLeft;
  Color color;

public:
  SquareData(Coordinate tl, Coordinate tr, Coordinate br, Coordinate bl, Color color);

  void setMargin(float size)
  {
    topLeft += {size, size};
    topRight += {-size, size};
    botRight += {-size, -size};
    botLeft += {size, -size};
  }

  int getBytesCount() const override;
};

