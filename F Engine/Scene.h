#pragma once

#include <vector>

#include "Object.h"
#include "Camera.h"

class Scene {
private:
	std::vector<Object*> objects;
	std::vector<Camera*> cameras;

public:
	Scene();
	void AddObject(Object*);
	void AddCamera(Camera*);
	
	std::vector<Object*>* GetObjects();
	std::vector<Camera*>* GetCameras();
};

