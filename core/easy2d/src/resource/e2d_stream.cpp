#include "e2d_stream.h"
#include "e2d_filesystem.h"

using namespace Easy2D;

DataStream::DataStream()
{

}

DataStream::DataStream(const Bytes& data)
{
    mData = data;
    mDataSize = mData.size();
}

DataStream::DataStream(const BYTE* data, size_t size)
{
    set(data, size);
}

DataStream::~DataStream()
{
    mData.clear();
}

size_t DataStream::read(Bytes& dst, size_t size)
{
    if (size == 0)
    {
        size = mDataSize;
    }
    size_t readSize = std::min(size, mDataSize - mCurPos);
    if (readSize > 0)
    {
        dst.resize(readSize);
        memcpy((char*)dst.data(), (char*)(mData.data() + mCurPos), readSize);
        mCurPos + readSize;
    }
    return readSize;
}

void DataStream::seek(uint64 pos, int whence)
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

size_t DataStream::tell() const
{
    return mCurPos;
}

void DataStream::set(const BYTE* data, size_t size)
{
    if (size > 0)
    {
        mData.clear();
        mData.resize(size);
        memcpy((char*)mData.data(), data, size);
        mDataSize = size;
        mCurPos = 0;
    }
}

FileStream::FileStream(const Path& path)
{
    mData = FileSystem::readFile(path);
    mDataSize = mData.size();
}

FileStream::~FileStream()
{
}
