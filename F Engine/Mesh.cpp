#include "Mesh.h"

#include <glad/glad.h>
#include <iostream>

Mesh::Mesh(){}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& _indices) {

	// Define the vertices and indices array
	//vertices = _vertices;
	indices_sz = _indices.size();

	// Define the buffer array objects
	// VAO
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// VBO
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); // Static draw could be replaced with dynamic for to optimise it

	// EBO
	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

	// Set and enable veretxattrib pointers
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// Texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));
	glEnableVertexAttribArray(1);

	// Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	// Tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	glEnableVertexAttribArray(3);

	// Un-bind VAO
	glBindVertexArray(0);
}

void Mesh::Draw() {
	// Bind VAO
	glBindVertexArray(this->VAO);

	// Draw
	glDrawElements(GL_TRIANGLES, indices_sz, GL_UNSIGNED_INT, 0);
}