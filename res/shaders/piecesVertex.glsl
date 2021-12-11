#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in int texId;
layout(location = 4) in int texColor;
layout(location = 5) in int texSelectedOption;

out vec4 fragColor;
out vec2 fragTexCoord;
flat out int fragTexId;
flat out int fragTexColor;
flat out int fragTexSelectedOption;

void main()
{
  gl_Position = position;
  fragColor = vertexColor;
  fragTexCoord = texCoord;
  fragTexId = texId;
  fragTexColor = texColor;
  fragTexSelectedOption = texSelectedOption;
}