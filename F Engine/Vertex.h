#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 textureCoordinate;
	glm::vec3 normal;
	glm::vec3 tangent;
};