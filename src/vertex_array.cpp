#include "vertex_array.h"
#include <gl_headers.h>

GLObj::VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout) : vertexBuffer(vb), layout(layout)
{
  GLCall(glGenVertexArrays(1, &rendererId));
  this->bind();
  vb.bind();
  const auto& elements = layout.getElements();
  unsigned __int64 offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    const auto& e = elements[i];
    GLCall(glEnableVertexAttribArray(i));
    if (e.type == GL_FLOAT)
    {
      GLCall(glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(), (void*)offset));
    }
    if (e.type == GL_INT)
    {
      GLCall(glVertexAttribIPointer(i, e.count, e.type, layout.getStride(), (void*)offset));
    }
    offset += static_cast<unsigned long long>(e.count) * e.size;
  }
  vb.unbind();
  unbind();
}

void GLObj::VertexArray::freeVertexArray()
{
  vertexBuffer.freeBuffer();
  GLCall(glDeleteVertexArrays(1, &rendererId));
}

void GLObj::VertexArray::updateBuffer(const void* data, unsigned int newSize)
{
  vertexBuffer.setData(data, newSize);
}


void GLObj::VertexArray::bind() const
{
  GLCall(glBindVertexArray(rendererId));
  vertexBuffer.bind();
}

void GLObj::VertexArray::unbind() const
{
  GLCall(glBindVertexArray(0));
  vertexBuffer.unbind();
}
