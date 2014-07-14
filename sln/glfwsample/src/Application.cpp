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

void Application::startup() {

}

void Application::render(double time) {

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

bool Application::loadVertexSharderSource(const std::string shaderName, GLuint &shader) {
	std::string source;
	File::readChar(shaderName, source);
	const GLchar * data[] = { source.c_str() };
	shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, data, NULL);
	glCompileShader(shader);
	return true;
}

bool Application::loadFragSharderSource(const std::string shaderName, GLuint &shader) {
	std::string source;
	File::readChar(shaderName, source);
	const GLchar * data[] = { source.c_str() };
	shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, data, NULL);
	glCompileShader(shader);
	return true;
}

bool Application::compileShader(GLuint vertexShader, GLuint fragShader, GLuint &program) {
	GLint compileStatus;
	char logMsg[1024];

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 1024, NULL, logMsg);
		std::cout << "Fail to compile with the following error: " << logMsg << std::endl;
	}

	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderInfoLog(fragShader, 1024, NULL, logMsg);
		std::cout << "Fail to compile with the following error: " << logMsg << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	return true;
}