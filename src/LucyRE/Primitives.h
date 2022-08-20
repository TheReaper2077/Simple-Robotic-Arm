#pragma once

#include "Vertex.h"

namespace lre {
	lgl::IndexBuffer* GetWireQuadIndices(int vertexcount);
	lgl::IndexBuffer* GetQuadIndices(int vertexcount);

	void QuadIndexed(std::vector<Vertex::P1>& vertices, const glm::vec3& position, const glm::vec2& size);
	void QuadIndexed(std::vector<Vertex::P1C1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	void QuadIndexed(std::vector<Vertex::P1C1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1C1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1);
	void QuadIndexed(std::vector<Vertex::P1C1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1C1UVW1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec3& uv0, const glm::vec2& uv1);
	void QuadIndexed(std::vector<Vertex::P1C1UVW1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec3& uv0, const glm::vec2& uv1, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1);
	void QuadIndexed(std::vector<Vertex::P1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex);
	void QuadIndexed(std::vector<Vertex::P1UVW1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec3& uv0, const glm::vec2& uv1);
	void QuadIndexed(std::vector<Vertex::P1UVW1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec3& uv0, const glm::vec2& uv1, const unsigned int tex);

	void QuadIndexed(std::vector<Vertex::P1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1C1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1C1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const unsigned int tex, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1C1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1C1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1C1UVW1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec3& uv0, const glm::vec2& uv1, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1C1UVW1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const glm::vec3& uv0, const glm::vec2& uv1, const unsigned int tex, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const unsigned int tex, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1UV1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1UV1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1, const unsigned int tex, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1UVW1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec3& uv0, const glm::vec2& uv1, const glm::quat& quaternions);
	void QuadIndexed(std::vector<Vertex::P1UVW1T1>& vertices, const glm::vec3& position, const glm::vec2& size, const glm::vec3& uv0, const glm::vec2& uv1, const unsigned int tex, const glm::quat& quaternions);
}
