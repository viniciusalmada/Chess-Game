#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 rgbColor;
out vec4 fragColor;
void main()
{
  gl_Position = position;
  fragColor = vec4(rgbColor.xyz, 1.0);
}