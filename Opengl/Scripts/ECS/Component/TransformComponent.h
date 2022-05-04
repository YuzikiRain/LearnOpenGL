#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct TransformComponent
{
	glm::vec3 position;
	glm::quat quaternion;
};