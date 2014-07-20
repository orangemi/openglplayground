#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 vertrexUV;
varying vec2 UV;
uniform mat4 mvpMatrix;

void main() {
	vec4 v = vec4(pos, 1.0);
	gl_Position = mvpMatrix * v;
	UV = vertrexUV;
}