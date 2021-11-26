#include "vertex_array.h"
#include <GL/glew.h>
#include <GL/GL.h>

GLElements::VertexArray::VertexArray()
{
  glGenVertexArrays(1, &rendererId);
}

void GLElements::VertexArray::freeVertexArray()
{
  for (auto& buffer : buffers)
  {
    buffer.first.freeBuffer();
  }
  glDeleteVertexArrays(1, &rendererId);
}

void GLElements::VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
  this->bind();
  vb.bind();
  const auto& elements = layout.getElements();
  GLintptr offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    const auto& e = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(), (GLvoid*)offset);
    offset += e.count * e.size;
  }
  buffers.push_back({ vb, layout });
}

void GLElements::VertexArray::bind() const
{
  glBindVertexArray(rendererId);
}

void GLElements::VertexArray::unbind() const
{
  glBindVertexArray(0);
}
