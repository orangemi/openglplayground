#version 430 core
layout (location = 0) in vec4 offset;

const vec4 vertices[3] = vec4[3](
	vec4(-0.6, -0.4, 0.5, 1.0),
	vec4( 0.6, -0.4, 0.5, 1.0),
	vec4( 0.0,  0.6, 0.5, 1.0)
);

void main() {
//	gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
	gl_Position = vertices[gl_VertexID] + offset;
}