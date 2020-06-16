#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <glad\glad.h>

class Texture {
private:
	unsigned int id = 0;
	int type;

public:
	Texture();
	Texture(std::string path, int textureType);

	unsigned int GetID();
	int GetType();
};

