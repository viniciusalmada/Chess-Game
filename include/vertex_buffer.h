#pragma once

namespace GLElements
{
  class VertexBuffer
  {
  private:
    unsigned int bufferId;

  public:
    VertexBuffer(const void* data, unsigned int size);
    void freeBuffer();

    void bind() const;
    void unbind() const;
  };
}