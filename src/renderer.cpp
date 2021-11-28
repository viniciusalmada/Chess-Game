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

void GLObj::Renderer::updateVertexBuffer(const void* data)
{
  rendereData.vertexArray.updateBuffer(data);
}

void GLObj::Renderer::draw() const
{
  rendereData.shader.bind();
  rendereData.vertexArray.bind();
  rendereData.indexBuffer.bind();

  glDrawElements(GL_TRIANGLES, rendereData.indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}