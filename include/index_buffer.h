#pragma once

namespace GLObj
{
  class IndexBuffer
  {
  private:
    unsigned int bufferId;
    unsigned int count;

  public:
    IndexBuffer(const void* data, unsigned int count);
    void freeBuffer();

    void bind() const;
    void unbind() const;

    unsigned int getCount() const { return count; }
  };
}