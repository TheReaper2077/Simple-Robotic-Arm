#pragma once

#include <LucyGL/LucyGL.h>
#include <glm/glm.hpp>

namespace lre {
	struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

		float roughness = 0.5;
		float metallic = 0;
		glm::vec3 albedo = glm::vec3(1, 0, 0);
	};
}