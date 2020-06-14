#pragma once

#include <string>
#include <glad/glad.h>
#include <vector>
#include <algorithm>

#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include "Primitive.h"

class FEngine {
private:
	Window* engineWindow = new Window();
	Scene* currentScene = new Scene();

	bool isEngineActive = true;

	double m_prevFrameTime = 0.0f;
	double m_currFrameTime = 0.0f;
	
	unsigned int m_drawCalls = 0;

	double prevMousePosX = 0.0f;
	double prevMousePosY = 0.0f;

	bool wireframeEnabled = false;

public:
	FEngine();
	void SetOpenGLOptions();
	void CreateEngineWindow(std::string, unsigned int, unsigned int);
	Window* GetWindow();
	bool IsActive();
	void DrawFrame(Camera* camera);
	void ChangeScene(Scene*);
	void HandleInput();
	bool IsKeyPressed(int keyCode);
	bool GetMouseDelta(double& mouseDX, double& mouseDY);
	double GetFrameTime();
};

