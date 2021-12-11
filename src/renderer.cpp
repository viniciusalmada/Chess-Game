#include "renderer.h"
#include <iostream>

GLObj::Renderer::Renderer(RendererData data) : rendereData(data)
{
}

GLObj::Renderer::~Renderer()
{
  rendereData.indexBuffer.freeBuffer();
  rendereData.vertexArray.freeVertexArray();
  rendereData.shader.freeProgram();
}

void GLObj::Renderer::updateVertexBuffer(const void* data, unsigned int newSize)
{
  rendereData.vertexArray.updateBuffer(data, newSize);
}

void GLObj::Renderer::updateIndexBuffer(const unsigned int* data, unsigned int newSize)
{
  rendereData.indexBuffer.updateBuffer(data, newSize);
}

void GLObj::Renderer::draw() const
{
  rendereData.shader.bind();
  rendereData.vertexArray.bind();
  rendereData.indexBuffer.bind();

  GLCall(glDrawElements(GL_TRIANGLES, rendereData.indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}