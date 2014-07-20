#version 430
 
layout(location = 0) in vec4 coord;

vec2 texcoord;
 
void main(void) {
  //color3 = vec3(1,0,0);
  gl_Position = vec4(coord.xy, 0, 1);
  texcoord = coord.zw;
}