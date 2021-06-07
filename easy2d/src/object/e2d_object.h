
#ifndef OBJECT_H
#define OBJECT_H

#include "e2d_config.h"

namespace Easy2D
{
    // 子类需要调用shared_from_this()
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object();
        Object(const String& name);
        virtual ~Object();

        virtual const String& getName() const;
        void setName(const String& name);
        bool compareName(const String& name) const;

        uint64 getGUID() const;
        bool compareGUID(const uint64 guid) const;

        virtual void destroy() = 0;

    protected:
        uint64 mGUID = 0;
        String mName = "";
    };
}

#endif
