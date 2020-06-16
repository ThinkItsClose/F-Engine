#include "Material.h"

Material::Material() {}

void Material::SendToShader(Shader* shader) {
	if (albedoMap->GetID()) {
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(albedoMap->GetType(), albedoMap->GetID());
		shader->SetUniform(std::string("albedoMap"), 0);
	}
}

void Material::AddAlbedoMap(Texture* newAlbedoMap) {
	albedoMap = newAlbedoMap;
}

Texture* Material::GetAlbedoMap() {
	return albedoMap;
}