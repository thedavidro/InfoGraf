//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Model.h" //model tiene el Mesh.h y Mesh.h tiene el Shader.h
#include "Object.h"
#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void DrawVAO(GLuint VAO);
GLfloat mixValue = 0.6f;
float rotationX = 0.0f;
float rotationY = 0.0f;

enum KeyPressed {
	keyW, keyA, keyS, keyD
};

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat fov = 45.0f;
bool firstTime = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int choosenObj = 1;

glm::vec3 cube1pos = { 0,0,0 };
GLfloat cube1offsetX;
GLfloat cube1offsetY;
GLfloat cube1offsetZ;

glm::vec3 cube2pos = { 0,0,0 };
GLfloat cube2offsetX;
GLfloat cube2offsetY;
GLfloat cube2offsetZ;

//funciones
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement(KeyPressed key);

int main() {
	//initGLFW
	//TODO
	GLFWwindow* window;

	if (!glfwInit()) exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "InfoGraf", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear ventana." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//set GLEW and inicializate
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		cout << "Error al iniciar glew." << endl;
		glfwTerminate();
		return NULL;
	}
	//set function when callback
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//set windows and viewport

	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader myShader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	GLuint shaderVar = glGetUniformLocation(myShader.Program, "offset");
	// Definir el buffer de vertices

	// Definir el EBO
	GLuint IndexBufferObject[]{
		0,1,3,
		1,2,3 };

	//ex shaders
	GLfloat VertexBufferObject[] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 CubesPositionBuffer[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Shader lightingShader("path/to/shaders/lighting.vs", "path/to/shaders/lighting.frag");
	Shader lampShader("path/to/shaders/lamp.vs", "path/to/shaders/lamp.frag");

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST); // Z-buffer

	glm::vec3 vector(3);
	glm::mat2 matriz;

	Object cubo1(glm::vec3 = { 1,1,1 }, glm::vec3 = { 0.3,0.3,0.3 }, cube1pos, 0);

	//Object cube1(glm::vec3(1.f, 1.f, 1.f), (0.3f, 0.3f, 0.3f), (0.0f, 0.0f, 0.0f), 0);



	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.f, 0.f, 0.f, 1.f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents(); //llama a do_movement

		myShader.Use();

		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 movementVector = glm::vec3(cube1pos.x + cube1offsetX, cube1offsetY + cube1offsetY, cube1pos.z + cube1offsetZ);
		glm::vec3 rotationVector = glm::vec3(rotationX, rotationY, 0.0f);


		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		projection = glm::perspective(fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		cube1.Move(movementVector);
		cube1.Rotate(rotationVector);
		model = cubeA.GetModelMatrix();

		GLint modelLoc = glGetUniformLocation(myShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(myShader.Program, "view");
		GLint projLoc = glGetUniformLocation(myShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		for (GLuint i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, CubesPositionBuffer[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//intercambia el framebuffer

		


		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstTime)
	{
		lastX = xpos;
		lastY = ypos;
		firstTime = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void do_movement(KeyPressed key) {
	GLfloat cameraSpeed = 5.0f * deltaTime;
	switch (key) {
	case keyW:
		cameraPos += cameraSpeed * cameraFront;
		break;

	case keyA:
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;

	case keyS:
		cameraPos -= cameraSpeed * cameraFront;
		break;

	case keyD:
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		break;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
		do_movement(keyW);

	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
		do_movement(keyA);

	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
		do_movement(keyS);

	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
		do_movement(keyD);

	//EJERCICIO 2
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		/*mixValue += 0.1f;
		if (mixValue >= 1.0f)
		mixValue = 1.0f;*/
		mixValue = 0;
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		/*mixValue -= 0.1f;
		if (mixValue <= 0.0f)
		mixValue = 0.0f;*/
		mixValue = 1;
	}

	// EJERCICIO 3
	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationX += 0.5f;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationX -= 0.5f;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationY -= 0.5f;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		rotationY += 0.5f;
	}

	// Swap de objetos
	if (key == GLFW_KEY_1 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		choosenObj = 1;
	}
	if (key == GLFW_KEY_2 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		choosenObj = 2;
	}
	if (key == GLFW_KEY_3 && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		choosenObj = 3;
	}
}
