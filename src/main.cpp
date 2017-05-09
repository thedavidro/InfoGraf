
#include "Camera.h" // Mesh.h + Shader.h + Object.h --> glm, etc added
#include <SOIL.h>

#include <gtc/type_ptr.hpp>


const GLint WIDTH = 800, HEIGHT = 600;

glm::vec3 vectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

bool firstMouse = true;

/*
glm::vec3 cube1pos = { 0,0,0 };
GLfloat cube1offsetX;
GLfloat cube1offsetY;
GLfloat cube1offsetZ;

glm::vec3 cube2pos = { 0,0,0 };
GLfloat cube2offsetX;
GLfloat cube2offsetY;
GLfloat cube2offsetZ;
*/


Camera myCam(glm::vec3(0.0f, 0.0f, 0.0f), vectorUp, -90.0f, 45.0f);

glm::vec3 c1scale = glm::vec3(1.f, 1.f, 1.f);
glm::vec3 c1rotation = glm::vec3(0.f, 0.f, 0.f);
glm::vec3 c1position = glm::vec3(0.f, 1.f, 2.f);
Object cubo1(c1scale, c1rotation, c1position, Object::cube);

glm::vec3 c2scale = glm::vec3(0.1f, 0.1f, 0.1f);
glm::vec3 c2rotation = glm::vec3(0.f, 0.f, 0.f);
glm::vec3 c2position = glm::vec3(0.f, 2.f, -1.f);
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
Object cubo2(c2scale, c2rotation, lightPos, Object::cube);

//funciones
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
	GLFWwindow* window;

	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "InfoGraf", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear ventana." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // cursor oculto en pantalla

	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		cout << "Error al iniciar glew." << endl;
		glfwTerminate();
		return NULL;
	}

	GLuint VBO, VAO, EBO;

	//set function when callback
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader myShader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader lightingShader("./src/LightVertexShader.vertexshader", "./src/LightFragmentShader.fragmenshader");
	

	glEnable(GL_DEPTH_TEST); // Z-buffer

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.Use();
		GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(lightingShader.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "lightPos");
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(viewPosLoc, myCam.camPos().x, myCam.camPos().y, myCam.camPos().z);



		glm::mat4 view;
		cubo1.Scale(c1scale);
		cubo1.Rotate(c1rotation);
		cubo1.Move(c1position);
		view = myCam.LookAt();
		glm::mat4 projection = glm::perspective(myCam.GetFOV(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		cubo1.Draw();
		glBindVertexArray(0);

		myShader.Use();
		modelLoc = glGetUniformLocation(myShader.Program, "model");
		viewLoc = glGetUniformLocation(myShader.Program, "view");
		projLoc = glGetUniformLocation(myShader.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cubo2.Draw();
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
		myCam.DoMovement(window, Camera::keyW, deltaTime);
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
		myCam.DoMovement(window, Camera::keyA, deltaTime);
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
		myCam.DoMovement(window, Camera::keyS, deltaTime);
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
		myCam.DoMovement(window, Camera::keyD, deltaTime);

	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1position.y += 0.1f;
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1position.y -= 0.1f;
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1position.x += 0.1f;
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1position.x -= 0.1f;

	if (key == GLFW_KEY_KP_8 && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1rotation.x += 0.1f;
	if (key == GLFW_KEY_KP_2 && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1rotation.x -= 0.1f;
	if (key == GLFW_KEY_KP_4 && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1rotation.y += 0.1f;
	if (key == GLFW_KEY_KP_6 && (action == GLFW_REPEAT || action == GLFW_PRESS))
		c1rotation.y -= 0.1f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	myCam.MouseMove(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	myCam.MouseScroll(window, xoffset, yoffset);
}