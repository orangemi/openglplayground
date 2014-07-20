#version 430
 
//varying vec2 texcoord;
layout(location = 1) in vec2 texcoord;
uniform sampler2D textureSampler;
//out vec3 color;
 
void main(void) {
  vec3 color = vec3(1, 1, 0);
  gl_FragColor = vec4(color.rgb, texture2D(textureSampler, texcoord).a);
  //gl_FragColor = texture2D(textureSampler, texcoord);
  gl_FragColor = vec4(1, 1, 1, texture2D(textureSampler, texcoord).a) * vec4(1,0,0,1);
}