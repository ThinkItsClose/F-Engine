#include "Mesh.h"

#include <glad/glad.h>
#include <iostream>

Mesh::Mesh(){}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices) {

	// Define the vertices and indices array
	vertices = _vertices;
	indices  = _indices;

	// Define the buffer array objects
	// VAO
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	// VBO
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); // Static draw could be replaced with dynamic for to optiomise it

	// EBO
	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Set and enable veretxattrib pointers
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// Un-bind VAO
	glBindVertexArray(0);
}

void Mesh::Draw() {

	// Bind VAO
	glBindVertexArray(this->VAO);

	// Draw
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}