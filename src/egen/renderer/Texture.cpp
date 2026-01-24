#include "egen/renderer/Texture.hpp"
#include "egen/filesystem/ImageFile.hpp"

namespace egen
{

Texture::Texture(const VFS& vfs, const std::string& texture_path)
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, n_channels;
    ImageFile texture_file = vfs.open(texture_path);
    if(!texture_file.valid())
    {
        throw new std::runtime_error(std::string("Failed to open " + texture_file.path()));
    }
    unsigned char* data = texture_file.read(width, height, n_channels);

    if (data)
    {
        GLenum format = (n_channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        texture_file.free(data);
    }
    else
    {
        const char* failure_reason = texture_file.failure_reason();
        throw std::runtime_error(std::string("Failed to loadimage ") + texture_file.path() + std::string(". Failure reason: ") + failure_reason);
    }
}

GLuint Texture::get()
{
    return m_texture;
}

}