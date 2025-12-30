#include "renderer/Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <iostream>

namespace egen
{

static std::string load_file(const std::filesystem::path& path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if(!file)
    {
        throw std::runtime_error("Failed to open shader file: " + path.string());
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

Shader::Shader(const std::filesystem::path& vertex_shader_path, const std::filesystem::path& fragment_shader_path)
{
    std::string vertex_shader_source = load_file(vertex_shader_path);
    std::string fragment_shader_source = load_file(fragment_shader_path);

    const char* vertex_shader_source_c_str = vertex_shader_source.c_str();
    const char* fragment_shader_source_c_str = fragment_shader_source.c_str();

    // Compile Vertex Shader
    GLuint vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source_c_str, NULL);
    glCompileShader(vertex_shader);
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile vertex shader: ") + info_log);

    }

    // Compile Fragment Shader
    GLuint fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source_c_str, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile fragment shader: ") + info_log);
    }

    // Create Shader Program, attach previous shaders, and link the shaders
    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, vertex_shader);
    glAttachShader(m_shader_program, fragment_shader);
    glLinkProgram(m_shader_program);
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_shader_program, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to link shader program: ") + info_log);

    }
    // Activate the Shader Program
    glUseProgram(m_shader_program);
    // After the shaders have been linked to the program, we can delete them
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

GLuint Shader::program()
{
    return m_shader_program;
}

}