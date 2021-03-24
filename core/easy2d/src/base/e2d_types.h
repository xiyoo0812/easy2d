#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <filesystem>
#include <unordered_map>

namespace Easy2D
{
    //unsigned types
    typedef unsigned char   uchar;
    typedef unsigned short  ushort;
    typedef unsigned int    uint;
    typedef unsigned long   ulong;
    //char types
    typedef char            char8;
    typedef unsigned char   uchar8;
    typedef short           char16;
    typedef unsigned short  uchar16;
    typedef int             char32;
    typedef unsigned int    uchar32;
    typedef unsigned char   BYTE;

    //bit types
    typedef char            int8;
    typedef short           int16;
    typedef int             int32;
    typedef long long       int64;
    //byte types
    typedef unsigned char   uint8;
    typedef unsigned short  uint16;
    typedef unsigned int    uint32;
    typedef unsigned long long uint64;

    typedef float           float32;
    typedef double          float64;
    typedef long double     float128;

    //std
    typedef std::string             String;
    typedef std::filesystem::path   Path;
    template <typename T> 
    using WPtr = std::weak_ptr<T>;
    template <typename T> 
    using SPtr = std::shared_ptr<T>;
    template <typename T> 
    using UPtr = std::unique_ptr<T>;
    template <typename F> 
    using Function = std::function<F>;
    template <class Key, class T,class Hash = std::hash<Key>,class KeyEqual = std::equal_to<Key>>
    using UnorderedMap = std::unordered_map<Key, T, Hash, KeyEqual>;
};

#endif