#pragma once

#ifndef VFS_HPP
#define VFS_HPP

#include "VfsNode.hpp"

class Vfs
{
    private:
        Hcl::Vector<MountPoint*> _mount;
        Vfs();

    public:
        static Vfs* getInstance();
        VfsNode getNode(Hcl::String);
}

#endif // VFS_HPP