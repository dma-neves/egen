#include "egen/renderer/Texture.hpp"
#include "platform/stb/stb_image.hpp"

namespace egen
{

Texture::Texture(const std::filesystem::path& texture_path)
{
    std::string texture_path_str = texture_path.string();
    const char* texture_path_c_str = texture_path_str.c_str();
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, n_channels;
    unsigned char *data = stbi_load(texture_path_c_str, &width, &height, &n_channels, 0);
    if (data)
    {
        GLenum format = (n_channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        const char* failure_reason = stbi_failure_reason();

        throw std::runtime_error(std::string("Failed to loadimage ") + texture_path.string() + std::string(". Failure reason: ") + failure_reason);
    }
    stbi_image_free(data);
}

GLuint Texture::get()
{
    return m_texture;
}

}