#pragma once
#include "GL/glew.h"
#include <vertex_array.h>
#include <index_buffer.h>
#include <shader.h>
#include <gl_utils.h>

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