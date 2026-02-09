#pragma once

#include <string>
#include <filesystem>

namespace egen
{

class File
{
public:

    File(std::string path);
    File();

    size_t read(char* dst, size_t bytes) const;
    size_t size() const;
    bool valid() const;
    std::string path() const;

protected:
    std::filesystem::path m_path;
};

}