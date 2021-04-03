#ifndef UTILS_H
#define UTILS_H

namespace Easy2D
{
    template <typename T>
    inline void safeDelete(T* &pointer)
    {
        if (pointer != nullptr)
        {
            delete pointer;
            pointer = nullptr;
        }
    }

    template <typename T>
    inline void safeDeleteArray(T* &array)
    {
        if (array != nullptr)
        {
            delete[] array;
            array = nullptr;
        }
    }
};

#endif
