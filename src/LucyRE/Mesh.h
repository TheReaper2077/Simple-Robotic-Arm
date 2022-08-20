#pragma once

#include <glm/glm.hpp>
#include <LucyGL/LucyGL.h>

namespace lre {
	struct Mesh {
		lgl::VertexArray* vertexarray = nullptr;
		lgl::VertexBuffer* vertexbuffer = nullptr;
		lgl::IndexBuffer* indexbuffer = nullptr;

		int vertexcount = 0;
		int indexcount = 0;
	};
}