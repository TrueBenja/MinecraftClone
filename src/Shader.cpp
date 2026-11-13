#include "Shader.hpp"

#include "../include/glad/glad.h"

#include <print>

namespace Clone
{
Shader::Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    // Ensures ifstream can throw exceptions
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vertexShaderStream, fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::println(std::cerr, "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n{}", e.what());
    }

    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();

    uint32_t vertex, fragment;
    int32_t success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::println(std::cerr, "ERROR::SHADER::VERTEX_COMPILATION_FAILED\n{}", infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::println(std::cerr, "ERROR::SHADER::FRAGMENT_COMPILATION_FAILED\n{}", infoLog);
    }

    Id = glCreateProgram();
    glAttachShader(Id, vertex);
    glAttachShader(Id, fragment);
    glLinkProgram(Id);

    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(Id, 512, nullptr, infoLog);
        std::println(std::cerr, "ERROR::SHADER::PROGRAM_LINKING_FAILED\n{}", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(Id);
}

void Shader::SetBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(Id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
} // namespace Clone
