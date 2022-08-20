#include "Transform.h"

glm::mat4 lucy::Transform::GetTranslationMatrix() {
	return glm::translate(/* (parent != nullptr) ? parent->GetTranslationMatrix():  */glm::mat4(1.0f), translation);
}

glm::mat4 lucy::Transform::GetScaleMatrix() {
	return glm::scale(/* (parent != nullptr) ? parent->GetScaleMatrix():  */glm::mat4(1.0f), scale);
}

glm::quat lucy::Transform::GetRotationQuat() {
	if (!use_rotation_quat)
		rotation_quat = glm::quat(glm::radians(rotation));

	return rotation_quat;
}

glm::mat4 lucy::Transform::GetRotationMatrix() {
	return glm::mat4_cast(glm::conjugate(GetRotationQuat()));
}

glm::mat4 lucy::Transform::GetModel() {
	return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}
