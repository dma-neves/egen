#include "egen/filesystem/vfs.hpp"

namespace egen
{
    void VFS::mount(std::string virtual_path, std::string real_path)
    {
        if (!real_path.empty() && real_path.back() != '/')
        {
            real_path += '/';
        }

        m_mounts.insert({virtual_path, real_path});
    }

    bool VFS::is_mounted(std::string virtual_path) const
    {
        auto it = m_mounts.find(virtual_path);
        return it != m_mounts.end();
    }

    File VFS::open(std::string virutal_path) const
    {
        auto mount_pos = virutal_path.find("://");
        if(mount_pos == std::string::npos)
        {
            return File{};
        }

        std::string mount_name = virutal_path.substr(0, mount_pos);
        std::string relative_path = virutal_path.substr(mount_pos + 3);
        
        auto it = m_mounts.find(mount_name);
        if(it == m_mounts.end())
        {
            return File{};
        }
        else
        {
            std::string mount_value = it->second;
            std::string real_path = mount_value + relative_path;
            return File(real_path);
        }
    }
}