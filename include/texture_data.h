#pragma once
#include <texture.h>

class TextureData
{
private:
  GLObj::Texture texture;
  std::string tag;
  int id;

  static GLObj::Texture loadTex(std::string str);

public:
  TextureData();
  TextureData(const std::string& imgName, const std::string& tag, int id);

  void bindTexture(unsigned int slot) const;

  int getId() const { return id; }
};

