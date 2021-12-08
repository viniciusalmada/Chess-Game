#include "texture_data.h"
#include "app.h"

GLObj::Texture TextureData::loadTex(std::string str)
{
  std::string path = App::getImagePath(str).generic_string();
  return { path };
}

TextureData::TextureData() : texture(loadTex({})), tag({}), id(0)
{
}

TextureData::TextureData(const std::string& imgName, const std::string& tag, int i)
  : texture(loadTex(imgName)), tag(tag), id(i)
{
  this->id = i;
}

void TextureData::bindTexture(unsigned int slot) const
{
  this->texture.bind(slot);
}
