/******************************************************************************/
/*                                                                            */
/*  Timer.cpp                                                                 */
/*                                                                            */
/*  Copyright (C) 2015, Joseph Andrew Staedelin IV                            */
/*                                                                            */
/*  This file is part of the FastGdk project.                                 */
/*                                                                            */
/*  The FastGdk is free software: you can redistribute it and/or modify       */
/*  it under the terms of the GNU Lesser General Public License as published  */
/*  by the Free Software Foundation, either version 3 of the License, or      */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  The FastGdk is distributed in the hope that it will be useful,            */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU Lesser General Public License for more details.                       */
/*                                                                            */
/*  You should have received a copy of the GNU Lesser General Public License  */
/*  along with the FastGdk.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                            */
/******************************************************************************/

#include <Fast/Timer.hpp>
#include <Fast/Math.hpp>

#if defined(FastOSWindows)
#	include <MMSystem.h>
#elif defined(FastOSUnixLike)
#	include <sys/time.h>
#endif

#include "Undefs.hpp"

namespace Fast
{
	Timer::Timer() {
		mTicks = 0;
		mTime = 0;
		mOldTime = 0;
		mPerformanceCounterFrequency = 0;
		mHasPerformanceCounter = false;
		mElapsedMicroseconds = 0;
		mTargetFps = 0;
		mTimeout = 500000;
		mUptimeBase = 0;
	#if defined(FastOSWindows)
		LARGE_INTEGER temp;
		if (QueryPerformanceFrequency(&temp)) {
			mHasPerformanceCounter = true;
			mPerformanceCounterFrequency = temp.QuadPart;
		} else {
			timeBeginPeriod(1);
		}
		mUptimeBase = timeGetTime() * 1000;
	#elif defined(FastOSUnixLike)
		struct timeval temp;
		gettimeofday(&temp, 0);
		mUptimeBase = (temp.tv_sec * 1000000) + temp.tv_usec;
	#endif
	}

	Timer::~Timer() {
	#if defined(FastOSWindows)
		if (!mHasPerformanceCounter) timeEndPeriod(1);
	#endif
	}

	void Timer::Start() {
	#if defined(FastOSWindows)
		if (mHasPerformanceCounter) {
			LARGE_INTEGER temp;
			QueryPerformanceCounter(&temp);
			mTime = mOldTime = temp.QuadPart * 1000000;
		} else {
			mTime = mOldTime = timeGetTime() * 1000;
		}
	#elif defined(FastOSUnixLike)
		struct timeval temp;
		gettimeofday(&temp, 0);
		mTime = mOldTime = mUptimeBase = (temp.tv_sec * 1000000) + temp.tv_usec;
	#endif
	}

	Long Timer::GetMicrosecondsSinceUpdate() const {
	#if defined(FastOSWindows)
		if (mHasPerformanceCounter) {
			LARGE_INTEGER temp;
			QueryPerformanceCounter(&temp);
			return (((temp.QuadPart * 1000000) - mOldTime) /
				mPerformanceCounterFrequency);
		} else return ((timeGetTime() * 1000) - mOldTime);
	#elif defined(FastOSUnixLike)
		struct timeval temp;
		gettimeofday(&temp, 0);
		return (((temp.tv_sec * 1000000) + temp.tv_usec) - mOldTime);
	#endif
	}

	Float Timer::GetMillisecondsSinceUpdate() const {
		return (Float)GetMicrosecondsSinceUpdate() / 1000.0f;
	}

	Float Timer::GetSecondsSinceUpdate() const {
		return (Float)GetMicrosecondsSinceUpdate() / 1000000.0f;
	}

	void Timer::Update() {
		Long elapsed = 0;
		Long targetElapsedMicroseconds = 0;
		if (mTargetFps > 0) targetElapsedMicroseconds = 1000000 / mTargetFps;
	#if defined(FastOSWindows)
		if (mHasPerformanceCounter) {
			LARGE_INTEGER temp;
			do {
				QueryPerformanceCounter(&temp);
				mTime = temp.QuadPart * 1000000;
				elapsed = (mTime - mOldTime) / mPerformanceCounterFrequency;
			} while (elapsed < targetElapsedMicroseconds);
		} else {
			do {
				mTime = timeGetTime() * 1000;
				elapsed = (mTime - mOldTime);
			} while (elapsed < targetElapsedMicroseconds);
		}
	#elif defined(FastOSUnixLike)
		struct timeval temp;
		do {
			gettimeofday(&temp, 0);
			mTime = (Double)((temp.tv_sec * 1000000) + temp.tv_usec);
			elapsed = mTime - mOldTime;
		} while (elapsed < targetElapsedMicroseconds);
	#endif
		if (elapsed < mTimeout && elapsed > 0) mElapsedMicroseconds = elapsed;
		else mElapsedMicroseconds = 0;
		mOldTime = mTime;
		mTicks++;
	}

	Long Timer::GetUpTimeInMicroseconds() const {
	#if defined(FastOSWindows)
		return (timeGetTime() - mUptimeBase);
	#elif defined(FastOSUnixLike)
		struct timeval temp;
		gettimeofday(&temp, 0);
		return (((temp.tv_sec * 1000000) + temp.tv_usec) - mUptimeBase);
	#endif
	}

	Float Timer::GetUpTimeInMilliseconds() const {
		return (Float)GetUpTimeInMicroseconds() / 1000.0f;
	}

	Float Timer::GetUpTimeInSeconds() const {
		return (Float)GetUpTimeInMicroseconds() / 1000000.0f;
	}

	void Timer::SetTargetFps(Long fps) {
		mTargetFps = fps;
	}

	Long Timer::GetTargetFps() const {
		return mTargetFps;
	}

	Long Timer::GetElapsedMicroseconds() const {
		return mElapsedMicroseconds;
	}

	Float Timer::GetElapsedMilliseconds() const {
		return (Float)mElapsedMicroseconds / 1000.0f;
	}

	Float Timer::GetElapsedSeconds() const {
		return (Float)mElapsedMicroseconds / 1000000.0f;
	}

	Long Timer::GetTickCount() const {
		return mTicks;
	}
}
