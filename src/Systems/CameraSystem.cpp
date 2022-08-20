#include "Systems.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Structures/Camera.h>
#include <Structures/Transform.h>
#include <Lucy/Lucy.h>

REGISTRY_DEF;
REGISTRY_STORE_DEF(editorwindow, lucy::EditorWindow);

static float scrollspeed = 0.750f;

namespace lucy {
	void EditorCamera() {
		if (State::editor_camera == (Entity)0) {
			State::editor_camera = registry.create();

			auto& transform = registry.emplace<Transform>(State::editor_camera);
			auto& camera = registry.emplace<Camera>(State::editor_camera);

			camera.type = PERSPECTIVE;
			camera.enable = true;
			camera.position = { 0, 0, 20 };
			transform.translation = { 0, 0, 20 };
		}

		auto& camera = registry.get<Camera>(State::editor_camera);
		auto& transform = registry.get<Transform>(State::editor_camera);

		float distance;

		if (camera.width != editorwindow.size.x || camera.height != editorwindow.size.y) {
			camera.width = editorwindow.size.x;
			camera.height = editorwindow.size.y;

			camera.lastx = camera.width / 2;
			camera.lasty = camera.height / 2;

			camera.first_mouse = true;

			if (camera.framebuffer != nullptr) {
				free(camera.framebuffer);
				camera.framebuffer = nullptr;
			}

			camera.framebuffer = new lgl::FrameBuffer(camera.width, camera.height, true);

			if (camera.type == PERSPECTIVE)
				camera.projection = glm::perspective(glm::radians(camera.fov), (float)camera.width / camera.height, camera.c_near, camera.c_far);
			if (camera.type == ORTHOGRAPHIC) {
				int widen = std::tan(glm::radians(camera.fov/2.0)) * camera.c_far;
				int highten = std::tan(glm::radians((float)(camera.fov / (float)(camera.width/camera.height))/2.0)) * camera.c_far;

				camera.projection = glm::ortho<float>(-widen, widen, -highten, highten, 0.0, (float)(camera.width/camera.height)*camera.c_far);
			}
		}

		if (Events::IsButtonPressed(SDL_BUTTON_MIDDLE)) {
			if (camera.first_mouse) {
				camera.lastx = Events::GetCursorPos().x;
				camera.lasty = Events::GetCursorPos().y;
				camera.first_mouse = false;
			}

			transform.rotation.y -= (Events::GetCursorPos().x - camera.lastx) * camera.sensitivity;
			transform.rotation.x += (camera.lasty - Events::GetCursorPos().y) * camera.sensitivity;

			camera.lastx = Events::GetCursorPos().x;
			camera.lasty = Events::GetCursorPos().y;
		} else {
			camera.first_mouse = true;
		}

		const auto& quaternion = transform.GetRotationQuat();

		camera.front = glm::normalize(quaternion * camera.world_front);
		camera.up = glm::normalize(quaternion * camera.world_up);

		if (Events::IsMouseScrollingUp()) {
			camera.position += camera.front * float(scrollspeed * TimeStep::dt);
		}
		if (Events::IsMouseScrollingDown()) {
			camera.position -= camera.front * float(scrollspeed * TimeStep::dt);
		}

		distance = glm::length(camera.position);
		scrollspeed = distance / 10;
		// camera.position = distance * -camera.front;
		transform.translation = distance * -camera.front;

		static glm::vec3 delta;
		// static glm::vec3 initpos;

		// static bool toggle = false;
		// if (Events::IsButtonPressed(SDL_BUTTON_LEFT) && Events::IsKeyPressed(SDL_SCANCODE_LALT)) {
		// 	glm::vec3 pos;
		// 	glm::vec4 ray_clip = glm::vec4(Events::Get_EditorWindow_CursorPosNormalized().x, Events::Get_EditorWindow_CursorPosNormalized().y, -1.0, 1.0);
		// 	glm::vec4 ray_eye = glm::inverse(camera.projection) * ray_clip;
		// 	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		// 	glm::vec3 ray_wor = glm::inverse(camera.view) * ray_eye;
		// 	ray_wor = glm::normalize(ray_wor);

		// 	float denom = glm::dot(camera.front, ray_wor);
		// 	float t = -glm::dot((camera.front * distance), camera.front) / denom;
		// 	pos = ray_wor * t + (camera.offset + camera.position);

		// 	if (!toggle) {
		// 		initpos = pos;
		// 	}

		// 	delta = pos - initpos;
		// 	toggle = true;
		// }

		// transform.translation = camera.position + camera.offset + delta;

		camera.view = glm::lookAt(transform.translation, transform.translation + camera.front, camera.up);

		// if (toggle && !Events::IsButtonPressed(SDL_BUTTON_LEFT) && Events::IsKeyPressed(SDL_SCANCODE_LALT)) {
		// 	camera.offset += delta;
		// 	toggle = false;
		// 	delta = glm::vec3();
		// }
	}
}

void lucy::System::CameraSystem() {
	EditorCamera();
}