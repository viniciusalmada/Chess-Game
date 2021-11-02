#pragma once
#include <unordered_map>
#include <coordinate.h>

struct SquarePositionHash
{
  std::size_t operator()(const SquarePosition& k) const
  {
    return std::hash<int>()(k.rankId()) ^
      (std::hash<int>()(k.fileId()) << 1);
  }
};

struct SquarePositionEqual
{
  bool operator()(const SquarePosition& lhs,const SquarePosition& rhs) const
  {
    return lhs == rhs;
  }
};