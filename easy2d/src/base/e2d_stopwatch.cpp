#include "e2d_stopwatch.h"

using namespace Easy2D;
using namespace std::chrono;

Stopwatch::Stopwatch(bool startup)
{
    if (startup)
    {
        start();
    }
}

void Stopwatch::start()
{
    if (!mbRunning)
    {
        mbRunning = true;
        mLastTime = high_resolution_clock::now();
        mStartTime = high_resolution_clock::now();
    }
}

void Stopwatch::reset()
{
    mbRunning = false;
}

time_t Stopwatch::elapsedSeconds()
{
    if (mbRunning)
    {
        mbRunning = false;
        return duration_cast<seconds>(high_resolution_clock::now() - mStartTime).count();
    }
    return 0;
}

time_t Stopwatch::elapsedMillSeconds()
{
    if (mbRunning)
    {
        mbRunning = false;
        return duration_cast<milliseconds>(high_resolution_clock::now() - mStartTime).count();
    }
    return 0;
}

time_t Stopwatch::elapsedSecondsNow()
{
    auto nowTime = high_resolution_clock::now();
    auto elapsedTime = nowTime - mStartTime;
    mStartTime = nowTime;
    return duration_cast<seconds>(elapsedTime).count();
}

time_t Stopwatch::elapsedMillSecondsNow()
{
    auto nowTime = high_resolution_clock::now();
    auto elapsedTime = nowTime - mStartTime;
    mStartTime = nowTime;
    return duration_cast<milliseconds>(elapsedTime).count();
}

bool Stopwatch::elapsedSeconds(time_t elapsedS)
{
    auto nowTime = high_resolution_clock::now();
    auto elapsedTime = nowTime - mLastTime;
    if (duration_cast<seconds>(elapsedTime).count() >= elapsedS)
    {
        mLastTime = nowTime;
        return true;
    }
    return false;
}

bool Stopwatch::elapsedMillSeconds(time_t elapsedMs)
{
    auto nowTime = high_resolution_clock::now();
    auto elapsedTime = nowTime - mLastTime;
    if (duration_cast<milliseconds>(elapsedTime).count() >= elapsedMs)
    {
        mLastTime = nowTime;
        return true;
    }
    return false;
}

StopwatchAvg::StopwatchAvg(int samples) : mSamples(samples)
{
}

void StopwatchAvg::beginSample()
{
    mStartTime = high_resolution_clock::now();
}

void StopwatchAvg::endSample()
{
    auto now = high_resolution_clock::now();
    msTaken = duration_cast<milliseconds>(now - mStartTime).count();

    msTakenAvgSamples++;
    msTakenAvgAccum += msTaken;
    if (msTakenAvgSamples >= mSamples)
    {
        msTakenAvg = int(msTakenAvgAccum / msTakenAvgSamples);
        msTakenAvgSamples = 0;
        msTakenAvgAccum = 0;
    }
}

int64_t StopwatchAvg::elapsedMillSeconds(Mode mode) const
{
    return mode == Mode::Average ? msTakenAvg : msTaken;
}
