#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <functional>
#include <filesystem>
#include <unordered_map>
//OpenGL Math Library
#include "glm\glm.h"
#include "glm\ext.hpp"

namespace Easy2D
{
    //unsigned types
    typedef unsigned char       uchar;
    typedef unsigned short      ushort;
    typedef unsigned int        uint;
    typedef unsigned long       ulong;

    //char types
    typedef char                char8;
    typedef short               char16;
    typedef int                 char32;
    typedef unsigned char       uchar8;
    typedef unsigned short      uchar16;
    typedef unsigned int        uchar32;

    //bit types
    typedef unsigned char       BYTE;
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
    typedef std::string             String;
    typedef std::filesystem::path   Path;

    template <typename T> 
    using WPtr = std::weak_ptr<T>;
    using NewWPtr = std::make_weak<T>;
    template <typename T> 
    using SPtr = std::shared_ptr<T>;
    using NewSPtr = std::make_shared<T>;
    template <typename T>
    using UPtr = std::unique_ptr<T>;
    using NewUPtr = std::make_unique<T>;
    template <typename F>
    using Function = std::function<F>;
    template <typename T>
    using Vector = std::vector<T>;
    template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
    using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual>;

    using RandIntDist   = std::uniform_int_distribution<int>;

    template <typename T>
	inline void SafeDelete(T * &pointer)
	{
		if(pointer != nullptr)
		{
			delete pointer;
			pointer = nullptr;
		}
	}

    using std::min;
    using std::max;

    //gl math library
    typedef glm::ivec2 ivec2;
    typedef glm::ivec3 ivec3;
    typedef glm::ivec4 ivec4;

    typedef glm::uvec2 uvec2;
    typedef glm::uvec3 uvec3;
    typedef glm::uvec4 uvec4;

    typedef glm::fvec2 fvec2;
    typedef glm::fvec3 fvec3;
    typedef glm::fvec4 fvec4;

    typedef glm::dvec2 dvec2;
    typedef glm::dvec3 dvec3;
    typedef glm::dvec4 dvec4;

    typedef glm::fquat fquat;
    typedef glm::dquat dquat;

    typedef glm::fmat2 fmat2;
    typedef glm::fmat3 fmat3;
    typedef glm::fmat4 fmat4;

    typedef glm::dmat2 dmat2;
    typedef glm::dmat3 dmat3;
    typedef glm::dmat4 dmat4;

    typedef fvec2 vec2;
    typedef fvec3 vec3;
    typedef fvec4 vec4;

    typedef fquat quat;

    typedef fmat2 mat2;
    typedef fmat3 mat3;
    typedef fmat4 mat4;

    const float64 PI = 3.14159265358979323846264338327950288;
    const float32 EPSILON = 0.0000001f;
};

#endif