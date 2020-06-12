#include "Object.h"

Object::Object(){
}

void Object::AddMesh(Mesh* objMesh) {

	// Delete the old mesh
	delete objectMesh;

	// Add the new mesh
	objectMesh = objMesh;
}

void Object::AddShader(Shader* objShader) {

	// Delete the old shader
	delete objectShader;

	// Add the new shader
	objectShader = objShader;
}

void Object::Draw(Camera* camera) {
	// Start the shader tied to the object
	objectShader->Use();

	// Send the camera matrix's to the shader
	objectShader->SetUniform(&std::string("ViewMatrix"), &camera->GetViewMatrix());
	objectShader->SetUniform(&std::string("ProjectionMatrix"), &camera->GetProjectionMatrix());
	objectShader->SetUniform(&std::string("ModelMatrix"), &modelMatrix);

	// Draw the vertices to the screen
	objectMesh->Draw();

	// Un bind the active shaders
	glUseProgram(0);
}