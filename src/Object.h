#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "Shader.h"

class Object {

public:
	enum FigureType {
		cube = 0,
	};

	Object(glm::vec3 scale, glm::vec3 rotation, glm::vec3 position, FigureType typef);
	~Object();

	void Draw();
	void Move(glm::vec3 translation);
	void Rotate(glm::vec3 rota);
	void Scale(glm::vec3 scal);
	void Delete();
	glm::mat4 GetModelMatrix();
	glm::vec3 GetPosition();

private:
	GLuint VBO, VAO, EBO;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};