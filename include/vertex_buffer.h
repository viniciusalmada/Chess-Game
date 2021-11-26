#pragma once

namespace GLObj
{
  class VertexBuffer
  {
  private:
    unsigned int bufferId;

  public:
    VertexBuffer(const void* data, unsigned int size);
    void freeBuffer();

    void setData(const void* data, unsigned int size);

    void bind() const;
    void unbind() const;
  };
}