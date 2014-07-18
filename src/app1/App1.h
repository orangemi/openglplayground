#pragma once
#include "Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class AppDelegate : public Application {
public:
	AppDelegate();
	~AppDelegate();
	void startup();
	void render(double time);

private:
	GLuint program;
	GLuint vertexBuffer;
};

