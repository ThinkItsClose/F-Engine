#include "Shader.h"

Shader::Shader(){}

Shader::Shader(std::string vShaderPath, std::string fShaderPath) {
	unsigned int vShader;
	unsigned int fShader;
	std::string vShaderCode;
	std::string fShaderCode;

	if (!ReadShaderFile(vShaderPath, vShaderCode) || !ReadShaderFile(fShaderPath, fShaderCode)) {
		didErrorOccur = true;
		return;
	}

	// Compile the shaders
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!CompileShader(vShader, vShaderCode) || !CompileShader(fShader, fShaderCode)) {
		// Error occured
		didErrorOccur = true;
		return;
	}

	// Link the shaders
	programID = glCreateProgram();
	glAttachShader(programID, vShader);
	glAttachShader(programID, fShader);
	glLinkProgram(programID);

	// Check for linking errors
	int linkSuccess;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess) {
		std::cout << "Shaders failed to link" << std::endl;
		
		// Get the error buffer length
		int errorLength;
		glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &errorLength);
		char* error = new char[errorLength];

		// Get the error and print it to the console
		glGetShaderInfoLog(programID, errorLength, NULL, error);
		std::cout << error << std::endl;

		didErrorOccur = true;
		return;
	}

	// The Shaders can now be deleted as they have been compiled and linked
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

bool Shader::ReadShaderFile(std::string filename, std::string& shaderCode) {
	std::ifstream shaderFile;
	std::stringstream shaderStream;
	
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderFile.open(filename);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
		return true;
	}
	catch (std::ifstream::failure& error) {
		std::cout << "Shader read file failed (" << filename << "): " << error.code() << std::endl;
		return false;
	}
}

bool Shader::CompileShader(unsigned int shader, std::string shaderCode) {
	const char* newShaderCode = shaderCode.c_str();
	
	// Attempt compilation
	glShaderSource(shader, 1, &newShaderCode, NULL);
	glCompileShader(shader);

	// Validate compilation
	int successfulCompilation;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &successfulCompilation);
	if (!successfulCompilation) {
		// Compilation failed, get the shader type
		int shaderType;
		glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);
		if (shaderType == GL_VERTEX_SHADER) {
			std::cout << "Vertex Shader failed to compile" << std::endl;
		}
		else {
			std::cout << "Fragment Shader failed to compile" << std::endl;
		}
		
		// Get the error buffer length
		int errorLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);
		char* error = new char[errorLength];

		// Get the error and print it to the console
		glGetShaderInfoLog(shader, errorLength, NULL, error);
		std::cout << error << std::endl;

		return false;
	}
	return true;
}

unsigned int Shader::GetProgramID() {
	return programID;
}

bool Shader::DidErrorOccur() {
	return didErrorOccur;
}

void Shader::Use() {
	glUseProgram(programID);
}

void Shader::SetUniform(std::string* name, glm::vec3* value) {
	glUniform3fv(glGetUniformLocation(programID, name->c_str()), 1, glm::value_ptr(*value));
}

void Shader::SetUniform(std::string* name, glm::mat4* value) {
	glUniformMatrix4fv(glGetUniformLocation(programID, name->c_str()), 1, GL_FALSE, &(*value)[0][0]);
}

void Shader::SetUniform(std::string name, int value) {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}