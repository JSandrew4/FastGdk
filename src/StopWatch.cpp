/******************************************************************************/
/*                                                                            */
/*  StopWatch.cpp                                                             */
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

#include <Fast/StopWatch.hpp>
#if defined(FastOSWindows)
#	include <MMSystem.h>
#elif defined(FastOSUnixLike)
#	include <sys/time.h>
#endif

#include "Undefs.hpp"

namespace Fast
{
	StopWatch::StopWatch() {
		Reset();
	}

	StopWatch::StopWatch(const StopWatch &that) {
		this->Reset();
		*this = that;
	}

	StopWatch::~StopWatch() {
		Reset();
	}

	void StopWatch::Start() {
	#if defined(FastOSWindows)
		mTime = timeGetTime() * 1000;
	#elif defined(FastOSUnixLike)
		struct timeval tv;
		gettimeofday(&tv, 0);
		mTime = (tv.tv_sec * 1000000) + tv.tv_usec;
	#endif
		mOldTime = mTime;
		mIsCounting = true;
	}

	void StopWatch::Pause() {
		GetTotalTime();
		mTime = 0;
		mOldTime = 0;
		mIsCounting = false;
	}

	void StopWatch::Reset() {
		mTotalTime = 0;
		mTime = 0;
		mOldTime = 0;
		mIsCounting = false;
	}

	Double StopWatch::GetElapsedMinutes() {
		GetTotalTime();
		return (Double)mTotalTime / 60000000.0;
	}

	Double StopWatch::GetElapsedSeconds() {
		GetTotalTime();
		return (Double)mTotalTime / 1000000.0;
	}
	
	Long StopWatch::GetElapsedMilliseconds() {
		GetTotalTime();
		return mTotalTime / 1000;
	}

	Long StopWatch::GetElapsedMicroseconds() {
		GetTotalTime();
		return mTotalTime;
	}

	void StopWatch::GetTotalTime() {
		if (mIsCounting) {
			Long timeget;
		#if defined(FastOSWindows)
			timeget = timeGetTime() * 1000;
		#elif defined(FastOSUnixLike)
			struct timeval tv;
			gettimeofday(&tv, 0);
			timeget = (tv.tv_sec * 1000000) + tv.tv_usec;
		#endif
			if (timeget < 0 || timeget < mOldTime)
				return;
			else
				mTime = timeget;
			mTotalTime += mTime - mOldTime;
			mOldTime = mTime;
		}
	}

	Bool StopWatch::IsCounting() const {
		return mIsCounting;
	}

	StopWatch& StopWatch::operator=(const StopWatch &that) {
		this->mIsCounting = that.mIsCounting;
		this->mOldTime = that.mOldTime;
		this->mTime = that.mTime;
		this->mTotalTime = that.mTotalTime;
		return *this;
	}

	Bool StopWatch::operator==(const StopWatch &that) const {
		return (this->mIsCounting == that.mIsCounting &&
			this->mOldTime == that.mOldTime &&
			this->mTime == that.mTime &&
			this->mTotalTime == that.mTotalTime);
	}

	Bool StopWatch::operator!=(const StopWatch &that) const {
		return (this->mIsCounting != that.mIsCounting ||
			this->mOldTime != that.mOldTime ||
			this->mTime != that.mTime ||
			this->mTotalTime != that.mTotalTime);
	}
}
