#include "shader.h"
#include <array>
#include <sstream>
#include <fstream>
#include <iostream>
#include <gl_headers.h>

unsigned int GLObj::Shader::getUniformLocation(const std::string& name)
{
  if (uniformLocations.find(name) != uniformLocations.end())
    return uniformLocations[name];

  GLCall(int location = glGetUniformLocation(programId, name.c_str()));
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
  GLCall(unsigned int id = glCreateShader(type));
  auto sourceC = source.c_str();
  GLCall(glShaderSource(id, 1, &sourceC, nullptr));
  GLCall(glCompileShader(id));

  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  if (!result)
  {
    int len;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));
    char* message = new char[len];
    GLCall(glGetShaderInfoLog(id, len, &len, message));
    std::cerr << message << std::endl;
    GLCall(glDeleteShader(id));
    delete[] message;
    return 0;
  }

  return id;
}

unsigned int GLObj::Shader::createProgram(const std::pair<std::string, std::string>& sources)
{
  GLCall(unsigned int programId = glCreateProgram());
  GLCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, sources.first));
  GLCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, sources.second));

  GLCall(glAttachShader(programId, vs));
  GLCall(glAttachShader(programId, fs));
  GLCall(glLinkProgram(programId));
  int result;
  GLCall(glGetProgramiv(programId, GL_LINK_STATUS, &result));
  if (!result)
  {
    int len;
    GLCall(glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len));
    char* message = new char[len];
    GLCall(glGetProgramInfoLog(programId, len, &len, message));
    std::cerr << message << std::endl;
    GLCall(glDeleteProgram(programId));
    programId = 0;
    delete[] message;
  }
  //glValidateProgram(programId);

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return programId;
}

GLObj::Shader::Shader(const std::filesystem::path& path, const std::string& vertexShaderName, const std::string& fragmentShaderName)
{
  auto shadersSouce = parseShaderString(path, vertexShaderName, fragmentShaderName);
  this->programId = createProgram(shadersSouce);
}

void GLObj::Shader::freeProgram()
{
  GLCall(glDeleteProgram(programId));
}

void GLObj::Shader::bind() const
{
  GLCall(glUseProgram(programId));
}

void GLObj::Shader::unbind() const
{
  GLCall(glUseProgram(0));
}

void GLObj::Shader::setUniform1i(const std::string& name, int i)
{
  GLCall(glUniform1i(getUniformLocation(name), i));
}

void GLObj::Shader::setUniform1iv(const std::string& name, int i, const int* data)
{
  GLCall(glUniform1iv(getUniformLocation(name), i, data));
}

void GLObj::Shader::setUniform3f(const std::string& name, float f0, float f1, float f2)
{
  GLCall(glUniform3f(getUniformLocation(name), f0, f1, f2));
}
