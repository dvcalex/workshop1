#pragma once

#include <glad/gl.h>
#include <string>

namespace shader
{
std::string readFile(const std::string& path);
GLuint compileShader(GLenum type, const std::string& source);
GLuint createProgram(const std::string& vertPath, const std::string& fragPath);
} // namespace shader
