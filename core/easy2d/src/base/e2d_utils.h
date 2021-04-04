#ifndef UTILS_H
#define UTILS_H

namespace Easy2D
{
    static const int32 NO_WRAPPING = -1;
    static const String TAB = _T("    ");
    static const String EMPTY_STRING = _T("");

    template <typename T, typename U = uint8>
    struct PointerArray
    {
        U amount;
        T* elements;
    };

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
