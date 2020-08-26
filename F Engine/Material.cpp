#include "Material.h"

Material::Material() {}

void Material::SendToShader(Shader* shader) {
	if (albedoMap->GetID()) {
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(albedoMap->GetType(), albedoMap->GetID());
		shader->SetUniform(std::string("albedoMap"), 0);
	}
	if (normalMap->GetID()) {
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(normalMap->GetType(), normalMap->GetID());
		shader->SetUniform(std::string("normalMap"), 1);
	}
}

void Material::AddAlbedoMap(Texture* newAlbedoMap) {
	albedoMap = newAlbedoMap;
}

Texture* Material::GetAlbedoMap() {
	return albedoMap;
}

void Material::AddNormalMap(Texture* newNormalMap) {
	normalMap = newNormalMap;
}

Texture* Material::GetNormalMap() {
	return normalMap;
}