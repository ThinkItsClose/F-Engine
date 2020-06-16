#pragma once

#include "Texture.h"
#include "Shader.h"

class Material {
private:
	Texture* albedoMap = new Texture;

public:
	Material();
	void SendToShader(Shader* shader);

	void AddAlbedoMap(Texture* newAlbedoMap);
	Texture* GetAlbedoMap();
};

