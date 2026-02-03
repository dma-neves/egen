#include "egen/renderer/Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace egen
{

Shader::Shader(std::uint8_t common_shader_bitfield, const VFS& vfs, const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    if(common_shader_bitfield != 0x0 && !vfs.is_mounted("common-shaders"))
    {
        throw std::runtime_error("common-shaders must be mounted on vfs");
    }

    File user_vertex_shader = vfs.open(vertex_shader_path);
    File user_fragment_shader = vfs.open(fragment_shader_path);

    std::vector<GLuint> shaders = {
        compile_shader(GL_VERTEX_SHADER, user_vertex_shader),
        compile_shader(GL_FRAGMENT_SHADER, user_fragment_shader)
    };

    if(common_shader_bitfield & MVP_VERT)
    {
        File mvp_vert_shader = vfs.open("common-shaders://mvp.vert");
        shaders.push_back(compile_shader(GL_VERTEX_SHADER, mvp_vert_shader));
    }
    if(common_shader_bitfield & LIGHT_FRAG)
    {
        File light_frag_shader = vfs.open("common-shaders://light.frag");
        shaders.push_back(compile_shader(GL_FRAGMENT_SHADER, light_frag_shader));
    }

    create_program(shaders);
}

void Shader::create_program(std::vector<GLuint> shaders)
{
    int success;
    char info_log[512];
    m_shader_program = glCreateProgram();

    for(GLuint shader : shaders)
        glAttachShader(m_shader_program, shader);

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
    for(GLuint shader : shaders)
        glDeleteShader(shader);
}

GLuint Shader::compile_shader(GLenum shader_type, const File& shader_file)
{
    std::vector<char> shader_source(shader_file.size() + 1);
    shader_file.read(shader_source.data(), shader_file.size());
    shader_source.back() = '\0';
    const GLchar* source = shader_source.data();
    
    GLuint shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &source, NULL);

    int success;
    char info_log[512];
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile ") + shader_file.path() + ": " + info_log);
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
