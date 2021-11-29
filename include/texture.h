#pragma once
#include <string>

namespace GLObj
{
  class Texture
  {
  private:
    unsigned int textureId;
    int width;
    int height;

  public:
    Texture() :textureId(0), width(0), height(0) {};
    Texture(const std::string& path);
    void freeTexture();

    void bind(unsigned int slot) const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
  };
}
