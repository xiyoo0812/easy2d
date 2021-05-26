#ifndef READER_H
#define READER_H

#include "e2d_config.h"

namespace Easy2D
{
    class Stream
    {
    public:
        Stream();
        Stream(const Bytes& data);
        Stream(const uchar* data, size_t size);
        virtual ~Stream();
        virtual size_t tell() const;
        virtual uchar* data() const;
        virtual size_t size() const;
        virtual size_t read(Bytes& dst, size_t size = 0);
        virtual void seek(uint64 pos, int whence);
        virtual void set(const uchar* data, size_t size);

    protected:
        uchar* mData = nullptr;
        size_t mDataSize = 0;
        size_t mCurPos = 0;
    };

    class FileStream : public Stream
    {
    public:
        FileStream(const Path& path);
        virtual ~FileStream();
    };
}

#endif
