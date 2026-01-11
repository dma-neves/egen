#include "egen/renderer/Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

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

Shader::Shader(const std::filesystem::path& common_shader_path, const std::filesystem::path& vertex_shader_path, const std::filesystem::path& fragment_shader_path)
{

    std::filesystem::path common_vertex_shader_path = common_shader_path/"common.vert";
    std::filesystem::path common_fragment_shader_path = common_shader_path/"common.frag";
    std::filesystem::path common_light_fragment_shader_path = common_shader_path/"light.frag";

    create_program(
        compile_shader(GL_VERTEX_SHADER, common_vertex_shader_path),
        compile_shader(GL_VERTEX_SHADER, vertex_shader_path),
        compile_shader(GL_FRAGMENT_SHADER, common_fragment_shader_path),
        compile_shader(GL_FRAGMENT_SHADER, common_light_fragment_shader_path),
        compile_shader(GL_FRAGMENT_SHADER, fragment_shader_path)
    );

    set_uniform("material.ambient", default_ambient);
    set_uniform("material.diffuse", default_diffuse);
    set_uniform("material.specular", default_specular);
    set_uniform("material.shininess", default_shininess);

}

GLuint Shader::compile_shader(GLenum shader_type, const std::filesystem::path& shader_path)
{
    std::string shader_source = load_file(shader_path);
    const char* shader_source_c_str = shader_source.c_str();
    GLuint shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_source_c_str, NULL);

    int success;
    char info_log[512];
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile ") + shader_path.string() + ": " + info_log);
    }

    return shader_id;
}

GLuint Shader::program()
{
    return m_shader_program;
}

void Shader::use()
{
    glUseProgram(m_shader_program);
}

GLint Shader::get_uniform_location(const std::string& name)
{
    auto it = m_uniform_cache.find(name);
    if (it != m_uniform_cache.end()) 
    {
        return it->second;
    }
    GLint loc = glGetUniformLocation(m_shader_program, name.c_str());
    m_uniform_cache[name] = loc; // cache -1 too
    return loc;
}

}
