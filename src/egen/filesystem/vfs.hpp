#pragma once

#include <map>

#include "egen/filesystem/file.hpp"

namespace egen
{

class VFS
{
public:
    void mount(std::string virtual_path, std::string real_path);
    bool is_mounted(std::string virtual_path) const;
    File open(std::string virutal_path) const;

private:
    std::map<std::string, std::string> m_mounts;
};

}