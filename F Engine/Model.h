#pragma once

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model {
private:
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes);

public:
	static std::vector<Mesh> GetMeshes(std::string path);
};

