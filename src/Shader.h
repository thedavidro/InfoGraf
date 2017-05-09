#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include<glm.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Shader
{
public:
	GLuint Program;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	void Use();
};

