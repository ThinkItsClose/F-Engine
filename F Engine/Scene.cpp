#include "Scene.h"

Scene::Scene() {}

void Scene::AddObject(Object* obj) {
	objects.push_back(obj);
}

std::vector<Object*>* Scene::GetObjects() {
	return &objects;
}

void Scene::AddCamera(Camera* cam) {
	cameras.push_back(cam);
}

std::vector<Camera*>* Scene::GetCameras() {
	return &cameras;
}