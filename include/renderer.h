#pragma once
#include <gl_headers.h>
#include <iostream>
#include <vertex_array.h>
#include <index_buffer.h>
#include <gl_utils.h>
#include <shader.h>

namespace GLObj
{
	struct RendererData
	{
		VertexArray vertexArray;
		IndexBuffer indexBuffer;
		Shader shader;
	};

	class Renderer
	{
	private:
		RendererData rendereData;

	public:
		Renderer(RendererData data);
		~Renderer();

		void updateVertexBuffer(const void* data, unsigned int newSize = 0);
		
		void updateIndexBuffer(const unsigned int* data, unsigned int newSize = 0);

		void draw() const;
	};
}