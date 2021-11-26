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

void GLObj::Renderer::clear() const
{
  glClear(GL_COLOR_BUFFER_BIT);
  GlUtils::uglClearColor(rendereData.clearColor);
}

void GLObj::Renderer::draw() const
{
  clear();

  rendereData.shader.bind();
  rendereData.vertexArray.bind();
  rendereData.indexBuffer.bind();

  glDrawElements(GL_TRIANGLES, rendereData.indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}