#ifndef SINGLETON_H
#define SINGLETON_H

#include "e2d_config.h"

namespace Easy2D
{
    template<typename T>
    class Singleton
    {
    public:
        static T* instance()
        {
            if (mInatance == nullptr)
            {
                mInatance = new T;
            }
            return mInatance;
        }

        static void destroy()
        {
            if (mInatance != nullptr)
            {
                delete mInatance;
                mInatance = nullptr;
            }
        }

    protected:
        Singleton() {}
        virtual ~Singleton() {}

    private:
        inline static T* mInatance = nullptr;
    };
}

#endif
