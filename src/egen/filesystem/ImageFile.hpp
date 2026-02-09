#pragma once

#include <string>
#include <filesystem>

#include "egen/filesystem/File.hpp"

namespace egen
{

class ImageFile : public File
{
public:

    ImageFile(File file);
    ImageFile(std::string path);
    ImageFile();

    unsigned char* read(int& width, int& height, int& n_channels) const;
    const char* failure_reason() const;
    void free(unsigned char* dst) const;
};

}