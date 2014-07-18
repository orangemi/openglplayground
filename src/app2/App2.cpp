#include "App2.h"

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

////////////////////////////////////////////////////////////////////////////

void AppDelegate::startup() {
	GLuint vertexShader;
	GLuint fragShader;
	loadVertexSharderSource("res/glsl/app2.vert", vertexShader);
	loadFragSharderSource("res/glsl/app2.frag", fragShader);
	compileShader(vertexShader, fragShader, program);

	GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, -1.0f, // triangle 1 : begin
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f, -1.0f, // triangle 2 : begin
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, // triangle 2 : end
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	GLfloat g_frag_buffer_data[] = {
		0.00f, 1.0f - 0.00f,
		0.00f, 1.0f - 0.33f,
		0.33f, 1.0f - 0.33f,
		1.00f, 1.0f - 0.00f,
		0.66f, 1.0f - 0.33f,
		1.00f, 1.0f - 0.33f,
		0.66f, 1.0f - 0.33f,
		0.33f, 1.0f - 0.66f,
		0.66f, 1.0f - 0.66f,
		1.00f, 1.0f - 0.00f,
		0.66f, 1.0f - 0.00f,
		0.66f, 1.0f - 0.33f,
		0.00f, 1.0f - 0.00f,
		0.33f, 1.0f - 0.33f,
		0.33f, 1.0f - 0.00f,
		0.66f, 1.0f - 0.33f,
		0.33f, 1.0f - 0.33f,
		0.33f, 1.0f - 0.66f,
		1.00f, 1.0f - 0.66f,
		1.00f, 1.0f - 0.33f,
		0.66f, 1.0f - 0.33f,
		0.66f, 1.0f - 0.00f,
		0.33f, 1.0f - 0.33f,
		0.66f, 1.0f - 0.33f,
		0.33f, 1.0f - 0.33f,
		0.66f, 1.0f - 0.00f,
		0.33f, 1.0f - 0.00f,
		0.00f, 1.0f - 0.33f,
		0.00f, 1.0f - 0.66f,
		0.33f, 1.0f - 0.66f,
		0.00f, 1.0f - 0.33f,
		0.33f, 1.0f - 0.66f,
		0.33f, 1.0f - 0.33f,
		0.66f, 1.0f - 0.66f,
		1.00f, 1.0f - 0.66f,
		0.66f, 1.0f - 0.33f
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_frag_buffer_data), g_frag_buffer_data, GL_STATIC_DRAW);

	int width, height;
	bool hasAlpha;
	GLubyte * bytes;
	loadPngImg("res/img/texture.png", width, height, hasAlpha, &bytes);
	loadImgTexture(width, height, hasAlpha, bytes, textureBuffer);
}

void AppDelegate::render(double time) {

	glUseProgram(program);

	glm::mat4 projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 modelMatrix(1.0f);
	glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

	GLuint uniformMartix = glGetUniformLocation(program, "mvpMatrix");
	GLuint uniformTexture = glGetUniformLocation(program, "textureSampler");
	glUniformMatrix4fv(uniformMartix, 1, GL_FALSE, &mvpMatrix[0][0]);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	glUniform1i(uniformTexture, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	
	glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void AppDelegate::end() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteProgram(program);
}