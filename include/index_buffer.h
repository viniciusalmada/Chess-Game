#pragma once

class IndexBuffer
{
private:
  unsigned int bufferId;
  unsigned int count;
   
public:
  IndexBuffer(const unsigned int* data, unsigned int count);
  ~IndexBuffer();

  void bind(); 
  void unbind();

  unsigned int getCount() const { return count; }
};