#version 300 es

#ifdef GL_ES
precision highp float;
#endif // GL_ES

in vec4 color;

void main() {
  fragColor = color;
}