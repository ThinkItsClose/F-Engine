#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

class Camera {
private:
	glm::vec3 position  = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float fov = 90.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;

	float sensitivity = 0.0f;
	float cameraSpeed = 3.0f;

	Window* window;

	void UpdateDirection();

public:
	Camera();
	Camera(Window* hWnd);

	void SetPosition(glm::vec3 newPosition);
	glm::vec3 GetPosition();

	void SetYaw(float newYaw);
	float GetYaw();

	void SetPitch(float newPitch);
	float GetPitch();

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

};

