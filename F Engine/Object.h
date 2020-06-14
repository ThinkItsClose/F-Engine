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
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	void UpdateModelMatrix();

public:
	Object();
	void AddMesh(Mesh*);
	void AddShader(Shader*);

	void SetPosition(glm::vec3 newPosition);
	void SetScale(glm::vec3 newScale);
	void SetRotation(glm::vec3 newRotation);

	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();

	void Draw(Camera* camera);
};

