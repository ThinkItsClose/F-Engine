#include "Primative.h"

// Define the vertices as arrays then convert them because the conversion is only done once and writing the vertices down in an array is alot easier
std::vector<Vertex> PrimativeMesh::ArrayToVector(Vertex* vertexArray, unsigned int size) {
	std::vector<Vertex> result;
	for (unsigned int index = 0; index < size / sizeof(Vertex); index++) {
		result.push_back(vertexArray[index]);
	}
	return result;
}

std::vector<unsigned int> PrimativeMesh::ArrayToVector(unsigned int* vertexArray, unsigned int size) {
	std::vector<unsigned int> result;
	for (unsigned int index = 0; index < size / sizeof(unsigned int); index++) {
		result.push_back(vertexArray[index]);
	}
	return result;
}

// Quad mesh definition
void QuadPrimative::GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {

	Vertex vertexArray[4 * sizeof(Vertex)] = {
		glm::vec3(-0.5, 0.5, 0.5),  glm::vec2(0, 1), glm::vec3(0, 0, 1), glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),   glm::vec2(1, 1), glm::vec3(0, 0, 1), glm::vec3(),
		glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0, 0), glm::vec3(0, 0, 1), glm::vec3(),
		glm::vec3(0.5, -0.5, 0.5),  glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec3()
	};
	unsigned int indicesArray[2 * 3] = {
		0, 3, 1,
		0, 2, 3
	};

	vertices = ArrayToVector(vertexArray, sizeof(vertexArray));
	indices = ArrayToVector(indicesArray, sizeof(indicesArray));
	return;
}

// Cube mesh definition
void CubePrimative::GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
	Vertex vertexArray[6 * 4 * sizeof(Vertex)] = {
		// Front face
		glm::vec3(-0.5, 0.5, 0.5),  glm::vec2(0, 1), glm::vec3(0, 0, 1),  glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),   glm::vec2(1, 1), glm::vec3(0, 0, 1),  glm::vec3(),
		glm::vec3(-0.5, -0.5, 0.5), glm::vec2(0, 0), glm::vec3(0, 0, 1),  glm::vec3(),
		glm::vec3(0.5, -0.5, 0.5),  glm::vec2(1, 0), glm::vec3(0, 0, 1),  glm::vec3(),

		// Back face
		glm::vec3(-0.5, 0.5, -0.5), glm::vec2(1, 1), glm::vec3(0, 0, -1), glm::vec3(),
		glm::vec3(0.5, 0.5, -0.5),  glm::vec2(0, 1), glm::vec3(0, 0, -1), glm::vec3(),
		glm::vec3(-0.5, -0.5, -0.5),glm::vec2(1, 0), glm::vec3(0, 0, -1), glm::vec3(),
		glm::vec3(0.5, -0.5, -0.5), glm::vec2(0, 0), glm::vec3(0, 0, -1), glm::vec3(),

		// Top Face
		glm::vec3(-0.5, 0.5, 0.5),  glm::vec2(0, 1),  glm::vec3(0, 1, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),   glm::vec2(1, 1),  glm::vec3(0, 1, 0), glm::vec3(),
		glm::vec3(-0.5, 0.5, -0.5), glm::vec2(0, 0),  glm::vec3(0, 1, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, -0.5),  glm::vec2(1, 0),  glm::vec3(0, 1, 0), glm::vec3(),

		// Bottom Face
		glm::vec3(-0.5, -0.5, 0.5),  glm::vec2(0, 1),  glm::vec3(0, -1, 0), glm::vec3(),
		glm::vec3(0.5, -0.5, 0.5),   glm::vec2(1, 1),  glm::vec3(0, -1, 0), glm::vec3(),
		glm::vec3(-0.5, -0.5, -0.5), glm::vec2(0, 0),  glm::vec3(0, -1, 0), glm::vec3(),
		glm::vec3(0.5, -0.5, -0.5),  glm::vec2(1, 0),  glm::vec3(0, -1, 0), glm::vec3(),

		// Left Face
		glm::vec3(-0.5, -0.5, -0.5),  glm::vec2(0, 0),  glm::vec3(-1, 0, 0), glm::vec3(),
		glm::vec3(-0.5, 0.5, -0.5),   glm::vec2(0, 1),  glm::vec3(-1, 0, 0), glm::vec3(),
		glm::vec3(-0.5, -0.5, 0.5),   glm::vec2(1, 0),  glm::vec3(-1, 0, 0), glm::vec3(),
		glm::vec3(-0.5, 0.5, 0.5),    glm::vec2(1, 1),  glm::vec3(-1, 0, 0), glm::vec3(),

		// Right Face
		glm::vec3(0.5, -0.5, 0.5),   glm::vec2(0, 0),  glm::vec3(1, 0, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, 0.5),    glm::vec2(0, 1),  glm::vec3(1, 0, 0), glm::vec3(),
		glm::vec3(0.5, -0.5, -0.5),  glm::vec2(1, 0),  glm::vec3(1, 0, 0), glm::vec3(),
		glm::vec3(0.5, 0.5, -0.5),   glm::vec2(1, 1),  glm::vec3(1, 0, 0), glm::vec3()
	};
	unsigned int indicesArray[6 * 2 * 3] = {
		// Front
		0, 3, 1,
		0, 2, 3,

		// Back
		4, 5, 7,
		4, 7, 6,

		// Top
		8, 9, 11,
		8, 11, 10,

		// Bottom
		12, 15, 13,
		12, 14, 15,

		// Left
		16, 19, 17,
		16, 18, 19,

		// Right
		20, 23, 21,
		20, 22, 23
	};

	vertices = ArrayToVector(vertexArray, sizeof(vertexArray));
	indices = ArrayToVector(indicesArray, sizeof(indicesArray));
	return;
}