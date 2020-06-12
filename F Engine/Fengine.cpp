#include "FEngine.h"

FEngine::FEngine() {

	// Intilaise engine
	glfwInit();

}

void FEngine::CreateEngineWindow(std::string windowName, unsigned int width, unsigned int height) {

	engineWindow = new Window(windowName, width, height);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		return;
	} 
}

Window* FEngine::GetWindow() {
	// Check if a window exists
	if (engineWindow)
		return engineWindow;
	else
		return NULL;
}

bool FEngine::IsActive() {
	return isEngineActive;
}

void FEngine::HandleInput() {

	

}

void FEngine::DrawFrame(Camera* camera) {
	m_currFrameTime = glfwGetTime() - m_prevFrameTime;
	m_prevFrameTime = glfwGetTime();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw each object in the scene
	std::vector<Object*>* objects = currentScene->GetObjects();

	for (unsigned int objectIndex = 0; objectIndex < objects->size(); objectIndex++) {
		objects->at(objectIndex)->Draw(camera);
	}

	glfwSwapBuffers(engineWindow->GetWindow());
	glfwPollEvents();
}

void FEngine::ChangeScene(Scene* scene) {
	currentScene = scene;
}