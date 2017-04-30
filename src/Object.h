/*#pragma once
//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "..\Shader.h"
#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class Object{
	Object(vec3 scale, vec3 rotation, vec3 position, FigureType typef);

	Object::~Object();
	void Object::Draw();
	void Object::Move(vec3 translation);
	void Object::Rotate(vec3 rota);
	void Object::Scale(vec3 scal);
	mat4 Object::GetModelMatrix();
	vec3 Object::GetPosition();
	void Object::Delete();
};*/