#include "shader.h"
#include <array>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <iostream>

unsigned int GLElements::Shader::getUniformLocation(const std::string& name)
{
  if (uniformLocations.find(name) != uniformLocations.end())
    return uniformLocations[name];

  int location = glGetUniformLocation(programId, name.c_str());
  if (location == -1)
    std::cout << "W: uniform " << name << " doesn't being used!" << std::endl;

  uniformLocations[name] = location;
  return location;
}

std::pair<std::string, std::string> GLElements::Shader::parseShaderString(const std::filesystem::path& path)
{
  std::array<std::string, 2> shaderNames = { {"vertex.glsl", "fragment.glsl"} };
  std::stringstream ss[2];
  for (int i = 0; i < 2; i++)
  {
    std::filesystem::path shader = std::filesystem::path{ path }.append(shaderNames[i]);
    std::ifstream stream(shader);
    std::string line;
    while (getline(stream, line))
    {
      ss[i] << line << std::endl;
    }
  }


  return { ss[0].str(), ss[1].str() };
}

unsigned int GLElements::Shader::compileShader(unsigned int type, std::string source)
{
  unsigned int id = glCreateShader(type);
  auto sourceC = source.c_str();
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

unsigned int GLElements::Shader::createProgram(const std::pair<std::string, std::string>& sources)
{
  unsigned int programId = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, sources.first);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, sources.second);

  glAttachShader(programId, vs);
  glAttachShader(programId, fs);
  glLinkProgram(programId);
  int result;
  glGetProgramiv(programId, GL_LINK_STATUS, &result);
  if (!result)
  {
    int len;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len);
    char* message = new char[len];
    glGetProgramInfoLog(programId, len, &len, message);
    std::cerr << message << std::endl;
    glDeleteProgram(programId);
    programId = 0;
    delete[] message;
  }
  //glValidateProgram(programId);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return programId;
}

GLElements::Shader::Shader()
{
  programId = 0;
}

GLElements::Shader::Shader(const std::filesystem::path& shadersPath)
{
  auto shadersSouce = parseShaderString(shadersPath);
  this->programId = createProgram(shadersSouce);
}

void GLElements::Shader::freeProgram()
{
  glDeleteProgram(programId);
}

void GLElements::Shader::bind() const
{
  glUseProgram(programId);
}

void GLElements::Shader::unbind() const
{
  glUseProgram(0);
}

void GLElements::Shader::setUniform1i(const std::string& name, int i)
{
  glUniform1i(getUniformLocation(name), i);
}
