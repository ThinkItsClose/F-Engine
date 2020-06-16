#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Material.h"


class Object {
private:
	std::vector<Mesh*> objectMeshes;
	Shader* objectShader = new Shader;
	Material* objectMaterial = new Material;
	
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 rotation = glm::vec3(0.0f);

	void UpdateModelMatrix();

public:
	Object();
	void AddMesh(Mesh*);
	void AddShader(Shader*);
	void AddMaterial(Material*);

	void SetMeshList(std::vector<Mesh>& newObjectMeshes);

	void SetPosition(glm::vec3 newPosition);
	void SetScale(glm::vec3 newScale);
	void SetRotation(glm::vec3 newRotation);

	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();

	void Draw(Camera* camera);
};

