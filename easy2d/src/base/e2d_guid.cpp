#include "e2d_guid.h"
#include "e2d_timer_mgr.h"
#include "math/e2d_math.h"

/* Easy2D */
using namespace Easy2D;

uint64 Guid::newGuid(short world, short type)
{
    if (world == 0)
    {
        world = random(0, MAX_WORLD);
    }
    if (type == 0)
    {
        type = random(0, MAX_TYPE);
    }
    type %= (MAX_TYPE + 1);
    world %= (MAX_WORLD + 1);

    uint32 serial = 0;
    std::time_t ts = TimerManager::getInstance()->systemTime();
    if (ts != mLasttime)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mSerials[type] = 0;
        mLasttime = ts;
    }
    else if (serial >= MAX_SERIAL)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mSerials[type] = 0;
        mLasttime++;
    }
    else
    {
        serial = mSerials[type]++;
    }
    return MAKE_GUID(world, type, serial, ts);
}

String Guid::toString(uint64 value)
{
    return std::to_string(value);
}

uint64 Guid::toGuid(String& str)
{
    return strtoull(str.c_str(), nullptr, 10);
}
