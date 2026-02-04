#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace shader
{
std::string readFile(const std::string& path)
{
    std::ifstream stream(path);
    std::stringstream ss;
    std::string line;

    while (getline(stream, line))
    {
        ss << line << '\n';
    }

    return ss.str();
}

GLuint compileShader(GLenum type, const std::string& source)
{
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // error handling
    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLint len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"
                  << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

GLuint createProgram(const std::string& vertPath, const std::string& fragPath)
{
    std::string vertSource = readFile(vertPath);
    std::string fragSource = readFile(fragPath);

    GLuint program = glCreateProgram();
    GLuint vertId = compileShader(GL_VERTEX_SHADER, vertSource);
    GLuint fragId = compileShader(GL_FRAGMENT_SHADER, fragSource);

    // link
    glAttachShader(program, vertId);
    glAttachShader(program, fragId);
    glLinkProgram(program);
    glValidateProgram(program);

    // cleanup
    glDeleteShader(vertId);
    glDeleteShader(fragId);

    return program;
}
} // namespace shader
