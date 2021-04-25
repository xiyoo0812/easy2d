#ifndef UTILS_H
#define UTILS_H

namespace Easy2D
{
    enum class HorizontalAlign : byte
    {
        Left = 0,
        Center,
        Right
    };

    enum class VerticalAlign : byte
    {
        Bottom = 0,
        Center,
        Top
    };

    enum class DockerAlign : byte
    {
        Top = 0,
        Left,
        Right,
        Bottom,
        Center,
        LeftTop,
        LeftBottom,
        RightTop,
        RightBottom,
    };

    template <typename T>
    inline void safeDelete(T*& pointer)
    {
        if (pointer != nullptr)
        {
            delete pointer;
            pointer = nullptr;
        }
    }

    template <typename T>
    inline void safeDeleteArray(T*& array)
    {
        if (array != nullptr)
        {
            delete[] array;
            array = nullptr;
        }
    }
};

#endif
