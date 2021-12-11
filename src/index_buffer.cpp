#include "index_buffer.h"
#include <gl_headers.h>

GLObj::IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
  this->count = count;
  GLCall(glGenBuffers(1, &bufferId));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
  unbind();
}

void GLObj::IndexBuffer::freeBuffer()
{
  GLCall(glDeleteBuffers(1, &bufferId));
}

void GLObj::IndexBuffer::bind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId));
}

void GLObj::IndexBuffer::unbind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void GLObj::IndexBuffer::updateBuffer(const void* data, unsigned int count)
{
  bind();
  this->count = count;
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
  unbind();
}
