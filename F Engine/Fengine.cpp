#include "FEngine.h"

FEngine::FEngine(std::string windowName, unsigned int width, unsigned int height) {

	// Intilaise engine
	glfwInit();

	// Initliase the window
	CreateEngineWindow(windowName, width, height);

	// Initliase GLAD so we have access to OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		return;
	}

	// Setup the OpenGL options (GL_DEPTH_TEST etc..)
	SetOpenGLOptions();

	// Initialise the frame buffers
	SetupFramebuffers();
}

void FEngine::SetupFramebuffers() {
	// Get a handle to the lighting shader that will be used
	delete lightingShader;
	lightingShader = new Shader("shaders/lightingPassVertex.glsl", "shaders/lightingPassFragment.glsl");

	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	// position color buffer
	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, engineWindow->GetWidth(), engineWindow->GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
	// normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, engineWindow->GetWidth(), engineWindow->GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
	// color + specular color buffer
	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, engineWindow->GetWidth(), engineWindow->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	attachments[0] = GL_COLOR_ATTACHMENT0;
	attachments[1] = GL_COLOR_ATTACHMENT1;
	attachments[2] = GL_COLOR_ATTACHMENT2;
	glDrawBuffers(3, attachments);
	// create and attach depth buffer (renderbuffer)
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, engineWindow->GetWidth(), engineWindow->GetHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	// finally check if framebuffer is complete
	if (glCheckNamedFramebufferStatus(gBuffer, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	std::cout << "generated fbo" << std::endl;

	screenObjectMesh = QuadPrimitive::GetMesh();
	screenObject.AddShader(lightingShader);
	screenObject.AddMesh(&screenObjectMesh);
}

void FEngine::SetOpenGLOptions() {
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.835, 1.0, 1.0);
}

void FEngine::CreateEngineWindow(std::string windowName, unsigned int width, unsigned int height) {

	engineWindow = new Window(windowName, width, height);

	// Capture the mouse in the window
	glfwSetInputMode(engineWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

	// Bind the gBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw each object in the scene
	std::vector<Object*>* objects = currentScene->GetObjects();

	for (unsigned int objectIndex = 0; objectIndex < objects->size(); objectIndex++) {
		objects->at(objectIndex)->Draw(camera);
	}

	// Unbind the FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup the texture objects for the lighting shader
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);

	// Draw the quad that encompasses the screen
	lightingShader->Use();
	lightingShader->SetUniform("gPosition", 0);
	lightingShader->SetUniform("gNormal", 1);
	lightingShader->SetUniform("gAlbedo", 2);
	screenObject.Draw(camera);

	glfwSwapBuffers(engineWindow->GetWindow());
	glfwPollEvents();
}

void FEngine::ChangeScene(Scene* scene) {
	currentScene = scene;
}

double FEngine::GetFrameTime() {
	return m_currFrameTime;
}

