#pragma once

#include <filesystem>
#include <cstdint>
#include <unordered_map>

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
    GLuint m_shader_program;
    std::unordered_map<std::string, GLint> m_uniform_cache;
    GLint get_uniform_location(const std::string& name);
};

}
