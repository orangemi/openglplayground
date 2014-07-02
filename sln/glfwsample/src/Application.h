#pragma once

#include <GLFW/glfw3.h>
#include <gl/glext.h>
#include <string.h>
#include <math.h>

class Application {
public:
	static Application* _currentApp;
	Application(void);
	~Application(void);
	virtual int start();
	virtual void startup();
	virtual void render(double time);
//	virtual void pollingEvent();
	static void onErrorCallback(int error, const char* desc);
	static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool isRunning();

private:

	bool _isRunning;
	char* _name;
	GLFWwindow* window;

	GLuint rendering_program;
	GLuint vertex_array_object;
};

