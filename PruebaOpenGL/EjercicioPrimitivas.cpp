#include <iostream>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//cuando se pulsa una tecla escape cerramos la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	//comprobar que GLFW estaactivo
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//crear la ventana
	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}

	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);

	//que funcion se llama cuando se detecta una pulsacion de tecla en la ventana x
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		////definir las dimensiones del buffer
		//int screenWithd, screenHeigtht;
		//float ratio;
		//glfwGetFramebufferSize(window, &screenWithd, &screenHeigtht);
		//ratio = screenWithd / (float)screenHeigtht;

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		//origen de la camara, dimensiones de la ventana
		glViewport(0, 0, screenWithd, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		//color de fondo
		glClearColor(0.35, 0.55, 1.0, 1.0);

		//definir la matriz de proyeccion
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10, 10, -10.f, 10.f, -1.0f, 10.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glRotatef((float)glfwGetTime() * 50.f,1.f, 0.f, 0.f);

		//para volver a dejar la rotacion parada
		//glLoadIdentity();

#if(true) // Smiley
		glPointSize(10.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f(9.0f, 9.7f, 0.0f);
		glVertex3f(9.5f, 9.7f, 0.0f);
		glEnd();
		glLineWidth(5.0f);
		glBegin(GL_LINE_STRIP);
		glVertex3f(8.8f, 9.5f, 0.0f);
		glVertex3f(9.3f, 9.2f, 0.0f);
		glVertex3f(9.7f, 9.5f, 0.0f);
		glEnd();
#endif

#if(true) // Montañas
		glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 0.25f, 0.1f);
		glVertex3f(-10.0f, -4.4f, 0.f);
		glVertex3f(6.6f, -4.4f, 0.f);
		glVertex3f(-3.f, 6.6f, 0.f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 0.25f, 0.1f);
		glVertex3f(-16.0f, -10.4f, 0.f);
		glVertex3f(0.6f, -4.4f, 0.f);
		glVertex3f(-7.5f, 7.6f, 0.f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 0.25f, 0.1f);
		glVertex3f(-16.0f, -10.4f, 0.f);
		glVertex3f(-4.6f, -4.4f, 0.f);
		glVertex3f(-11.5f, 7.6f, 0.f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 0.25f, 0.1f);
		glVertex3f(-7.5f, -3.4f, 0.f);
		glVertex3f(7.5f, -4.4f, 0.f);
		glVertex3f(3.5f, 7.6f, 0.f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 0.25f, 0.1f);
		glVertex3f(.0f, -3.4f, 0.f);
		glVertex3f(10.6f, -4.4f, 0.f);
		glVertex3f(7.5f, 6.0f, 0.f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 0.25f, 0.1f);
		glVertex3f(6.0f, -3.4f, 0.f);
		glVertex3f(16.6f, -4.4f, 0.f);
		glVertex3f(11.0f, 6.0f, 0.f);
		glEnd();

#endif

#if(true) // Campo

		glBegin(GL_TRIANGLES);
		glColor3f(0.1f, 0.50f, 0.2f);
		glVertex3f(0.0f, -50.f, 0.f);
		glVertex3f(15.0f, -1.f, 0.f);
		glVertex3f(-15.0f, 0.f, 0.f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.15f, 0.65f, 0.4f);
		glVertex3f(-10.0f, -10.f, 0.f);
		glVertex3f(10.0f, -10.f, 0.f);
		glVertex3f(10.0f, -4.f, 0.f);
		glVertex3f(5.0f, -1.f, 0.f);
		glVertex3f(-10.0f, -6.f, 0.f);
		glEnd();

#endif

		//intercambia el framebuffer
		glfwSwapBuffers(window);
		//comprueba que algun disparador se halla activado (tales como el teclado, raton, etc)
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}