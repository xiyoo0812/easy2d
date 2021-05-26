#ifndef __GUID_H__
#define __GUID_H__

#include "e2d_config.h"
#include <mutex>

namespace Easy2D
{
    class Guid final : public Singleton<GUID>
    {
    public:
        static uint64 newGuid(short world = 0, short type = 0);
        static String toString(uint64 value);
        static uint64 toGuid(String& str);

    protected:
        inline static std::time_t mLasttime = 0;
        inline static std::mutex mMutex = std::mutex();
        inline static uint32 mSerials[0x3F] = { 0 };
    };

    #define MAX_WORLD                   0x3F
    #define MAX_TYPE                    0x3F
    #define MAX_SERIAL                  0xFFFFF
    #define MAX_TIMESTAMP               0xFFFFFFFF
    #define MAKE_GUID(w, t, s, ts)      (uint64(s) | (uint64(ts) << 20) | (uint64(t) << 52) | (uint64(w) << 58))
    #define BUILD_GUID()                Guid::newGuid()
    #define BUILD_SGUID()               Guid::toString(Guid::newGuid())
    #define NEW_GUID(world, type)       Guid::newGuid(world, type)
    #define NEW_GUID_STR(world, type)   Guid::toString(Guid::newGuid(world, type))
    #define GUID2STR(guid)              Guid::toString(guid)
    #define STR2GUID(str)               Guid::toGuid(str)

    #define GUID_WORLD(guid)            (uint32)((uint64(guid) >> 58) & MAX_WORLD)
    #define GUID_TYPE(guid)             (uint32)((uint64(guid) >> 52) & MAX_TYPE)
    #define GUID_TIMESTAMP(guid)        (uint32)((uint64(guid) >> 20) & MAX_TIMESTAMP)
    #define GUID_SERIAL(guid)           (uint32)(uint64(guid)  & MAX_SERIAL)
};


#endif
