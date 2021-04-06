#ifndef READER_H
#define READER_H

#include "e2d_config.h"

namespace Easy2D
{
    class DataStream
    {
    public:
        DataStream();
        DataStream(const Bytes& data);
        DataStream(const BYTE* data, size_t size);
        virtual ~DataStream();
        virtual size_t tell() const;
        virtual size_t read(Bytes& dst, size_t size = 0);
        virtual void seek(uint64 pos, int whence);
        virtual void set(const BYTE* data, size_t size);

    protected:
        Bytes mData = {};
        size_t mDataSize = 0;
        size_t mCurPos = 0;
    };

    class FileStream : public DataStream
    {
    public:
        FileStream(const Path& path);
        virtual ~FileStream();
    };
}

#endif
