#include <texture.h>
#include <gl_headers.h>
#include <image_loader.h>

GLObj::Texture::Texture(const std::string& path, unsigned int slot) : textureId(0), slot(slot), width(0), height(0)
{
  unsigned char* localBuffer = ImageLoader::loadTexture(path, width, height);

  glGenTextures(1, &textureId);
  glActiveTexture(slot);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
  unbind();

  delete localBuffer;
}

void GLObj::Texture::freeTexture()
{
  glDeleteTextures(1, &textureId);
}

void GLObj::Texture::bind() const
{
  glActiveTexture(slot);
  glBindTexture(GL_TEXTURE_2D, textureId);
}

void GLObj::Texture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
