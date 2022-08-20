#pragma once

#include <vector>
#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

#define VERTEX_DEF

namespace lre::Vertex {
	template <typename T>
	std::vector<T>& GetVertices() {
		static std::vector<T> vertices;
		return vertices;
	}

	template <typename T>
	lgl::VertexBuffer* GetVertexBuffer() {
		static lgl::VertexBuffer vertexbuffer;
		return &vertexbuffer;
	}

	#define SET_VERTEXARRAY(...) static lgl::VertexArray* VertexArray() { static lgl::VertexArray vertexarray(__VA_ARGS__); return &vertexarray; }

	enum Attrib {
		position = 0,
		color = 1,
		normal = 2,
		tex = 3,
		uv = 4,
		uvw = 5,

		Index_COUNT
	};

	struct P1;
	struct P1C1;
	struct P1C1N1;
	struct P1C1N1T1;
	struct P1C1N1UV1;
	struct P1C1N1UV1T1;
	struct P1C1N1UVW1;
	struct P1C1N1UVW1T1;
	struct P1C1T1;
	struct P1C1UV1;
	struct P1C1UV1T1;
	struct P1C1UVW1;
	struct P1C1UVW1T1;
	struct P1N1;
	struct P1N1T1;
	struct P1N1UV1;
	struct P1N1UV1T1;
	struct P1N1UVW1;
	struct P1N1UVW1T1;
	struct P1T1;
	struct P1UV1;
	struct P1UV1T1;
	struct P1UVW1;
	struct P1UVW1T1;
}

#include "VertexPermutations.h"