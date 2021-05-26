#ifndef RESOURCE_H
#define RESOURCE_H

#include "e2d_config.h"

namespace Easy2D
{
    class Resource
    {
    public:
        Resource(const Path& path) :mPath(path){}

        virtual bool load() = 0;
        bool isLoad() const { return mbLoad; }
        const Path& getPath() const { return mPath; }

    protected:
        Path mPath = "";
        bool mbLoad = false;
    };
}

#endif
