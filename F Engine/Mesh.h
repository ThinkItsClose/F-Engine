#pragma once

#include <glm/vec3.hpp>
#include <vector>

#include "Vertex.h"

class Mesh {
private:
	//std::vector<Vertex> vertices;
	//std::vector<unsigned int> indices;
	unsigned int indices_sz = 0;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

public:
	Mesh();
	Mesh(std::vector<Vertex>& _vertices, std::vector<unsigned int>& _indices);
	void Draw();
};

