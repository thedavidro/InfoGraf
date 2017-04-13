#include <iostream>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	GLFWwindow * window;

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Hola mundo", nullptr, nullptr);

	if (!window) {
		std::cout << "Error al cargar la ventana" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Error al cargar glew" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	while (!glfwWindowShouldClose(window)) {
		int screenwithd, screenHeight;

		glfwGetFramebufferSize(window, &screenwithd, &screenHeight);
		glViewport(0, 0, screenwithd, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10.f, 10.f, 10.f, -10.f, -1.f, 10.f);
		glMatrixMode(GL_MODELVIEW);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}