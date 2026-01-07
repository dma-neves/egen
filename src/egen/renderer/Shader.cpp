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
    std::string common_vertex_shader_source = load_file(common_shader_path/"common.vert");
    std::string common_fragment_shader_source = load_file(common_shader_path/"common.frag");
    std::string common_light_fragment_shader_source = load_file(common_shader_path/"light.frag");
    std::string vertex_shader_source = load_file(vertex_shader_path);
    std::string fragment_shader_source = load_file(fragment_shader_path);

    const char* common_vertex_shader_source_c_str = common_vertex_shader_source.c_str();
    const char* common_fragment_shader_source_c_str = common_fragment_shader_source.c_str();
    const char* common_light_fragment_shader_source_c_str = common_light_fragment_shader_source.c_str();
    const char* vertex_shader_source_c_str = vertex_shader_source.c_str();
    const char* fragment_shader_source_c_str = fragment_shader_source.c_str();

    int success;
    char info_log[512];

    // Compile Common Vertex Shader
    GLuint common_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(common_vertex_shader, 1, &common_vertex_shader_source_c_str, NULL);
    glCompileShader(common_vertex_shader);
    glGetShaderiv(common_vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(common_vertex_shader, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile common vertex shader [") + (common_shader_path/"common.vert").string() + "]" + info_log);
    }

    // Compile Vertex Shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source_c_str, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile vertex shader [") + std::string(vertex_shader_path) + std::string("]") + info_log);
    }

    // Compile Common Fragment Shader
    GLuint common_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(common_fragment_shader, 1, &common_fragment_shader_source_c_str, NULL);
    glCompileShader(common_fragment_shader);
    glGetShaderiv(common_fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(common_fragment_shader, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile common fragment shader [") + (common_shader_path/"common.frag").string() + "]" + info_log);
    }

    // Compile Common Light Fragment Shader
    GLuint common_light_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(common_light_fragment_shader, 1, &common_light_fragment_shader_source_c_str, NULL);
    glCompileShader(common_light_fragment_shader);
    glGetShaderiv(common_light_fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(common_light_fragment_shader, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile common light fragment shader [") + (common_shader_path/"light.frag").string() + "]" + info_log);
    }

    // Compile Fragment Shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source_c_str, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        throw std::runtime_error(std::string("Failed to compile fragment shader [") + std::string(fragment_shader_path) + std::string("]") + info_log);
    }

    // Create Shader Program, attach previous shaders, and link the shaders
    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, common_vertex_shader);
    glAttachShader(m_shader_program, vertex_shader);
    glAttachShader(m_shader_program, common_fragment_shader);
    glAttachShader(m_shader_program, common_light_fragment_shader);
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
    glDeleteShader(common_vertex_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(common_fragment_shader);
    glDeleteShader(common_light_fragment_shader);
    glDeleteShader(fragment_shader);
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
