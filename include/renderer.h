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

		void draw() const;
	};
}