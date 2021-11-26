#include "index_buffer.h"
#include <GL/glew.h>

GLElements::IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
  this->count = count;
  glGenBuffers(1, &bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
  unbind();
}

void GLElements::IndexBuffer::freeBuffer()
{
  glDeleteBuffers(1, &bufferId);
}

void GLElements::IndexBuffer::bind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void GLElements::IndexBuffer::unbind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
