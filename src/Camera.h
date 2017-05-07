#pragma once

#include <vector>

#include <GLFW\glfw3.h> // para el window
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>



class Camera {
public:
	enum KeyPressed {
		keyW, keyA, keyS, keyD
	};

	Camera(glm::vec3 position, glm::vec3 upVector, float yaw, float pitch);
	void DoMovement(GLFWwindow *window, KeyPressed key, GLfloat deltaTime);
	void MouseMove(GLFWwindow *window, double xpos, double ypos);
	void MouseScroll(GLFWwindow *window, double xScroll, double yScroll);
	void CalculateVectors();
	glm::mat4 LookAt();
	GLfloat GetFOV();
	glm::vec3 camPos();

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 vectorUp;
	GLfloat LastMx;
	GLfloat LastMy;
	GLfloat Sensitivity = 0.25f;
	GLfloat PITCH = 0.0f;
	GLfloat YAW = -90.0f;
	GLfloat FOV = 45.0f;
	GLfloat speed;
	GLfloat movement = 1;
};

Camera::Camera(glm::vec3 position, glm::vec3 upVector, float yaw, float pitch) {
	this->cameraPos = position;
	this->vectorUp = upVector;
	this->YAW = yaw;
	this->PITCH = pitch;
	this->CalculateVectors(); //se actualiza todo
}

void Camera::DoMovement(GLFWwindow *window, KeyPressed key, GLfloat deltaTime) {
	this->speed = movement * deltaTime;

	switch (key) {
	case keyW: //adelante
		this->cameraPos += cameraFront * this->speed;
		break;

	case keyA: //izquierda
		this->cameraPos += cameraRight * this->speed;
		break;

	case keyS: //atrás
		this->cameraPos -= cameraFront * this->speed;
		break;

	case keyD: //derecha
		this->cameraPos -= cameraRight * this->speed;
		break;
	}

	this->CalculateVectors(); //se actualiza todo
}

void Camera::MouseMove(GLFWwindow *window, double xpos, double ypos) {
	xpos *= this->Sensitivity;
	ypos *= this->Sensitivity;

	this->YAW = xpos;
	this->PITCH = ypos;

	if (this->PITCH > 89.0f)
		this->PITCH = 89.0f;
	if (this->PITCH < -89.0f)
		this->PITCH = -89.0f;

	this->CalculateVectors(); //update de vectores
}

void Camera::MouseScroll(GLFWwindow *window, double xScroll, double yScroll) {
	if (this->FOV >= 1.0f && this->FOV <= 45.0f)
		this->FOV -= yScroll;
	if (this->FOV <= 1.0f)
		this->FOV = 1.0f;
	if (this->FOV >= 45.0f)
		this->FOV = 45.0f;
}

glm::mat4 Camera::LookAt() {
	return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
}

GLfloat Camera::GetFOV() {
	return FOV;
}

void Camera::CalculateVectors() {
	glm::vec3 frontVector;
	frontVector.x = cos(glm::radians(this->YAW)) * cos(glm::radians(this->PITCH));
	frontVector.y = sin(glm::radians(this->PITCH));
	frontVector.z = sin(glm::radians(this->YAW)) * cos(glm::radians(this->PITCH));
	this->cameraFront = glm::normalize(frontVector);

	this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->vectorUp));
	this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));
}

glm::vec3 Camera::camPos() {
	return cameraPos;
}