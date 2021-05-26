#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "e2d_config.h"

namespace Easy2D
{
    class FileSystem
    {
    public:
        static bool exists(const Path& p);
        static bool createDir(const Path& p);
        static bool createParentDir(const Path& p);

        static int64_t getLastWriteTime(const Path& p);
        static bool isFile(const Path& p);
        static bool isDirectory(const Path& p);

        static void copyFile(const Path& src, const Path& dst);
        static bool remove(const Path& path);

        static void writeFile(const Path& path, const char* data, size_t length);
        static void writeFile(const Path& path, const Bytes& data);
        static void writeFile(const Path& path, const String& data);
        static Bytes readFile(const Path& path);

        static Vector<Path> enumerateDirectory(const Path& path, bool full = true);

        static Path getRelative(const Path& path, const Path& parentPath);
        static Path getAbsolute(const Path& path);

        static size_t fileSize(const Path& path);

        static Path getTemporaryPath();
    };
}

#endif
