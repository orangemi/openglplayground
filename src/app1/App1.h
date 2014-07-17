#pragma once
#include "Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class AppDeletgate : public Application {
public:
	AppDeletgate();
	~AppDeletgate();
	void startup();
	void render(double time);

private:
	GLuint program;
	GLuint vertexBuffer;
};

