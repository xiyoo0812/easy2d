#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <filesystem>
#include <unordered_map>

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
};

#endif