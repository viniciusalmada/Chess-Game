#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 rgbaColor;
out vec4 fragColor;
void main()
{
  gl_Position = vec4(position,1.0,1.0);
  fragColor = rgbaColor;
}