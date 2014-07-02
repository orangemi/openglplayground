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


////////////////////////////////////////////////////////////////////////////


GLuint compileShader() {
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	static const GLchar* vertex_shader_source[] = {
		"#version 430 core \n"
		"\n"
		"void main(void) { \n"
		"	gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
		"} \n"
	};

	static const GLchar* fragment_shader_source[] = {
		"#version 430 core \n"
		"out vec4 color; \n"
		"\n"
		"void main(void) { \n"
		"	color = vec4(0.0, 0.8, 1.0, 1.0); \n"
		"} \n"
	};

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}



void Application::startup() {
	//GLuint vertex_array_object;
	rendering_program = compileShader();
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	glPointSize(40.0f);
}

void Application::render(double time) {
	GLfloat red[] = { (float)sin(time) * 0.5f + 0.5f, (float)cos(time) * 0.5f + 0.5f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, red);
	glUseProgram(rendering_program);
	glDrawArrays(GL_POINTS, 0, 1);
}
