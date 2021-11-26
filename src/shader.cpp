#include "shader.h"
#include <array>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <iostream>

unsigned int GLObj::Shader::getUniformLocation(const std::string& name)
{
  if (uniformLocations.find(name) != uniformLocations.end())
    return uniformLocations[name];

  int location = glGetUniformLocation(programId, name.c_str());
  if (location == -1)
    std::cout << "W: uniform " << name << " doesn't being used!" << std::endl;

  uniformLocations[name] = location;
  return location;
}

std::pair<std::string, std::string> GLObj::Shader::parseShaderString(const std::filesystem::path& path, const std::string& vertexShaderName, const std::string& fragmentShaderName)
{
  std::array<std::string, 2> shaderNames = { {vertexShaderName, fragmentShaderName} };
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

unsigned int GLObj::Shader::compileShader(unsigned int type, std::string source)
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

unsigned int GLObj::Shader::createProgram(const std::pair<std::string, std::string>& sources)
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

GLObj::Shader::Shader(const std::filesystem::path& path, const std::string& vertexShaderName, const std::string& fragmentShaderName)
{
  auto shadersSouce = parseShaderString(path, vertexShaderName, fragmentShaderName);
  this->programId = createProgram(shadersSouce);
}

void GLObj::Shader::freeProgram()
{
  glDeleteProgram(programId);
}

void GLObj::Shader::bind() const
{
  glUseProgram(programId);
}

void GLObj::Shader::unbind() const
{
  glUseProgram(0);
}

void GLObj::Shader::setUniform1i(const std::string& name, int i)
{
  glUniform1i(getUniformLocation(name), i);
}

void GLObj::Shader::setUniform3f(const std::string& name, float f0, float f1, float f2)
{
  glUniform3f(getUniformLocation(name), f0, f1, f2);
}
