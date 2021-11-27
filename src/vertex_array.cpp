#include "vertex_array.h"
#include <GL/glew.h>
#include <GL/GL.h>

GLObj::VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout) : vertexBuffer(vb), layout(layout)
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
    if (e.type == GL_FLOAT)
      glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(), (void*)offset);
    if (e.type == GL_UNSIGNED_INT)
      glVertexAttribIPointer(i, e.count, e.type, layout.getStride(), (void*)offset);
    offset += static_cast<unsigned long long>(e.count) * e.size;
  }
  vb.unbind();
  unbind();
}

void GLObj::VertexArray::freeVertexArray()
{
  vertexBuffer.freeBuffer();
  glDeleteVertexArrays(1, &rendererId);
}

void GLObj::VertexArray::updateBuffer(const void* data, unsigned int size)
{
  vertexBuffer.setData(data, size);
}


void GLObj::VertexArray::bind() const
{
  glBindVertexArray(rendererId);
  vertexBuffer.bind();
}

void GLObj::VertexArray::unbind() const
{
  glBindVertexArray(0);
  vertexBuffer.unbind();
}
