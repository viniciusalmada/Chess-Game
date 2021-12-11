#include "vertex_buffer.h"
#include <gl_headers.h>

GLObj::VertexBuffer::VertexBuffer(const void* data, unsigned int size) : size(size)
{
  GLCall(glGenBuffers(1, &bufferId));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  unbind();
}

void GLObj::VertexBuffer::freeBuffer()
{
  GLCall(glDeleteBuffers(1, &bufferId));
}

void GLObj::VertexBuffer::setData(const void* data, unsigned int newSize)
{
  if (newSize != 0) size = newSize;
  bind();
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  unbind();
}

void GLObj::VertexBuffer::bind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
}

void GLObj::VertexBuffer::unbind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
