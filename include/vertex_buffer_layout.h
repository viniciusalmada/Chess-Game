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

  class VertexBufferLayoutBuilder;

  class VertexBufferLayout
  {
  private:
    friend VertexBufferLayoutBuilder;

    std::vector<VertexBufferElement> elements;
    unsigned int stride = 0;

    VertexBufferLayout() {};

    void pushFloat(unsigned int count);

    void pushInt(unsigned int count);

  public:
    const std::vector<VertexBufferElement>& getElements() const { return elements; }

    unsigned int getStride() const { return stride; }

    unsigned int getBytesCount() const;
  };

  class VertexBufferLayoutBuilder
  {
  private:
    VertexBufferLayout vbl;

  public:
    VertexBufferLayoutBuilder() : vbl({})
    {
    }

    VertexBufferLayoutBuilder& pushFloat(unsigned int count) {
      vbl.pushFloat(count);
      return *this;
    }
    
    VertexBufferLayoutBuilder& pushInt(unsigned int count) {
      vbl.pushInt(count);
      return *this;
    }

    VertexBufferLayout getLayout() const
    {
      return vbl;
    }

  };
}