#include "App1.h"

AppDeletgate::AppDeletgate() {
}

////////////////////////////////////////////////////////////////////////////

GLuint program;

GLuint compileShader() {
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;
	GLint compileStatus;
	char logMsg[1024];

	static const GLchar* vertex_shader_source[] = {
		"#version 430 core \n"
		"\n"
		"layout (location = 0) in vec4 offset; \n"
		"\n"
		"const vec4 vertices[3] = vec4[3]( \n"
		"	vec4(-0.6, -0.4, 0.5, 1.0), \n"
		"	vec4( 0.6, -0.4, 0.5, 1.0), \n"
		"	vec4( 0.0,  0.6, 0.5, 1.0)); \n"
		"\n"
		"void main(void) { \n"
		//		"	gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
		"	gl_Position = vertices[gl_VertexID] + offset; \n"
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

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderInfoLog(vertex_shader, 1024, NULL, logMsg);
		std::cout << "Fail to compile with the following error: " << logMsg << std::endl;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE) {
		glGetShaderInfoLog(fragment_shader, 1024, NULL, logMsg);
		std::cout << "Fail to compile with the following error: " << logMsg << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}

void AppDeletgate::startup() {
	//GLuint vertex_array_object;
	program = compileShader();
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	glPointSize(10.0f);
}

void AppDeletgate::render(double time) {
	GLfloat color[] = { (float)sin(time) * 0.5f + 0.5f, (float)cos(time) * 0.5f + 0.5f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	GLfloat attrib[] = { (float)sin(time) * 0.5f, (float)cos(time) * 0.5f, 0.0f, 0.0f };
	glVertexAttrib4fv(0, attrib);

	glUseProgram(program);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_POINTS, 0, 3);
}
