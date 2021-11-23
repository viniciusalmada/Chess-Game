#pragma once

class VertexBuffer
{
private:
  unsigned int bufferId;
   
public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void bind(); 
  void unbind();
};