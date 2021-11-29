#include "index_buffer.h"
#include <gl_headers.h>

GLObj::IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
  this->count = count;
  glGenBuffers(1, &bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
  unbind();
}

void GLObj::IndexBuffer::freeBuffer()
{
  glDeleteBuffers(1, &bufferId);
}

void GLObj::IndexBuffer::bind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void GLObj::IndexBuffer::unbind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
