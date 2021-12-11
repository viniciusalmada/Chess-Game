#version 330 core
in vec4 fragColor;
in vec2 fragTexCoord;

flat in int fragTexId;
flat in int fragTexColor;
flat in int fragTexSelectedOption;

out vec4 color;

uniform sampler2D bishopTex;
uniform sampler2D kingTex;  
uniform sampler2D knightTex;
uniform sampler2D pawnTex;
uniform sampler2D queenTex; 
uniform sampler2D rookTex;

const int TEX_ID_BISHOP = 1;
const int TEX_ID_KING = 2;
const int TEX_ID_KNIGHT = 3;
const int TEX_ID_PAWN = 4;
const int TEX_ID_QUEEN = 5;
const int TEX_ID_ROOK = 6;

const int TEX_FILTER_BLACK = 0;
const int TEX_FILTER_WHITE = 1;
const int TEX_FILTER_SELECTED = 2;
const int TEX_FILTER_OPTION = 3;
const int TEX_FILTER_NO_SELECTED = 4;

vec4 invertColor(vec4 color)
{
  vec3 invColor = vec3(1.0,1.0,1.0) - color.rgb;
  return vec4(invColor, color.a);
}

vec4 getPieceTexture(int texId)
{
  switch(texId)
  {
    case TEX_ID_BISHOP:
      return texture(bishopTex, fragTexCoord);
    case TEX_ID_KING:
      return texture(kingTex, fragTexCoord);
    case TEX_ID_KNIGHT:
      return texture(knightTex, fragTexCoord);
    case TEX_ID_PAWN:
      return texture(pawnTex, fragTexCoord);
    case TEX_ID_QUEEN:
      return texture(queenTex, fragTexCoord);
    case TEX_ID_ROOK:
      return texture(rookTex, fragTexCoord);
  }
  return vec4(1.0, 0.0, 0.0, 1.0);
}

vec4 getPieceColorized(vec4 currentColor, int texColor)
{
  switch (texColor)
  {
    case TEX_FILTER_BLACK:
      return currentColor;
    case TEX_FILTER_WHITE:
      return invertColor(currentColor);
  }

  return vec4(1.0, 0.0, 0.0, 1.0);
}

vec4 getPieceSelectedOption(vec4 currentColor, int selectedOption)
{
  switch (selectedOption)
    {
      case TEX_FILTER_NO_SELECTED:
        return currentColor;
      case TEX_FILTER_SELECTED:
        return currentColor * vec4(0.23, 0.68, 0.28, 1.0);
      case TEX_FILTER_OPTION:
        return vec4(currentColor.rgb, currentColor.a * 0.4);
    }
  return currentColor;
}

void main()
{
  vec4 pieceTexture = getPieceTexture(fragTexId);
  vec4 pieceTextureColorized = getPieceColorized(pieceTexture, fragTexColor);
  color = getPieceSelectedOption(pieceTextureColorized, fragTexSelectedOption);
}