#include "vertex_buffer.h"
#include <gl_headers.h>

GLObj::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
  glGenBuffers(1, &bufferId);
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  unbind();
}

void GLObj::VertexBuffer::freeBuffer()
{
  glDeleteBuffers(1, &bufferId);
}

void GLObj::VertexBuffer::setData(const void* data, unsigned int size)
{
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
  unbind();
}

void GLObj::VertexBuffer::bind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void GLObj::VertexBuffer::unbind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
