#include "vertex_buffer_layout.h"
#include <GL/glew.h>

void GLElements::VertexBufferLayout::pushFloat(unsigned int count)
{
  elements.push_back({ GL_FLOAT, count, GL_FALSE, sizeof(float) });
  stride += sizeof(float) * count;
}

void GLElements::VertexBufferLayout::pushUInt(unsigned int count)
{
  elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, sizeof(unsigned int) });
  stride += sizeof(unsigned int) * count;
}
