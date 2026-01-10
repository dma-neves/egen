#pragma once

#include <filesystem>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "platform/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "egen/renderer/details/Uniform.hpp"

namespace egen
{

class Shader
{
public:
    Shader(const std::filesystem::path& common_shader_path, const std::filesystem::path& vertex_shader_path, const std::filesystem::path& fragment_shader_path);

    GLuint program();
    void use();
    
    template<typename T>
    bool set_uniform(std::string name, T value)
    {
        GLint loc = get_uniform_location(name);
        if (loc == -1)
            return false;

        details::set_uniform(loc, value);

        return true;
    }

private:
    GLuint compile_shader(GLenum shader_type, const std::filesystem::path& shader_path);
    void create_program(std::vector<GLuint>&& shaders);

    template <typename... ShaderIds>
    void create_program(ShaderIds... shaders)
    {
        int success;
        char info_log[512];
        m_shader_program = glCreateProgram();

        (glAttachShader(m_shader_program, shaders), ...);

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
        (glDeleteShader(shaders), ...);
    }

    GLuint m_shader_program;
    std::unordered_map<std::string, GLint> m_uniform_cache;
    GLint get_uniform_location(const std::string& name);
};

}
