#ifndef UTILS_H
#define UTILS_H

namespace Easy2D
{
    static const int32 NO_WRAPPING = -1;
    static const Wtring TAB = L"    ";
    static const Wtring EMPTY_STRING = L"";

    enum class HorizontalAlignment : byte
	{
		Left = 0,
		Center,
		Right
	};

	enum class VerticalAlignment : byte
	{
		Bottom = 0,
		Center,
		Top
	};

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
