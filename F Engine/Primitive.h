#pragma once

#include <vector>

#include "Vertex.h"

constexpr auto PI = 3.1415926535;

class QuadPrimitive {
public:
	static void GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};

class CubePrimitive {
public:
	static void GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};

class SpherePrimitive {
public:
	static void GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};

class ConePrimitive {
public:
	static void GetMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};