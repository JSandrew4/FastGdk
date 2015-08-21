/******************************************************************************/
/*                                                                            */
/*  Conditional.cpp                                                           */
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

#include <Fast/Conditional.hpp>
#include <Fast/Mutex.hpp>

#include <stdio.h>

#include "Multithreading.hpp"

#include "Undefs.hpp"

namespace Fast
{
	Conditional::Conditional(const String &name) {
		mName = name;
		mConditionVariable = new ConditionVariable;
	#if defined(FastOSWindows)
		InitializeConditionVariable(&mConditionVariable->cv);
	#elif defined(FastOSUnixLike)
		pthread_cond_init(&mConditionVariable->cv, NULL);
	#endif
	}

	Conditional::~Conditional() {
	#if defined(FastOSWindows)
		// Do nothing I guess
	#elif defined(FastOSUnixLike)
		pthread_cond_destroy(&mConditionVariable->cv);
	#endif
		delete mConditionVariable;
	}

	const String& Conditional::GetName() const {
		return mName;
	}

	void Conditional::SetName(const String &name) {
		mName = name;
	}

	void Conditional::Wait(Mutex *mutex, Int microseconds) {
		//printf("Wait(%s) start\n", mName.GetCString());
	#if defined(FastOSWindows)
		if (0 > microseconds)
			SleepConditionVariableCS(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs, INFINITE);
		else
			SleepConditionVariableCS(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs, microseconds / 1000);
	#elif defined(FastOSUnixLike)
		if (0 > microseconds)
			pthread_cond_wait(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs);
		else {
			struct timespec timeToWait;
			struct timeval now;
			gettimeofday(&now, NULL);
			timeToWait.tv_sec = now.tv_sec + (microseconds / 1000000);
			timeToWait.tv_nsec = 1000 * (now.tv_usec + (microseconds -
				((microseconds / 1000000) * 1000000)));
			pthread_cond_timedwait(&mConditionVariable->cv,
				&mutex->GetCriticalSection()->cs, &timeToWait);
		}
	#endif
		//printf("Wait(%s) end\n", mName.GetCString());
	}

	void Conditional::Signal() {
		//printf("Signal(%s) start\n", mName.GetCString());
	#if defined(FastOSWindows)
		WakeConditionVariable(&mConditionVariable->cv);
	#elif defined(FastOSUnixLike)
		pthread_cond_signal(&mConditionVariable->cv);
	#endif
		//printf("Signal(%s) end\n", mName.GetCString());
	}

	void Conditional::Broadcast() {
	#if defined(FastOSWindows)
		WakeAllConditionVariable(&mConditionVariable->cv);
	#elif defined(FastOSUnixLike)
		pthread_cond_broadcast(&mConditionVariable->cv);
	#endif
	}
}
