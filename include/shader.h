#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>

namespace GLElements
{
  class Shader
  {
  private:
    unsigned int programId;
    std::unordered_map<std::string, int> uniformLocations;

    unsigned int getUniformLocation(const std::string& name);

    std::pair<std::string, std::string> parseShaderString(const std::filesystem::path& path);

    unsigned int compileShader(unsigned int type, std::string source);

    unsigned int createProgram(const  std::pair<std::string, std::string>& sources);

  public:
    Shader();
    Shader(const std::filesystem::path& shadersPath);
    void freeProgram();

    void bind() const;
    void unbind() const;

    void setUniform1i(const std::string& name, int i);
  };
}