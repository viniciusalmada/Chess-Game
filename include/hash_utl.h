#pragma once
#include <unordered_map>

struct PairIntIntHash
{
  std::size_t operator()(const std::pair<int, int>& k) const
  {
    return std::hash<int>()(k.first) ^
      (std::hash<int>()(k.second) << 1);
  }
};