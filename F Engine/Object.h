#pragma once

#include "Mesh.h"
#include "Shader.h"

class Object {
private:
	Mesh* objectMesh = new Mesh();
	Shader* objectShader = new Shader();

public:
	Object();
	void AddMesh(Mesh*);
	void AddShader(Shader*);

	void Draw();
};

