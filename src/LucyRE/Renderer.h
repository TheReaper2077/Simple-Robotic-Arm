#pragma once

#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>
#include "Primitives.h"
#include "TextureStore.h"
#include <vector>
#include <memory>

namespace lre {
	enum LightMode {
		DIRECTIONAL,
		AREAL,
		POINT,

		LightMode_COUNT
	};

	static enum ShaderStates {
		TEXTURE,
		TEXTURE_COLOR,
		TEXTURE_UCOLOR,
		UTEXTURE,
		UTEXTURE_COLOR,
		UTEXTURE_UCOLOR,
		COLOR,
		UCOLOR = 7,
	};

	struct LightContainer {
		int idx = 0;
		LightMode mode;
		glm::vec3 position_or_direction;
		glm::vec3 color;
	};

	struct RenderContext {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 view_pos;

		lgl::FrameBuffer* render_target = nullptr;

		lgl::UniformBuffer* uniformbuffer = nullptr;
		std::unordered_map<std::string, lgl::Shader*> shader_map;

		// Line
		glm::vec4 line_color = { 1, 1, 1, 1 };
		std::vector<Vertex::P1> line_vertices;
		std::vector<Vertex::P1C1> line_color_vertices;
		lgl::VertexBuffer* line_vertexbuffer = nullptr;

		// Mesh


		// Light
		int dir_light_count = 0;
		int point_light_count = 0;
		std::vector<LightContainer> light_array;

		// Shaders
		lgl::Shader* screen_shader = nullptr;
		lgl::Shader* line_shader = nullptr;

		static RenderContext* Instance() {
			static RenderContext instance;
			return &instance;
		}

		RenderContext() {}
		~RenderContext() {}
	};

	void Initialize();

	void SetModel(const glm::mat4& model);
	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);
	void SetViewPos(const glm::vec3& projection);

	void SetFrameBuffer(lgl::FrameBuffer* framebuffer);

	void SetPerspective(float fovy, float aspect, float vnear, float vfar);
	void SetOrtho(const float left, const float right, const float top, const float bottom, const float vnear, const float vfar);

	void ClearLights();
	void SetPointLight(const glm::vec3& position, const glm::vec3& color);
	void SetDirLight(const glm::vec3& direction, const glm::vec3& color);

	void SetLineColor(const glm::vec4& color);
	void RenderLine(glm::vec3 v0, glm::vec3 v1);
	void RenderLine(const glm::vec3& v0, const glm::vec3& v1, const glm::vec4& color);
	void RenderLine(const std::vector<glm::vec3>& v);
	void RenderLine(const std::vector<glm::vec3>& v, const glm::vec3& color);

	void Render_Lines();
	void Render_FrameBuffer();

	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count);
	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count);
	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures);
	void Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures);

	void RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int count);
	void RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int count, TextureStore& textures);

	void RenderTest();

	void Clear();
	void Clear(const glm::vec4& color);
	void Clear(const glm::vec3& color);
}
