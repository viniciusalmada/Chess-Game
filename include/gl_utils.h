#pragma once
#include <array>
#include <string>
#include <filesystem>
#include <im/im.h>
#include <im/im_image.h>


class GlUtils
{
public:

  class Program
  {
  public:
    unsigned int id;

    Program(std::filesystem::path shadersPath);

    void use() const;
  };

  struct ShaderSources
  {
    std::string vertexSource;
    std::string fragmentSource;
  };

  struct Color
  {
    unsigned int hexColor = 0x0;
    int alpha = 0xFF;

    std::array<float, 4> getColorsF();
  };

  struct Texture
  {
    int width;
    int height;
    unsigned int id;
  };

  static Color RED;
  static Color WHITE;

  static void uglClearColor(Color color);

  static void uglColor3f(Color color);

  static void uglColor4f(Color color);

  static Texture createTexture2D(imImage* im);

  static void uglViewportAndOrtho(int size);

  static void drawSquare(int x, int y, int squareSize);

  static void draw2DTexture(int texId, int x, int y, int sq, Color color = WHITE);

private:
  static ShaderSources parseShaderString(const std::filesystem::path&);

  static unsigned int compileShader(unsigned int type, std::string source);

  static unsigned int createProgram(const ShaderSources& sources);
};