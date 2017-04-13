//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include <Shader.hpp>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIREFRAME = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
	GLFWwindow* window;

	//initGLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}

	//set function when callback
	glfwSetKeyCallback(window, key_callback);

	//set windows and viewport
	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);
	glViewport(0, 0, screenWithd, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT);

	//fondo
	glClearColor(0.35, 0.55, 1.0, 1.0);


	//cargamos los shader
	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	// Definir el buffer de vertices
	GLfloat VertexBufferObject[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};

	


	// Definir el EBO
	GLuint IndexBufferObject[]{
		0,1,2,
		3,0,2
	};

	// Crear los VBO, VAO y EBO
	GLuint EBO;
	GLuint VBO;
	GLuint VAO;

	//reservar memoria para el VAO, VBO y EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Establecer el objeto
	glBindVertexArray(VAO); {

		//Declarar el VBO + EBO y enlazar los buffers con OpenGL
		glBindBuffer(GL_ARRAY_BUFFER, VBO);		
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);

		//Establecer las propiedades de los vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//liberar el buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		
	}//liberar el buffer de vertices
	glBindVertexArray(0);

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glClear(GL_COLOR_BUFFER_BIT);

		//establecer el shader
		//glUseProgram(programID);

		//pitar el VAO
		glBindVertexArray(VAO);

		//glClearColor(0.35, 0.1, 0.0, 1.0);



		if (WIREFRAME) {
			//pintar con lineas
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_LINE_LOOP, sizeof(VertexBufferObject), GL_UNSIGNED_INT, 0);

		} else if (!WIREFRAME) {
			//pintar con triangulos
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		glDrawElements(GL_TRIANGLES, sizeof(VertexBufferObject), GL_UNSIGNED_INT, 0);
		

		glDisable(GL_CULL_FACE);

		//Delink Buffer
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//Comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		WIREFRAME = !WIREFRAME;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
