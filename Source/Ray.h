#pragma once

#include <glm/vec3.hpp>

using glm::vec3;
struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() = default;
	Ray(glm::vec3 origin, glm::vec3 direction) : origin(origin), direction(direction) {}

	glm::vec3 at(float t) const { return origin + t * direction; }
	glm::vec3 operator * (float t) { return at(t); }
};

