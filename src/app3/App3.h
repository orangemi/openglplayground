#pragma once
#include "Application.h"

class AppDelegate : public Application {
public:
	AppDelegate();
	~AppDelegate();
	void startup();
	void render(double time);
	void end();

private:
	GLuint program;
	GLuint fontTexture;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint textureBuffer;
	FT_Face face;
};

