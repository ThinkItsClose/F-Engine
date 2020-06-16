#include "Object.h"

Object::Object(){
}

void Object::AddMesh(Mesh* objMesh) {
	// Add the new mesh
	objectMeshes.push_back(objMesh);
}


void Object::SetMeshList(std::vector<Mesh>& newObjectMeshes) {
	for (unsigned int index = 0; index < newObjectMeshes.size(); index++) {
		objectMeshes.push_back(&newObjectMeshes.at(index));
	}
}

void Object::AddShader(Shader* objShader) {

	// Delete the old shader
	delete objectShader;

	// Add the new shader
	objectShader = objShader;
}

void Object::AddMaterial(Material* objMaterial) {

	// Delete the old material
	delete objectMaterial;

	// Add the new material
	objectMaterial = objMaterial;
}

void Object::Draw(Camera* camera) {
	// Start the shader tied to the object
	objectShader->Use();

	// Send the camera matrix's to the shader
	objectShader->SetUniform(&std::string("ViewMatrix"), &camera->GetViewMatrix());
	objectShader->SetUniform(&std::string("ProjectionMatrix"), &camera->GetProjectionMatrix());
	objectShader->SetUniform(&std::string("ModelMatrix"), &modelMatrix);

	// Send the material information to the shader
	objectMaterial->SendToShader(objectShader);

	// Draw the vertices to the screen by itterating over all meshes
	for (unsigned int index = 0; index < objectMeshes.size(); index++) {
		objectMeshes.at(index)->Draw();
	}

	// Un bind the active shaders
	glUseProgram(0);
}

void Object::UpdateModelMatrix() {
	// Make sure to translate -> rotate -> scale
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
}

void Object::SetPosition(glm::vec3 newPosition) {
	position = newPosition;
	UpdateModelMatrix();
}

void Object::SetScale(glm::vec3 newScale) {
	scale = newScale;
	UpdateModelMatrix();
}

void Object::SetRotation(glm::vec3 newRotation) {
	rotation = newRotation;
	UpdateModelMatrix();
}

glm::vec3 Object::GetPosition() {
	return position;
}

glm::vec3 Object::GetScale() {
	return scale;
}

glm::vec3 Object::GetRotation() {
	return rotation;
}