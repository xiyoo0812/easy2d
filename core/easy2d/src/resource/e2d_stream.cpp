#include "e2d_stream.h"
#include "e2d_filesystem.h"

using namespace Easy2D;

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
        size = dataSize;
    }
    size_t readSize = std::min(size, dataSize - mCurPos);
	dst.resize(readSize);
    memcpy((char*)dst[0], (char*)mData[mCurPos], readSize);
    return readSize;
}

void DataStream::seek(uint64 pos, int whence)
{
    switch (whence) {
    case SEEK_SET:
        mCurPos = std::max(pos, dataSize);
        break;
    case SEEK_CUR:
        mCurPos = std::max(mCurPos + pos);
        break;
    case SEEK_END:
        mCurPos = dataSize - std::max(pos, dataSize);
        break;
    }
}

size_t DataStream::tell() const
{
    return mCurPos;
}

void DataStream::set(const BYTE* data, size_t size)
{
    mData.clear();
	dst.resize(size);
    memcpy((char*)mData[0], data, size);
    mDataSize = size;
	mCurPos = 0;
}

FileStream::FileStream(const Path& path)
{
	mData = FileSystem::readFile(path);
}

FileStream::~FileStream()
{
}
