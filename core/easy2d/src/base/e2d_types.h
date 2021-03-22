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

    //bit types
    typedef unsigned char   bit8;
    typedef unsigned short  bit16;
    typedef unsigned int    bit32;
    //byte types
    typedef unsigned char   byte;
    typedef unsigned short  byte2;
    typedef unsigned int    byte4;
    #if defined(_MSC_VER)
    typedef __int64         bit64;
    typedef __int64         byte16;
    #else
    typedef long long       bit64;
    typedef long long       byte16;
    #endif

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