#include "FEngine.h"

FEngine::FEngine() {

	// Intilaise engine
	glfwInit();
}

void FEngine::SetOpenGLOptions() {
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FEngine::CreateEngineWindow(std::string windowName, unsigned int width, unsigned int height) {

	engineWindow = new Window(windowName, width, height);

	// Capture the mouse in the window
	glfwSetInputMode(engineWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initliase GLAD so we have access to OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		return;
	}

	// Setup the OpenGL options (GL_DEPTH_TEST etc..)
	SetOpenGLOptions();
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

	// For now get the pointer to the one camera
	Camera* cam = currentScene->GetCameras()->at(0);

	if (IsKeyPressed(GLFW_KEY_W)) {
		cam->SetPosition( cam->GetPosition() + ( cam->GetDirection() * cam->GetCameraSpeed() * (float)m_currFrameTime ));
	}
	if (IsKeyPressed(GLFW_KEY_S)) {
		cam->SetPosition(cam->GetPosition() - (cam->GetDirection() * cam->GetCameraSpeed() * (float)m_currFrameTime));
	}
	if (IsKeyPressed(GLFW_KEY_A)) {
		cam->SetPosition(cam->GetPosition() - (glm::cross(cam->GetDirection(), cam->GetUpVector()) * cam->GetCameraSpeed() * (float)m_currFrameTime));
	}
	if (IsKeyPressed(GLFW_KEY_D)) {
		cam->SetPosition(cam->GetPosition() + (glm::cross(cam->GetDirection(), cam->GetUpVector()) * cam->GetCameraSpeed() * (float)m_currFrameTime));
	}
	if (IsKeyPressed(GLFW_KEY_ESCAPE)) {
		isEngineActive = false;
	}
	if (IsKeyPressed(GLFW_KEY_F)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE + (int)!wireframeEnabled);
		wireframeEnabled = !wireframeEnabled;
	}

	double mouseDX = 0;
	double mouseDY = 0;

	if (GetMouseDelta(mouseDX, mouseDY))  {
		cam->SetYaw(cam->GetYaw() + mouseDX * cam->GetSensitivity() );
		// Clamped to -89 and 89 because after that the image will flip
		cam->SetPitch(std::clamp((float)(cam->GetPitch() + mouseDY * cam->GetSensitivity()), -89.0f, 89.0f));
	}

}

bool FEngine::IsKeyPressed(int keyCode) {
	return (glfwGetKey(engineWindow->GetWindow(), keyCode) == GLFW_PRESS);
}

bool FEngine::GetMouseDelta(double& mouseDX, double& mouseDY) {

	double mouseX;
	double mouseY;

	glfwGetCursorPos(engineWindow->GetWindow(), &mouseX, &mouseY);

	// If the mouse didn't change exit the function
	if (mouseX == prevMousePosX && mouseY == prevMousePosY) {
		return false;
	}

	// Y axis is inverted so it is the other way around
	mouseDX = mouseX - prevMousePosX;
	mouseDY = prevMousePosY - mouseY;

	// Set the new previous positions
	prevMousePosX = mouseX;
	prevMousePosY = mouseY;

	return true;
}

void FEngine::DrawFrame(Camera* camera) {
	m_currFrameTime = glfwGetTime() - m_prevFrameTime;
	m_prevFrameTime = glfwGetTime();

	glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
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

double FEngine::GetFrameTime() {
	return m_currFrameTime;
}

