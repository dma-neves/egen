#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "platform/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "egen/renderer/details/Uniform.hpp"
#include "egen/filesystem/vfs.hpp"

#define NONE_COMMON_SHADER 0x0
#define MVP_VERT 0x1
#define LIGHT_FRAG 0x2

namespace egen
{

class Shader
{
public:

    Shader(std::uint8_t common_shader_bitfield, const VFS& vfs, const std::string& vertex_shader_path, const std::string& fragment_shader_path);

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
    GLuint compile_shader(GLenum shader_type, const File& shader_file);
    void create_program(std::vector<GLuint> shaders);
    GLint get_uniform_location(const std::string& name);

    GLuint m_shader_program;
    std::unordered_map<std::string, GLint> m_uniform_cache;
};

}
