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

void Object::Draw() {
	objectShader->Use();
	objectMesh->Draw();
	glUseProgram(0);
}