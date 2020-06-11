#pragma once

#include <vector>

#include "Object.h"

class Scene {
private:
	std::vector<Object*> objects;

public:
	Scene();
	void AddObject(Object*);
	
	std::vector<Object*>* GetObjects();
};

