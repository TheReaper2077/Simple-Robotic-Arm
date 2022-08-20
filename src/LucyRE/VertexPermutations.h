#pragma once

#ifndef VERTEX_DEF
	#include "Vertex.h"
#endif

struct lre::Vertex::P1 {
	glm::vec3 position;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1 {
	glm::vec3 position;
	glm::vec4 color;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1N1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1N1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1N1UV1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1N1UV1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1N1UVW1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec3 uvw;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1N1UVW1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec3 uvw;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1T1 {
	glm::vec3 position;
	glm::vec4 color;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1UV1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1UV1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1UVW1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 uvw;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
	})
};
struct lre::Vertex::P1C1UVW1T1 {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 uvw;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::color, 4, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1N1 {
	glm::vec3 position;
	glm::vec3 normal;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
	})
};
struct lre::Vertex::P1N1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1N1UV1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
	})
};
struct lre::Vertex::P1N1UV1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1N1UVW1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 uvw;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
	})
};
struct lre::Vertex::P1N1UVW1T1 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 uvw;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::normal, 3, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1T1 {
	glm::vec3 position;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1UV1 {
	glm::vec3 position;
	glm::vec2 uv;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
	})
};
struct lre::Vertex::P1UV1T1 {
	glm::vec3 position;
	glm::vec2 uv;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::uv, 2, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
struct lre::Vertex::P1UVW1 {
	glm::vec3 position;
	glm::vec3 uvw;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
	})
};
struct lre::Vertex::P1UVW1T1 {
	glm::vec3 position;
	glm::vec3 uvw;
	float tex;

	SET_VERTEXARRAY({
		{ Attrib::position, 3, lgl::FLOAT },
		{ Attrib::uvw, 3, lgl::FLOAT },
		{ Attrib::tex, 1, lgl::FLOAT },
	})
};
