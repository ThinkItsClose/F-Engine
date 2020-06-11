#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>

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
};

