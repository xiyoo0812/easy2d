#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <set>
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <filesystem>
#include <unordered_map>
//OpenGL Math Library
#include "glm.h"
#include "ext.hpp"

namespace Easy2D
{
    //unsigned types
    typedef unsigned char       uchar;
    typedef unsigned short      ushort;
    typedef unsigned int        uint;
    typedef unsigned long       ulong;
    typedef void*               handle;

    //char types
    typedef char                char8;
    typedef short               char16;
    typedef int                 char32;
    typedef unsigned char       uchar8;
    typedef unsigned short      uchar16;
    typedef unsigned int        uchar32;

    //bit types
    typedef unsigned char       byte;
    typedef unsigned short      byte16;
    typedef int8_t              lay;

    //int
    typedef char                int8;
    typedef short               int16;
    typedef int                 int32;
    typedef long long           int64;
    typedef unsigned char       uint8;
    typedef unsigned short      uint16;
    typedef unsigned int        uint32;
    typedef unsigned long long  uint64;

    typedef float               float32;
    typedef double              float64;
    typedef long double         float128;

    //std
    using std::min;
    using std::max;
    using String = std::string;
    using Wtring = std::wstring;
	using Bytes = std::vector<byte>;
	using Path = std::filesystem::path;

    template <typename T>
    using WPtr = std::weak_ptr<T>;
    template <typename T>
    using SPtr = std::shared_ptr<T>;
    template <typename T>
    using UPtr = std::unique_ptr<T>;
    template <typename F>
    using Function = std::function<F>;
    template <typename T>
    using Vector = std::vector<T>;
    template <typename T>
    using List = std::list<T>;
    template <typename T>
    using Set = std::set<T>;
    template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
    using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual>;

    //gl math library
    typedef glm::ivec2 Vec2i;
    typedef glm::ivec3 Vec3i;
    typedef glm::ivec4 Vec4i;

    typedef glm::fvec2 Vec2f;
    typedef glm::fvec3 Vec3f;
    typedef glm::fvec4 Vec4f;

    typedef glm::fquat Quatf;

    typedef glm::fmat2 Mat2f;
    typedef glm::fmat3 Mat3f;
    typedef glm::fmat4 Mat4f;

    typedef Vec2f Vec2;
    typedef Vec3f Vec3;
    typedef Vec4f Vec4;

    typedef Quatf Quat;

    typedef Mat2f Mat2;
    typedef Mat3f Mat3;
    typedef Mat4f Mat4;

    const Vec2 VEC2_ZERO = Vec2(0, 0);
    const Vec3 VEC3_ZERO = Vec3(0, 0, 0);
    const Vec4 VEC4_ZERO = Vec4(0, 0, 0, 0);

    const float32 PI        = float32(3.141592);
    const float32 EPSILON   = 0.0000001f;
};

#endif
