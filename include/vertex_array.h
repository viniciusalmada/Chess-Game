#pragma once
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace GLElements
{
  class VertexArray
  {
  private:
    unsigned int rendererId;
    std::vector<std::pair<VertexBuffer, VertexBufferLayout>> buffers;

  public:
    VertexArray();
    void freeVertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;
  };
}