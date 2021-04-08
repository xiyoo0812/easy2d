#include <chrono>
#include <fstream>
#include "math/e2d_math.h"
#include "e2d_filesystem.h"

using namespace Easy2D;
using namespace std::chrono;
using namespace std::filesystem;

bool FileSystem::exists(const Path& p)
{
    return ::exists(p);
}

bool FileSystem::createDir(const Path& p)
{
    try
    {
        if (!exists(p))
        {
            return create_directories(p);
        }
        else
        {
            return false;
        }
    }
    catch (...)
    {
        return false;
    }
}

bool FileSystem::createParentDir(const Path& p)
{
    return createDir(p.parent_path().string());
}

int64_t FileSystem::getLastWriteTime(const Path& p)
{
    std::error_code ec;
    const auto ftime = last_write_time(p, ec);
    auto sctp = time_point_cast<system_clock::duration>(ftime - decltype(ftime)::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

bool FileSystem::isFile(const Path& p)
{
    return is_regular_file(p);
}

bool FileSystem::isDirectory(const Path& p)
{
    return is_directory(p);
}

void FileSystem::copyFile(const Path& src, const Path& dst)
{
    createParentDir(dst);
    copy_file(src, src, copy_options::overwrite_existing);
}

bool FileSystem::remove(const Path& path)
{
    std::error_code ec;
    int nRemoved = std::filesystem::remove_all(path, ec) > 0;
    return nRemoved > 0 && ec.value() == 0;
}

void FileSystem::writeFile(const Path& path, const char* data, size_t length)
{
    createParentDir(path);
    std::ofstream fp(path.string(), std::ios::binary | std::ios::out);
    fp.write(data, length);
    fp.close();
}

void FileSystem::writeFile(const Path& path, const Bytes& data)
{
    writeFile(path, (const char*)data[0], data.size());
}

void FileSystem::writeFile(const Path& path, const String& data)
{
    writeFile(path, data.c_str(), data.length());
}

Bytes FileSystem::readFile(const Path& path)
{
    Bytes result;
    std::ifstream fp(path.string(), std::ios::binary | std::ios::in);
    if (!fp.is_open())
    {
        return result;
    }
    fp.seekg(0, std::ios::end);
    size_t size = fp.tellg();
    fp.seekg(0, std::ios::beg);
    result.resize(size);
    fp.read(reinterpret_cast<char*>(result.data()), size);
    fp.close();
    return result;
}

Vector<Path> FileSystem::enumerateDirectory(const Path& dir, bool full)
{
    Vector<Path> result;
    if (exists(dir))
    {
        using RDI = recursive_directory_iterator;
        RDI end;
        for (RDI i(dir); i != end; ++i)
        {
            Path fullPath = i->path();
            if (is_regular_file(fullPath.native()))
            {
                result.push_back(full ? fullPath : fullPath.lexically_relative(dir));
            }
        }
    }
    return result;
}

Path FileSystem::getRelative(const Path& path, const Path& parentPath)
{
    return relative(path, parentPath);
}

Path FileSystem::getAbsolute(const Path& path)
{
    return path.lexically_normal().string();
}

size_t FileSystem::fileSize(const Path& path)
{
    return file_size(path);
}

Path FileSystem::getTemporaryPath()
{
    std::array<char, 16> name;
    const std::array<char, 16> digits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    for (size_t i = 0; i < name.size(); ++i)
    {
        name[i] = digits[random(0, 15)];
    }
    return Path(temp_directory_path().string()) / Path(String(name.data(), name.size()).c_str());
}
