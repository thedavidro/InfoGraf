#pragma once

#include "Object.h"



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
	GLfloat movement = 4;
	GLboolean firstMouse = true;
};