#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace lucy {
	struct Transform {
		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 anchor_point;
		bool rotate_around_anchor = false;

		glm::quat rotation_quat;
		bool use_rotation_quat = false;

		Transform* parent = nullptr;

		glm::mat4 GetTranslationMatrix();
		glm::mat4 GetScaleMatrix();
		glm::quat GetRotationQuat();
		glm::mat4 GetRotationMatrix();
		glm::mat4 GetModel();
	};
}