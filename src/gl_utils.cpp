#include <GL/glew.h>
#include "gl_utils.h"
#include "numeric_utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

GlUtils::Color GlUtils::RED = { 0xFF0000 };
GlUtils::Color GlUtils::WHITE = { 0xFFFFFF };

static void _genBuffers(unsigned int& id)
{
  if (id == 0)
  {
    glGenBuffers(1, &id);
    if (id == 0)
    {
      throw std::runtime_error("Error generating vertex buffer");
    }
  }
}

std::array<float, 4> GlUtils::Color::getColorsF()
{
  auto rgb = NumericUtils::hexTo3Dec(hexColor);

  float r = rgb[0] / (float)0xFF;
  float g = rgb[1] / (float)0xFF;
  float b = rgb[2] / (float)0xFF;
  float a = alpha / (float)0xFF;
  return { r, g, b, a };
}

void GlUtils::uglClearColor(Color color)
{
  auto rgb = color.getColorsF();

  glClearColor(rgb[0], rgb[1], rgb[2], rgb[3]);
}

void GlUtils::uglColor3f(Color color)
{
  auto rgb = color.getColorsF();

  glColor3f(rgb[0], rgb[1], rgb[2]);
}

void GlUtils::uglColor4f(Color color)
{
  auto rgba = color.getColorsF();

  glColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);
}

GlUtils::Texture GlUtils::createTexture2D(imImage* img)
{
  int data_type = 0;
  switch (img->data_type)
  {
  case IM_BYTE:
    data_type = GL_UNSIGNED_BYTE;
    break;
  case IM_FLOAT:
    data_type = GL_FLOAT;
    break;
  }

  /*
  * Get the data planes
  * --------------[imImage->data]------------
  * |RRR...RRR|GGG...GGG|BBB...BBB|AAA...AAA|
  * |   Red   |  Green  |   Blue  |  Alpha  |
  * |planesize|planesize|planesize|planesize|
  *
  * Each entry (R,G,B or A) of this data array has a single byte (unsigned char)
  * of color/alpha intensity varying from 0x00 to 0xFF	*/
  unsigned char* rplane = ((unsigned char**)(img->data))[0];
  unsigned char* gplane = ((unsigned char**)(img->data))[0] + 1 * (long long)img->plane_size;
  unsigned char* bplane = ((unsigned char**)(img->data))[0] + 2 * (long long)img->plane_size;
  unsigned char* aplane = ((unsigned char**)(img->data))[0] + 3 * (long long)img->plane_size;

  /*
  * To compound a OpenGL texture, the colors must be placed in following order:
  * |RGBA|RGBA|RGBA|....
  * | 1px| 1px| 1px|
  */
  int pixelsCount = img->width * img->height;

  unsigned char* imageBuffer = new unsigned char[(long long)pixelsCount * 4];

  unsigned char* bufferAuxPtr = imageBuffer;

  for (int i = 0; i < pixelsCount; i++)
  {
    bufferAuxPtr[0] = *(rplane++);
    bufferAuxPtr[1] = *(gplane++);
    bufferAuxPtr[2] = *(bplane++);
    bufferAuxPtr[3] = img->has_alpha ? *(aplane++) : 0xFF;
    bufferAuxPtr += 4;
  }

  unsigned int textureId = 0;
  glGenTextures(1, &textureId);

  glBindTexture(GL_TEXTURE_2D, textureId);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, data_type, imageBuffer);

  GlUtils::Texture tex{ img->width, img->height, textureId };

  delete[] imageBuffer;
  imImageDestroy(img);

  return tex;
}

void GlUtils::uglViewportAndOrtho(int s)
{
  glViewport(0, 0, s, s);
  glLoadIdentity();
  glOrtho(0, s, s, 0, -1.0, 1.0);
}

void GlUtils::drawSquare(int x, int y, int squareSize)
{
  glBegin(GL_QUADS);
  glVertex2i(x, y);
  glVertex2i(x + squareSize, y);
  glVertex2i(x + squareSize, y + squareSize);
  glVertex2i(x, y + squareSize);
  glEnd();
}

