#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>

namespace GLObj
{
  class Shader
  {
  private:
    unsigned int programId;
    std::unordered_map<std::string, int> uniformLocations;

    unsigned int getUniformLocation(const std::string& name);

    std::pair<std::string, std::string> parseShaderString(const std::filesystem::path& path, const std::string& vertexShaderName, const std::string& fragmentShaderName);

    unsigned int compileShader(unsigned int type, std::string source);

    unsigned int createProgram(const  std::pair<std::string, std::string>& sources);

  public:
    Shader(const std::filesystem::path& shadersPath, const std::string& vertexShaderName, const std::string& fragmentShaderName);
    void freeProgram();

    void bind() const;
    void unbind() const;

    unsigned int getId() { return programId; }

    void setUniform1i(const std::string& name, int i);
    void setUniform1iv(const std::string& name, int i, const int* data);
    void setUniform3f(const std::string& name, float f0, float f1, float f2);
  };
}