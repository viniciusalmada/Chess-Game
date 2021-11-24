#include "vertex_buffer.h"
#include <GL/glew.h>

GLElements::VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
  glGenBuffers(1, &bufferId);
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GLElements::VertexBuffer::~VertexBuffer()
{
  glDeleteBuffers(1, &bufferId);
}

void GLElements::VertexBuffer::bind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void GLElements::VertexBuffer::unbind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
