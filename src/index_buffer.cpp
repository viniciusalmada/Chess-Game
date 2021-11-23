#include "index_buffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
  this->count = count;
  glGenBuffers(1, &bufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(1, &bufferId);
}

void IndexBuffer::bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void IndexBuffer::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
