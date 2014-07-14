#include "App1.h"

AppDeletgate::AppDeletgate() {
}

AppDeletgate::~AppDeletgate() {
}

////////////////////////////////////////////////////////////////////////////

void AppDeletgate::startup() {
	GLuint vertexShader;
	GLuint fragShader;
	loadVertexSharderSource("res/glsl/app1.vert", vertexShader);
	loadFragSharderSource("res/glsl/app1.frag", fragShader);
	compileShader(vertexShader, fragShader, program);

	GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
	
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void AppDeletgate::render(double time) {

	glm::mat4 projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 modelMatrix(1.0f);
	glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

	GLuint martix = glGetUniformLocation(program, "mvpMatrix");
	glUniformMatrix4fv(martix, 1, GL_FALSE, &mvpMatrix[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glUseProgram(program);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
