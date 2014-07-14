#version 430 core

in vec3 pos;
uniform mat4 mvpMatrix;

void main() {
	vec4 v = vec4(pos, 1.0);
	gl_Position = mvpMatrix * v;
}