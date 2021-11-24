#include "vertex_array.h"
#include <GL/glew.h>

GLElements::VertexArray::VertexArray()
{
  glGenVertexArrays(1, &rendererId);
}

GLElements::VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &rendererId);
}

void GLElements::VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
  vb.bind();
  const auto& elements = layout.getElements();
  int offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    const auto& e = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(), (const void*)&offset);
    offset += e.count * e.size;
  }
}

void GLElements::VertexArray::bind() const
{
  glBindVertexArray(rendererId);
}

void GLElements::VertexArray::unbind() const
{
  glBindVertexArray(0);
}
