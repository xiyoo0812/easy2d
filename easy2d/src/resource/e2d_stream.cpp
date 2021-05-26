#include "e2d_stream.h"
#include "e2d_filesystem.h"

using namespace Easy2D;

Stream::Stream()
{

}

Stream::Stream(const Bytes& data)
{
    set(data.data(), data.size());
}

Stream::Stream(const uchar* data, size_t size)
{
    set(data, size);
}

Stream::~Stream()
{
    safeDeleteArray(mData);
}

size_t Stream::read(Bytes& dst, size_t size)
{
    if (size == 0)
    {
        size = mDataSize;
    }
    size_t readSize = std::min(size, mDataSize - mCurPos);
    if (readSize > 0)
    {
        dst.resize(readSize);
        memcpy((char*)dst.data(), (char*)(mData + mCurPos), readSize);
        mCurPos += readSize;
    }
    return readSize;
}


uchar* Stream::data() const
{
    return mData;
}

size_t Stream::size() const
{
    return mDataSize;
}

void Stream::seek(uint64 pos, int whence)
{
    switch (whence) {
    case SEEK_SET:
        mCurPos = std::max(pos, mDataSize);
        break;
    case SEEK_CUR:
        mCurPos = std::max(mCurPos + pos, mDataSize);
        break;
    case SEEK_END:
        mCurPos = mDataSize - std::max(pos, mDataSize);
        break;
    }
}

size_t Stream::tell() const
{
    return mCurPos;
}

void Stream::set(const BYTE* data, size_t size)
{
    if (size > 0)
    {
        safeDeleteArray(mData);
        mData = new uchar[size];
        memcpy(mData, data, size);
        mDataSize = size;
        mCurPos = 0;
    }
}

FileStream::FileStream(const Path& path)
{
    auto data = FileSystem::readFile(path);
    set(data.data(), data.size());
}

FileStream::~FileStream()
{
}
