#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <iostream>
#include "VertexPermutations.h"

#define self lre::RenderContext::Instance()

void lre::Initialize() {
	assert(lgl::IsInitialized());

	self->uniformbuffer = lgl::MakeUniformBuffer();

	self->uniformbuffer->Bind();
	self->uniformbuffer->Allocate(sizeof(glm::mat4) * 4);
	self->uniformbuffer->BindRange(0, sizeof(glm::mat4) * 4, 0);

	SetModel(glm::mat4(1.0f));
	SetView(glm::mat4(1.0f));
	SetProjection(glm::mat4(1.0f));
	SetViewPos(glm::vec3(0.0f));

	self->line_shader = new lgl::Shader("D:\\C++\\Robotic Arm\\src\\LucyRE\\Shaders\\vertex.glsl", "D:\\C++\\Robotic Arm\\src\\LucyRE\\Shaders\\line.frag", true);
}

void lre::SetModel(const glm::mat4& model) {
	if (self->model == model) return;
	self->model = model;
	self->uniformbuffer->AddDataDynamic(&self->model[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 0);
}

void lre::SetView(const glm::mat4& view) {
	if (self->view == view) return;
	self->view = view;
	self->uniformbuffer->AddDataDynamic(&self->view[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 1);
}

void lre::SetProjection(const glm::mat4& projection) {
	if (self->projection == projection) return;
	self->projection = projection;
	self->uniformbuffer->AddDataDynamic(&self->projection[0][0], sizeof(glm::mat4), sizeof(glm::mat4) * 2);
}

void lre::SetViewPos(const glm::vec3& view_pos) {
	if (self->view_pos == view_pos) return;
	self->view_pos = view_pos;
	self->uniformbuffer->AddDataDynamic(&self->view_pos[0], sizeof(glm::mat4), sizeof(glm::mat4) * 3);
}

void lre::SetFrameBuffer(lgl::FrameBuffer* framebuffer) {
	self->render_target = framebuffer;
}

void lre::SetPerspective(float fovy, float aspect, float vnear, float vfar) {
	SetProjection(glm::perspective(fovy, aspect, vnear, vfar));
}

void lre::SetOrtho(const float left, const float right, const float top, const float bottom, const float vnear, const float vfar) {
	SetProjection(glm::ortho<float>(left, right, top, bottom, vnear, vfar));
}

void lre::ClearLights() {
	self->light_array.clear();
	self->dir_light_count = 0;
	self->point_light_count = 0;
}

void lre::SetPointLight(const glm::vec3& position, const glm::vec3& color) {
	self->light_array.push_back({self->point_light_count++, POINT, position, color});
}

void lre::SetDirLight(const glm::vec3& direction, const glm::vec3& color) {
	self->light_array.push_back({self->point_light_count++, POINT, direction, color});
}

void lre::SetLineColor(const glm::vec4& color) {
	self->line_color = color;
}

void lre::RenderLine(glm::vec3 v0, glm::vec3 v1) {
	// self->line_vertices.reserve(2 + self->line_vertices.size());

	self->line_vertices.push_back(Vertex::P1{ v0 });
	self->line_vertices.push_back(Vertex::P1{ v1 });
}

void lre::RenderLine(const glm::vec3& v0, const glm::vec3& v1, const glm::vec4& color) {
	// self->line_color_vertices.reserve(2 + self->line_color_vertices.size());

	self->line_color_vertices.push_back(Vertex::P1C1{ v0, color });
	self->line_color_vertices.push_back(Vertex::P1C1{ v1, color });
}

void lre::Render_Lines() {
	if (self->render_target != nullptr)
		self->render_target->Bind();

	if (self->line_vertexbuffer == nullptr)
		self->line_vertexbuffer = new lgl::VertexBuffer();

	self->line_shader->Bind();

	if (self->line_vertices.size() > 0) {
		self->line_vertexbuffer->Bind();
		self->line_vertexbuffer->Allocate(sizeof(Vertex::P1) * self->line_vertices.size());
		self->line_vertexbuffer->AddDataDynamic(self->line_vertices.data(), sizeof(Vertex::P1) * self->line_vertices.size());

		auto* vertexarray = Vertex::P1::VertexArray();
		vertexarray->Bind();
		vertexarray->BindVertexBuffer(self->line_vertexbuffer, vertexarray->stride);

		self->line_shader->SetUniformVec4("u_color", &self->line_color[0]);
		self->line_shader->SetUniformi("type", 0);

		lgl::Draw(lgl::LINE, 0, self->line_vertices.size());

		self->line_vertices.clear();
	}

	if (self->line_color_vertices.size() > 0) {
		self->line_vertexbuffer->Bind();
		self->line_vertexbuffer->Allocate(sizeof(Vertex::P1C1) * self->line_color_vertices.size());
		self->line_vertexbuffer->AddDataDynamic(self->line_color_vertices.data(), sizeof(Vertex::P1C1) * self->line_color_vertices.size());

		auto* vertexarray = Vertex::P1C1::VertexArray();
		vertexarray->Bind();
		vertexarray->BindVertexBuffer(self->line_vertexbuffer, vertexarray->stride);

		self->line_shader->SetUniformi("type", 1);

		lgl::Draw(lgl::LINE, 0, self->line_color_vertices.size());

		self->line_color_vertices.clear();
	}

	self->line_shader->UnBind();

	if (self->render_target != nullptr)
		self->render_target->UnBind();
}

void lre::Render_FrameBuffer() {
	if (self->render_target == nullptr) return;

	self->render_target->UnBind();

	self->screen_shader->Bind();

	static auto* vertexarray = new lgl::VertexArray({});
	vertexarray->Bind();

	self->render_target->texture->BindUnit(0);
	self->screen_shader->SetUniformi("u_texture", 0);

	lgl::Draw(lgl::TRIANGLE, 0, 6);

	self->screen_shader->UnBind();
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count) {
	if (vertexarray && vertexbuffer && indexbuffer) {
		if (shader != nullptr)
			shader->Bind();
		vertexarray->Bind();
		vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);
		vertexarray->BindIndexBuffer(indexbuffer);

		lgl::DrawIndexed(primitive, count, lgl::UNSIGNED_INT, nullptr);
	} else {
		assert(false);
	}
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count, TextureStore& textures) {
	textures.bind();

	Render(primitive, shader, vertexarray, vertexbuffer, first, count);
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int first, int count) {
	if (vertexarray && vertexbuffer) {
		if (shader != nullptr)
			shader->Bind();
		vertexarray->Bind();
		vertexarray->BindVertexBuffer(vertexbuffer, vertexarray->stride);

		lgl::Draw(primitive, first, count);
	} else {
		assert(false);
	}
}

void lre::Render(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, lgl::IndexBuffer* indexbuffer, int count, TextureStore& textures) {
	textures.bind();

	Render(primitive, shader, vertexarray, vertexbuffer, indexbuffer, count);
}

void lre::RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int vertexcount) {
	Render(primitive, shader, vertexarray, vertexbuffer, GetQuadIndices(vertexcount), vertexcount*1.5);
}

void lre::RenderQuads(lgl::Primitive primitive, lgl::Shader* shader, lgl::VertexArray* vertexarray, lgl::VertexBuffer* vertexbuffer, int vertexcount, TextureStore& textures) {
	Render(primitive, shader, vertexarray, vertexbuffer, GetQuadIndices(vertexcount), vertexcount*1.5, textures);
}

void lre::RenderTest() {
	// lgl::VertexArray* vertexarray = Vertex::P1C1::VertexArray();
	// lgl::VertexBuffer vertexbuffer;
}

void lre::Clear() {
	
}

void lre::Clear(const glm::vec4& color) {
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void lre::Clear(const glm::vec3& color) {
	glClearColor(color.x, color.y, color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// void lre::SetShader(const std::string& name, const std::string& vs_filename, const std::string& fs_filename) {
// 	shader_src_map[name] = std::pair(vs_filename, fs_filename);
// }

#undef self