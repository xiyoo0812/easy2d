#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include "e2d_config.h"

namespace Easy2D
{
    class Stopwatch
    {
    public:
        Stopwatch(bool startup = true);

        void start();
        void reset();

        time_t elapsedSeconds();
        time_t elapsedMillSeconds();
        time_t elapsedSecondsNow();
        time_t elapsedMillSecondsNow();
        bool elapsedSeconds(time_t elapsedS);
        bool elapsedMillSeconds(time_t elapsedMs);

    private:
        bool mbRunning = false;
        std::chrono::time_point<std::chrono::high_resolution_clock> mLastTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;

    public:
        inline static time_t SECOND = 1;
        inline static time_t MINUTE = 60;
        inline static time_t MILLSECOND = 1000;
        inline static time_t MILLMINUTE = 60000;
    };

    class StopwatchAvg
    {
    public:
        enum class Mode
        {
            Average,
            Latest
        };

        explicit StopwatchAvg(int samples = 30);
        void beginSample();
        void endSample();

        time_t elapsedMillSeconds(Mode mode) const;

    private:
        int mSamples = 30;
        int msTakenAvgSamples = 0;

        std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;

        time_t msTaken = 0;
        time_t msTakenAvg = 0;
        time_t msTakenAvgAccum = 0;
    };
}

#endif
