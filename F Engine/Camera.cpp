#include "Camera.h"

Camera::Camera(){}

Camera::Camera(Window* hWnd){
	window = hWnd;
}

void Camera::SetPosition(glm::vec3 newPosition) {
	position = newPosition;
}

glm::vec3 Camera::GetPosition() {
	return position;
}

void Camera::SetYaw(float newYaw) {
	yaw = newYaw;
	UpdateDirection();
}

float Camera::GetYaw() {
	return yaw;
}

void Camera::SetPitch(float newPitch) {
	pitch = newPitch;
	UpdateDirection();
}

float Camera::GetPitch() {
	return pitch;
}

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(glm::radians(fov), (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(position, position + direction, up);
}

void Camera::UpdateDirection() {
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);
}