#pragma once
#include <string>

namespace GLObj
{
  class Texture
  {
  private:
    unsigned int textureId;
    unsigned int slot;
    int width;
    int height;

  public:
    Texture(const std::string& path, unsigned int slot);
    void freeTexture();

    void bind() const;
    void unbind() const;

    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
  };
}