void GlUtils::draw2DTexture(int texId, int x, int y, int sq, GlUtils::Color color)
{
  //glBindTexture(GL_TEXTURE_2D, 0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texId);
  GlUtils::uglColor4f(color);
  glBegin(GL_QUADS);
  // top-right
  glTexCoord2f(0.0f, 1.0f); glVertex2i(x, y);
  // top-left
  glTexCoord2f(1.0f, 1.0f); glVertex2i(x + sq, y);
  // bottom-left
  glTexCoord2f(1.0f, 0.0f); glVertex2i(x + sq, y + sq);
  // bottom-right
  glTexCoord2f(0.0f, 0.0f); glVertex2i(x, y + sq);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void GlUtils::drawElements(int totalIndices)
{
  glDrawElements(GL_TRIANGLES, totalIndices, GL_UNSIGNED_INT, nullptr);
}

GlUtils::ShaderSources GlUtils::parseShaderString(const std::filesystem::path& path)
{
  std::array<std::string, 2> shaderNames = { {"vertex.glsl", "fragment.glsl"} };
  std::stringstream ss[2];
  for (int i = 0; i < 2; i++)
  {
    std::filesystem::path shader = std::filesystem::path{ path }.append(shaderNames[i]);
    std::fstream stream(shader.generic_string());
    std::string line;
    while (getline(stream, line))
    {
      ss[i] << line << std::endl;
    }
  }


  return { ss[0].str(), ss[1].str() };

}

unsigned int GlUtils::compileShader(unsigned int type, std::string src)
{
  unsigned int id = glCreateShader(type);
  auto sourceC = src.c_str();
  glShaderSource(id, 1, &sourceC, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (!result)
  {
    int len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
    char* message = new char[len];
    glGetShaderInfoLog(id, len, &len, message);
    std::cerr << message << std::endl;
    glDeleteShader(id);
    delete[] message;
    return 0;
  }

  return id;
}

unsigned int GlUtils::createProgram(const ShaderSources& sources)
{
  unsigned int programId = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, sources.vertexSource);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, sources.fragmentSource);

  glAttachShader(programId, vs);
  glAttachShader(programId, fs);
  glLinkProgram(programId);
  glValidateProgram(programId);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return programId;
}

GlUtils::Program::Program(std::filesystem::path shadersPath)
{
  auto sources = parseShaderString(shadersPath);
  this->id = createProgram(sources);
}

void GlUtils::Program::use() const
{
  glUseProgram(id);
}

int GlUtils::BufferData::addSquare(SquareBufferData square)
{
  squares[counter] = square;
  return counter++;
}

int GlUtils::BufferData::getIndicesSize()
{
  return static_cast<int>(ibo.indices.size());
}

void GlUtils::BufferData::loadBuffers(int sideSize)
{
  if (vbo.id > 0 && ibo.id > 0)
    return;
  vbo.genBuffer();
  ibo.genBuffer();

  for (auto& squarePair : squares)
  {
    VertexAttributes vaTopLeft, vaTopRight;
    VertexAttributes vaBotLeft, vaBotRight;
    vaTopLeft.loadFromSquare(squarePair.second, 0, sideSize);
    vaTopRight.loadFromSquare(squarePair.second, 1, sideSize);
    vaBotRight.loadFromSquare(squarePair.second, 2, sideSize);
    vaBotLeft.loadFromSquare(squarePair.second, 3, sideSize);
    vbo.addVertex(vaTopLeft);
    vbo.addVertex(vaTopRight);
    vbo.addVertex(vaBotRight);
    vbo.addVertex(vaBotLeft);

    ibo.indices.push_back(squarePair.first * 4 + 0);
    ibo.indices.push_back(squarePair.first * 4 + 1);
    ibo.indices.push_back(squarePair.first * 4 + 2);
    ibo.indices.push_back(squarePair.first * 4 + 2);
    ibo.indices.push_back(squarePair.first * 4 + 3);
    ibo.indices.push_back(squarePair.first * 4 + 0);
  }
  vbo.bindBuffer();
  vbo.populateBuffer();

  ibo.bindBuffer();
  ibo.populateBuffer();
}

void GlUtils::VertexBufferObject::genBuffer()
{
  _genBuffers(id);
}

void GlUtils::VertexBufferObject::bindBuffer()
{
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void GlUtils::VertexBufferObject::addVertex(VertexAttributes va)
{
  vertices.push_back(va);
}

void GlUtils::VertexBufferObject::populateBuffer()
{
  int size = (int)vertices.size() * sizeof(VertexAttributes);
  glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

  // TODO: remove attributes settings
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (void*)offsetof(VertexAttributes, x));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttributes), (void*)offsetof(VertexAttributes, red));
}

void GlUtils::IndexBufferObject::genBuffer()
{
  _genBuffers(id);
}

void GlUtils::IndexBufferObject::bindBuffer()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void GlUtils::IndexBufferObject::populateBuffer()
{
  int size = (int)indices.size() * sizeof(unsigned int);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), GL_STATIC_DRAW);
}

void GlUtils::VertexAttributes::loadFromSquare(SquareBufferData& data, int index, int sideSize)
{
  Coordinate coord;
  if (index == 0)
    coord = data.topLeft;
  else if (index == 1)
    coord = data.topRight;
  else if (index == 2)
    coord = data.botRight;
  else if (index == 3)
    coord = data.botLeft;
  x = 2.0F * (float)coord.x() / (float)sideSize - 1.0F;
  y = -2.0F * (float)coord.y() / (float)sideSize + 1.0F;
  auto colorsF = data.color.getColorsF();
  red = colorsF[0];
  green = colorsF[1];
  blue = colorsF[2];
}
