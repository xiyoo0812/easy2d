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
		void pause();
		void reset();

		time_t elapsedSeconds() const;
		time_t elapsedMillSeconds() const;
		time_t elapsedSecondsNow() const;
		time_t elapsedMillSecondsNow() const;

	private:
		bool mbRunning = false;
		time_t mElapsedTime = 0;
		std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
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
