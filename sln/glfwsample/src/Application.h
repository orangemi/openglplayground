#pragma once

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>

#include <GLFW/glfw3.h>
#include <gl/glext.h>
#include <png.h>

#include "File.h"

class Application {
public:
	static Application* _currentApp;
	Application(void);
	~Application(void);
	virtual int start();
	virtual void startup();
	virtual void render(double time);
	static void onErrorCallback(int error, const char* desc);
	static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool isRunning();

protected:
	bool loadVertexSharderSource(char * shaderName, GLuint * shader);
	bool loadFragSharderSource(char * shaderName, GLuint * shader);

protected:

	bool _isRunning;
	char* _name;
	GLFWwindow* window;

	
};

