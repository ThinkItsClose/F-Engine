#pragma once

#include <vector>

#include "Mesh.h"

constexpr auto PI = 3.1415926535;

class QuadPrimitive {
public:
	static Mesh GetMesh();
};

class CubePrimitive {
public:
	static Mesh GetMesh();
};

class SpherePrimitive {
public:
	static Mesh GetMesh();
};