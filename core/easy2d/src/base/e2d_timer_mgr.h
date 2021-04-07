#pragma once

#include "e2d_config.h"

namespace Easy2D
{
    typedef Function<void(uint64)> TimerFunc;
    class Timer
    {
    public:
        String mName;
        int32 mEscape;      //下次执行时间
        uint32 mPeriod;     //周期
        uint32 mTimes;      //执行次数
        TimerFunc mCallback;    //回调函数
        bool mPause = false;

        Timer(const String& name, uint32 interval, uint32 period, uint32 times, TimerFunc callback)
            : mName(name), mPeriod(period), mTimes(times), mCallback(callback)
        {
            mEscape = period - interval;
        }
    };

    class TimerManager final : public Singleton<TimerManager>
    {
    public:
        friend Singleton<TimerManager>;

        ~TimerManager() {}

        void update(const uint32& escapeMs);

        bool createTimer(const String& name, uint32 interval, uint32 period, uint32 times, TimerFunc callback);
        bool once(const String& name, uint32 interval, TimerFunc callback);
        bool loop(const String& name, uint32 period, TimerFunc callback);
        bool removeTimer(const String& name);
        void resumeTimer(const String& name);
        void pauseTimer(const String& name);

        time_t systemTime() const;
        time_t systemTimeMs() const;

    private:
        TimerManager();
        UnorderedMap<String, Timer> mTimers;
    };
}
