#include "vertex_buffer_layout.h"
#include <gl_headers.h>

void GLObj::VertexBufferLayout::pushFloat(unsigned int count)
{
  elements.push_back({ GL_FLOAT, count, GL_FALSE, sizeof(float) });
  stride += sizeof(float) * count;
}

void GLObj::VertexBufferLayout::pushInt(unsigned int count)
{
  elements.push_back({ GL_INT, count, GL_FALSE, sizeof(unsigned int) });
  stride += sizeof(unsigned int) * count;
}

unsigned int GLObj::VertexBufferLayout::getBytesCount() const
{
  unsigned int bytesCount = 0;
  for (const auto& el : elements)
    bytesCount += el.size * el.count;
  return bytesCount;
}
