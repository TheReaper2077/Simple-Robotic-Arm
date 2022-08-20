#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <LucyGL/LucyGL.h>
#include <string>

namespace lucy {
	enum Projection_Type {
		ORTHOGRAPHIC,
		PERSPECTIVE,

		Projection_Type_COUNT
	};

	struct Camera {
		glm::mat4 projection;
		glm::mat4 view;

		glm::vec3 position = { 0.0, 0.0, 0.0 };
		glm::vec3 world_front = { 0.0, 0.0, -1.0 };
		glm::vec3 front = world_front;
		glm::vec3 world_up = { 0.0, 1.0, 0.0 };
		glm::vec3 up = world_up;
		glm::vec3 offset;

		glm::vec4 clear_color = { 0, 0, 0, 0 };
		uint32_t clear_flags = lgl::COLOR_BUFFER_BIT | lgl::DEPTH_BUFFER_BIT;

		int width, height;
		int lastx, lasty;
		bool first_mouse = true;
		float fov = 45;
		float c_near = 0.01, c_far = 1000;
		float sensitivity = 0.1;

		bool enable = true;

		// ViewMode mode = ViewMode_None;
		Projection_Type type = PERSPECTIVE;

		lgl::FrameBuffer* framebuffer = nullptr;
		std::string skybox_id;

		Camera() {}

		void UpdateFPS();
		void UpdateEditor();
		void Update();
	};
}