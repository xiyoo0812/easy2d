#include "e2d_timer_mgr.h"
#include <chrono>

/* Easy2D */
using namespace Easy2D;
using namespace std::chrono;


TimerManager::TimerManager()
{
}

void TimerManager::update(const uint32& escapeMs)
{
    for (auto it = mTimers.begin(); it != mTimers.end(); )
    {
        Timer& timer = it->second;
        if (timer.mTimes == 0)
        {
            mTimers.erase(it++);
            continue;
        }
        if (!timer.mPause)
        {
            timer.mEscape += escapeMs;
            if (timer.mEscape >= timer.mPeriod)
            {
                if (timer.mTimes > 0)
                {
                    timer.mTimes -= ::floor(timer.mEscape / timer.mPeriod);
                    if (timer.mTimes < 0)
                    {
                        timer.mTimes = 0;
                    }
                }
                timer.mEscape %= timer.mPeriod;
                timer.mCallback(timer.mEscape);
            }
        }
        ++it;
    }
}

bool TimerManager::createTimer(const String& name, uint32 interval, uint32 period, uint32 times, TimerFunc callback)
{
    auto it = mTimers.find(name);
    if (it != mTimers.end())
    {
        return false;
    }
    mTimers.insert(std::make_pair(name, Timer(name, interval, period, times, callback)));
    return true;
}

bool TimerManager::once(const String& name, uint32 interval, TimerFunc callback)
{
    return createTimer(name, interval, 0, 1, callback);
}

bool TimerManager::loop(const String& name, uint32 period, TimerFunc callback)
{
    return createTimer(name, period, period, -1, callback);
}

bool TimerManager::removeTimer(const String& name)
{
    auto it = mTimers.find(name);
    if (it != mTimers.end())
    {
        mTimers.erase(it);
        return true;
    }
    return false;
}

void TimerManager::pauseTimer(const String& name)
{
    auto it = mTimers.find(name);
    if (it != mTimers.end())
    {
        it->second.mPause = true;
    }
}

void TimerManager::resumeTimer(const String& name)
{
    auto it = mTimers.find(name);
    if (it != mTimers.end())
    {
        Timer& timer = it->second;
        timer.mPause = false;
        timer.mEscape = 0;
    }
}

time_t TimerManager::systemTime() const
{
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

time_t TimerManager::systemTimeMs() const
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
