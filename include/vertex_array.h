#pragma once
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray
{
private:
  unsigned int rendererId;

public:
  VertexArray();
  ~VertexArray();

  void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

  void bind() const;
  void unbind() const;
};