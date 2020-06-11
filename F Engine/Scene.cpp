#include "Scene.h"

Scene::Scene() {}

void Scene::AddObject(Object* obj) {
	objects.push_back(obj);
}

std::vector<Object*>* Scene::GetObjects() {
	return &objects;
}