#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"


class Object {
private:
	Mesh* objectMesh = new Mesh();
	Shader* objectShader = new Shader();
	
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f);


public:
	Object();
	void AddMesh(Mesh*);
	void AddShader(Shader*);

	void Draw(Camera* camera);
};

