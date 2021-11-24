#pragma once
#include "GL/glew.h"
#include <vertex_array.h>
#include <index_buffer.h>
#include <shader.h>

namespace GLElements
{
	class Renderer
	{
	private:

	public:
		Renderer();
		~Renderer();

		void clear() const;

		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}