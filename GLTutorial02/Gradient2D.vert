#version 300 es

#ifdef GL_ES
precision highp float;
#endif // GL_ES

in vec2 vertPos;

out vec4 color;

void main() {
  // float red = 1.0 - abs(vertPos.x);
  float red = 0.5 * (vertPos.y + 1.0);
  float green = vertPos.x;
  float blue = -vertPos.x;
  // float total = red + green;
  // red /= total;
  // green /= total;
  // blue /= total;
  color = vec4(red, green, blue, 1.0);
  gl_Position = vec4(vertPos, 0.0, 1.0);
}
