#include <texture.h>
#include <gl_headers.h>
#include <image_loader.h>

GLObj::Texture::Texture(const std::string& path) : textureId(0), width(0), height(0)
{
  unsigned char* localBuffer = ImageLoader::loadTexture(path, width, height);

  GLCall(glGenTextures(1, &textureId));
  GLCall(glBindTexture(GL_TEXTURE_2D, textureId));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
  GLCall(glGenerateMipmap(GL_TEXTURE_2D));

  delete localBuffer;
}

void GLObj::Texture::freeTexture()
{
  GLCall(glDeleteTextures(1, &textureId));
}

void GLObj::Texture::bind(unsigned int slot) const
{
  GLCall(glActiveTexture(slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, textureId));
}
