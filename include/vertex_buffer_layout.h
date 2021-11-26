#pragma once
#include <vector>

namespace GLObj
{
  struct VertexBufferElement
  {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    unsigned int size;
  };

  class VertexBufferLayout
  {
  private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

  public:
    VertexBufferLayout() : stride(0) {}

    void pushFloat(unsigned int count);

    void pushUInt(unsigned int count);

    const std::vector<VertexBufferElement>& getElements() const { return elements; }

    unsigned int getStride() const { return stride; }
  };
}