#version 330 core
in vec4 fragColor;
in vec2 fragTexCoord;

flat in int fragTexId;
flat in int fragIsBlack;

out vec4 color;

uniform sampler2D bishopTex;
uniform sampler2D kingTex;  
uniform sampler2D knightTex;
uniform sampler2D pawnTex;
uniform sampler2D queenTex; 
uniform sampler2D rookTex;
uniform sampler2D movementOptionTex;

vec4 invertColor(vec4 color)
{
  vec3 invColor = vec3(1.0,1.0,1.0) - color.rgb;
  return vec4(invColor, color.a);
}

void main()
{
  switch(fragTexId)
  {
    case 1:
      color = texture(bishopTex, fragTexCoord);
      break;
    case 2:
      color = texture(kingTex, fragTexCoord);
      break;
    case 3:
      color = texture(knightTex, fragTexCoord);
      break;
    case 4:
      color = texture(pawnTex, fragTexCoord);
      break;
    case 5:
      color = texture(queenTex, fragTexCoord);
      break;
    case 6:
      color = texture(rookTex, fragTexCoord);
      break;
    case 7:
      color = texture(movementOptionTex, fragTexCoord);
      break;
    default:
      color = vec4(1.0, 0.0, 0.0, 1.0);
      break;
  }
  if (fragIsBlack != 1)
    color = invertColor(color);
}