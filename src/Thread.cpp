/******************************************************************************/
/*                                                                            */
/*  Thread.cpp                                                                */
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

#include <Fast/Thread.hpp>
#include <Fast/ExceptionType.hpp>
#include <Fast/Exception.hpp>
#include <Fast/StopWatch.hpp>
#include <Fast/Mutex.hpp>

#include <cstring>

#include "Multithreading.hpp"

#include "Undefs.hpp"

namespace Fast
{
	ThreadFunction Thread::Start(void *args) {
	#if defined(FastOSUnixLike)
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	#endif
		Thread *thread = (Thread*)args;
		thread->mCreationMutex.Lock(); 
		thread->mIsRunning = true;
		thread->mCreationConditional.Signal();
		thread->Main();
		thread->mShouldEnd = true;
		thread->mIsRunning = false;
		thread->mCreationMutex.Unlock();
	#if defined(FastOSWindows)
		_endthreadex(0);
		return 0;
	#elif defined(FastOSUnixLike)
		pthread_exit(0);
	#endif
	}

	void Thread::Rest(Long microseconds) {
	#if defined(FastOSWindows)
		Sleep((Int)(microseconds / 1000L));
	#elif defined(FastOSUnixLike)
		struct timeval tv;
		Long tstart;
		Long tcurrent;
		Long tend;
		gettimeofday(&tv, 0);
		tcurrent = tstart = ((Long)tv.tv_sec * 1000000L) + (Long)tv.tv_usec;
		tend = tstart + microseconds;
		while (tcurrent < tend) {
			sched_yield();
			gettimeofday(&tv, 0);
			tcurrent = ((Long)tv.tv_sec * 1000000L) + (Long)tv.tv_usec;
		}
	#endif
	}

	ThreadHandle Thread::GetCurrentThreadHandle() {
		ThreadHandle threadHandle;
	#if defined(FastOSWindows)
		threadHandle.mThreadData->mHandle = GetCurrentThread();
	#elif defined(FastOSUnixLike)
		threadHandle.mThreadData->mPThread = pthread_self();
	#endif
		return threadHandle;
	}

	Thread::Thread() : mCreationMutex("CreationMutex"),
		mCreationConditional("CreationConditional")
	{
		mThreadData = new ThreadData;
		memset(mThreadData, 0, sizeof(ThreadData));
		mIsRunning = false;
		mShouldEnd = true;
		mStackSize = 0;
	}

	Thread::~Thread() {
		End();
		delete mThreadData;
	}

	ErrorType Thread::Run() {
		End();
		mShouldEnd = false;
		mIsRunning = false;
		mCreationMutex.Lock();
	#if defined(FastOSWindows)
		uintptr_t ret = _beginthreadex(0, mStackSize,
			(unsigned int (__stdcall*)(void*))&Start, (void*)this, 0, 0);
		if (ret == -1L) {
			switch (errno)
			{
			case EAGAIN:
				Exception::Throw(kExceptionThreadTooManyThreads,
					String("(%s)", FastFunctionName));
			case EINVAL:
				Exception::Throw(kExceptionThreadInvalidArgument,
					String("(%s)", FastFunctionName));
			case EACCES:
				Exception::Throw(kExceptionThreadOutOfResources,
					String("(%s)", FastFunctionName));
			case EPERM:
				Exception::Throw(kExceptionThreadPermissionDenied,
					String("(%s)", FastFunctionName));
			}
		} else {
			mThreadData->mHandle = (HANDLE)ret;
		}
	#elif defined(FastOSUnixLike)
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setstacksize(&attr, stackSize);
		int error = pthread_create(&mThreadData->mPThread, 0,
			(void*(*)(void*))&ThreadStart, (void*)ta);
		switch (error)
		{
		case EAGAIN:
			Exception::Throw(kExceptionThreadTooManyThreads,
				String("(%s)", FastFunctionName));
		case EINVAL:
			Exception::Throw(kExceptionThreadInvalidArgument,
				String("(%s)", FastFunctionName));
		case EPERM:
			Exception::Throw(kExceptionThreadPermissionDenied,
				String("(%s)", FastFunctionName));
		}
	#endif
		mCreationMutex.Unlock();
		mCreationConditional.Wait(&mCreationMutex);
		return kErrorNone; // TODO
	}
	
	void Thread::AskToEnd() {
		mShouldEnd = true;
	}

	void Thread::End() {
		if (IsRunning()) {
			AskToEnd();
		#if defined(FastOSWindows)
			if (mThreadData->mHandle) {
				WaitForSingleObject(mThreadData->mHandle, INFINITE);
				CloseHandle(mThreadData->mHandle);
				mThreadData->mHandle = NULL;
			}
		#elif defined(FastOSUnixLike)
			if (mThreadData->mPThread) {
				pthread_join(mThreadData->mPThread, 0);
				mThreadData->mPThread = 0;
			}
		#endif
		}
	}

	void Thread::Murder() {
		if (IsRunning()) {
		#if defined(FastOSWindows)
			CloseHandle(mThreadData->mHandle);
			mThreadData->mHandle = NULL;
		#elif defined(FastOSUnixLike)
			pthread_cancel(mThreadData->mPThread);
			mThreadData->mPThread = 0;
		#endif
		}
	}

	void Thread::SetStackSize(Int stackSize) {
		if (!IsRunning())
			mStackSize = stackSize;
	}

	Bool Thread::ShouldEnd() {
		return mShouldEnd;
	}

	Bool Thread::IsRunning() {
		return mIsRunning;
	}

	Int Thread::GetStackSize() const {
		return mStackSize;
	}
}
