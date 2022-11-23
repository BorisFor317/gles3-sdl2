#version 300 es

#ifdef GL_ES
precision highp float;
#endif // GL_ES

in vec2 vertPos;

out vec4 color;

const vec4 white = vec4(1.0);
const vec4 red = vec4(1.0, 0.0, 0.0, 1.0);

void main() {
  color = red;
  gl_Position = vec4(vertPos, 0.0, 1.0);
}
