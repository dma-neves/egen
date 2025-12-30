#pragma once

#include <filesystem>
#include <cstdint>

#include "opengl/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

namespace egen
{

class Shader
{
public:
    Shader(const std::filesystem::path& vertex_shader_path, const std::filesystem::path& fragment_shader_path);

    GLuint program();

private:
    GLuint m_shader_program;
};

}