#include "egen/filesystem/ImageFile.hpp"

#include "platform/stb/stb_image.hpp"

namespace egen
{

ImageFile::ImageFile(File file) : File(file.path())
{

}

ImageFile::ImageFile(std::string path) : File(path)
{

}

ImageFile::ImageFile() : File()
{

}

const char* ImageFile::failure_reason() const
{
    return stbi_failure_reason();
}


unsigned char* ImageFile::read(int& width, int& height, int& n_channels) const
{
    if(!valid())
    {
        nullptr;
    }

    std::string real_path = m_path.string();
    const char* real_path_c_str = real_path.c_str();
    return stbi_load(real_path_c_str, &width, &height, &n_channels, 0);
}

void ImageFile::free(unsigned char* dst) const
{
    stbi_image_free(dst);
}

}

