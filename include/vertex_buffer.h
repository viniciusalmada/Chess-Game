#pragma once

namespace GLObj
{
  class VertexBuffer
  {
  private:
    unsigned int bufferId;
    unsigned int size;

  public:
    VertexBuffer(const void* data, unsigned int size);
    void freeBuffer();

    void setData(const void* data, unsigned int newSize);

    void bind() const;
    void unbind() const;
  };
}