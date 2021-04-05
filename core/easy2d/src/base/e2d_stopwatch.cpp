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
		mStartTime = high_resolution_clock::now();
	}
}

void Stopwatch::pause()
{
	if (mbRunning)
	{
		mbRunning = false;
		mElapsedTime += high_resolution_clock::now() - mStartTime;
	}
}

void Stopwatch::reset()
{
	mElapsedTime = 0;
}

time_t Stopwatch::elapsedSeconds() const
{
	return duration_cast<seconds>(mElapsedTime).count();
}

time_t Stopwatch::elapsedMillSeconds() const
{
	return duration_cast<milliseconds>(mElapsedTime).count();
}

time_t Stopwatch::elapsedSecondsNow() const
{
	auto now = high_resolution_clock::now()
	mElapsedTime = now - mStartTime;
	mStartTime = now
	return duration_cast<seconds>(mElapsedTime).count();
}

time_t Stopwatch::elapsedMillSecondsNow() const
{
	auto now = high_resolution_clock::now()
	mElapsedTime = now - mStartTime;
	mStartTime = now
	return duration_cast<milliseconds>(mElapsedTime).count();
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
