//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#pragma once
class Shader
{
public:
	GLuint Program;
	Shader(const GLchar*, const GLchar*);
	
	void USE();
};

