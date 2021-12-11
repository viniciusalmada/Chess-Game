#pragma once
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace GLObj
{
  class VertexArray
  {
  private:
    unsigned int rendererId;
    VertexBuffer vertexBuffer;
    VertexBufferLayout layout;

  public:
    VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void freeVertexArray();

    void updateBuffer(const void* data, unsigned int newSize);

    void bind() const;
    void unbind() const;
  };
}