#include "Application.h"

Application* Application::_currentApp = nullptr;

Application::Application() {
	_isRunning = false;
	_name = "Sample";
}

Application::~Application() {
}

bool Application::isRunning() {
	return _isRunning;
}

void Application::onErrorCallback(int error, const char* desc) {
	_currentApp->_isRunning = false;
}

void Application::onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		_currentApp->_isRunning = false;
	}
}

int Application::start() {
	Application::_currentApp = this;
	glfwSetErrorCallback(onErrorCallback);
	if (!glfwInit()) return 1;
	window = glfwCreateWindow(640, 480, this->_name, NULL, NULL);
	if (!window) {
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, onKeyCallback);

	startup();

	_isRunning = true;
	do {
		render(glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (_isRunning && !glfwWindowShouldClose(window));

	return 0;
}

bool Application::loadVertexSharderSource(char * shaderName, GLuint * shader) {
	FILE * fp;
	
	fclose(fp);
	GLchar ** source;
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex_shader, 1, source, NULL);
	glCompileShader(vertex_shader);
}