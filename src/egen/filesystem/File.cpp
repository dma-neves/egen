#include "egen/filesystem/File.hpp"

#include <fstream>

namespace egen
{
    File::File(std::string path) : m_path(path)
    {
    }

    File::File() : m_path("")
    {
    }

    size_t File::read(char* dst, size_t bytes) const
    {
        if(!valid())
        {
            return 0;
        }

        std::ifstream file(m_path, std::ios::in | std::ios::binary);
        if(!file)
        {
            return 0;
        }

        file.read(static_cast<char*>(dst), bytes);
        return static_cast<size_t>(file.gcount());
    }

    size_t File::size() const
    {
        if(!valid())
        {
            return 0;
        }

        return std::filesystem::file_size(m_path);
    }

    bool File::valid() const
    {
        return !m_path.empty() && std::filesystem::exists(m_path) && std::filesystem::is_regular_file(m_path);
    }

    std::string File::path() const
    {
        return m_path.string();
    }
}