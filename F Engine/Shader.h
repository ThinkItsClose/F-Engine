#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	unsigned int programID = 0;
	bool didErrorOccur = false;

	bool ReadShaderFile(std::string filename, std::string& shaderCode);
	bool CompileShader(unsigned int shader, std::string shaderCode);

public:
	Shader();
	Shader(std::string vShaderPath, std::string fShaderPath);
	bool DidErrorOccur();
	void Use();

	void SetUniform(std::string* name, glm::vec3* value);
	void SetUniform(std::string* name, glm::mat4* value);
	void SetUniform(std::string name, int value);
};

