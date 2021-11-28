#pragma once
#include <array>
#include <vector>

class NumericUtils
{
public:
  static std::array<int, 3> hexTo3Dec(int hexColor);
  static std::array<int, 4> hexTo4Dec(unsigned long hexColor);

  static std::vector<unsigned int> genIndices(unsigned int totalSquares)
  {
    std::vector<unsigned int> indices;
    indices.reserve(totalSquares * 6);
    for (unsigned int i = 0, counter = 0; 
      i < totalSquares; 
      i++, counter += 4)
    {
      unsigned int i0 = counter;
      unsigned int i1 = counter + 1;
      unsigned int i2 = counter + 2;
      unsigned int i3 = counter + 3;
      indices.push_back(i0);
      indices.push_back(i1);
      indices.push_back(i2);

      indices.push_back(i2);
      indices.push_back(i3);
      indices.push_back(i0);
    }
    return indices;
  }
};
