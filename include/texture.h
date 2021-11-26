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
    Texture(const std::string& path);
    void freeTexture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
  };
}
