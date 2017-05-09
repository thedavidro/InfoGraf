#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 upVector, float yaw, float pitch) {
	cameraPos = position;
	vectorUp = upVector;
	YAW = yaw;
	PITCH = pitch;
	CalculateVectors(); //se actualiza todo
}

void Camera::DoMovement(GLFWwindow *window, KeyPressed key, GLfloat deltaTime) {
	speed = movement * deltaTime;

	switch (key) {
	case keyW: //adelante
		cameraPos += cameraFront * speed;
		break;

	case keyA: //izquierda
		cameraPos += cameraRight * speed;
		break;

	case keyS: //atrás
		cameraPos -= cameraFront * speed;
		break;

	case keyD: //derecha
		cameraPos -= cameraRight * speed;
		break;
	}

	CalculateVectors(); //se actualiza todo
}

void Camera::MouseMove(GLFWwindow *window, double xpos, double ypos) {
	
	if (firstMouse) {
		LastMx = xpos;
		LastMy = ypos;
		firstMouse = false;
	}

	GLfloat diffX = xpos - LastMx;
	GLfloat diffY = LastMy - ypos;
	LastMx = xpos;
	LastMy = ypos;

	diffX *= Sensitivity;
	diffY *= Sensitivity;

	YAW = glm::mod(YAW + diffX, 360.0f);
	PITCH += diffY;


	if (this->PITCH > 89.0f) this->PITCH = 89.0f;
	if (this->PITCH < -89.0f) this->PITCH = -89.0f;


	CalculateVectors(); //update de vectores
}

void Camera::MouseScroll(GLFWwindow *window, double xScroll, double yScroll) {
	if (FOV >= 1.0f && FOV <= 45.0f)
		FOV -= yScroll;
	if (FOV <= 1.0f)
		FOV = 1.0f;
	if (FOV >= 45.0f)
		FOV = 45.0f;
}

glm::mat4 Camera::LookAt() {
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

GLfloat Camera::GetFOV() {
	return FOV;
}

void Camera::CalculateVectors() {
	glm::vec3 frontVector;
	frontVector.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
	frontVector.y = sin(glm::radians(PITCH));
	frontVector.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
	cameraFront = glm::normalize(frontVector);

	cameraRight = glm::normalize(glm::cross(cameraFront, vectorUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

glm::vec3 Camera::camPos() {
	return cameraPos;
}