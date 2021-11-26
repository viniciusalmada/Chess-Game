#include "vertex_array.h"
#include <GL/glew.h>
#include <GL/GL.h>

GLElements::VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout) : vertexBuffer(vb), layout(layout)
{
  glGenVertexArrays(1, &rendererId);
  this->bind();
  vb.bind();
  const auto& elements = layout.getElements();
  unsigned __int64 offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    const auto& e = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(), (void*)offset);
    offset += static_cast<unsigned long long>(e.count) * e.size;
  }
  vb.unbind();
  unbind();
}

void GLElements::VertexArray::freeVertexArray()
{
  vertexBuffer.freeBuffer();
  glDeleteVertexArrays(1, &rendererId);
}

void GLElements::VertexArray::updateBuffer(const void* data, unsigned int size)
{
  vertexBuffer.setData(data, size);
}


void GLElements::VertexArray::bind() const
{
  glBindVertexArray(rendererId);
   vertexBuffer.bind();
}

void GLElements::VertexArray::unbind() const
{
  glBindVertexArray(0);
   vertexBuffer.unbind();
}
