#pragma once

#include <vector>

#include "Vertex.h"

class PrimativeMesh {
protected:
	static std::vector<Vertex> ArrayToVector(Vertex* vertexArray, unsigned int size);
	static std::vector<unsigned int> ArrayToVector(unsigned int* vertexArray, unsigned int size);
};

class QuadPrimative : public PrimativeMesh {
public:
	static void GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};

class CubePrimative : public PrimativeMesh {
public:
	static void GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
