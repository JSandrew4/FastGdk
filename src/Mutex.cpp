/******************************************************************************/
/*                                                                            */
/*  Mutex.cpp                                                                 */
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

#include <Fast/Mutex.hpp>

#include <stdio.h>

#include "Multithreading.hpp"

#include "Undefs.hpp"

namespace Fast
{
	Mutex::Mutex(const String &name) {
		mName = name;
		mLockCount = 0;
		mCriticalSection = new CriticalSection;
	#if defined(FastOSWindows)
		InitializeCriticalSection(&mCriticalSection->cs);
	#elif defined(FastOSUnixLike)
		pthread_mutexattr_t mattr;
		pthread_mutexattr_init(&mattr);
		pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init(&mCriticalSection->cs, &mattr);
	#endif
		// TODO: Check success, throw Exception if not
	}

	Mutex::~Mutex() {
	#if defined(FastOSWindows)
		DeleteCriticalSection(&mCriticalSection->cs);
	#elif defined(FastOSUnixLike)
		pthread_mutex_destroy(&mCriticalSection->cs);
	#endif
		delete mCriticalSection;
		mCriticalSection = NULL;
	}

	void Mutex::Lock() {
	#if defined(FastOSWindows)
		EnterCriticalSection(&mCriticalSection->cs);
	#elif defined(FastOSUnixLike)
		pthread_mutex_lock(&mCriticalSection->cs);
	#endif
		//printf("Lock(%s, %p, %d, %d);\n", mName.GetCString(),
		//	(void*)&mCriticalSection->cs, (void*)mCriticalSection->cs.OwningThread,
		//	mLockCount);
		++mLockCount;
	}

	Bool Mutex::TryLock() {
	#if defined(FastOSWindows)
		return TryEnterCriticalSection(&mCriticalSection->cs) ? true : false;
	#elif defined(FastOSUnixLike)
		return pthread_mutex_trylock(&mCriticalSection->cs) ? false : true;
	#endif
	}

	void Mutex::Unlock() {
		//printf("Unlock(%s, %p, %d, %d);\n", mName.GetCString(),
		//	(void*)&mCriticalSection->cs, (void*)mCriticalSection->cs.OwningThread,
		//	mLockCount);
		--mLockCount;
	#if defined(FastOSWindows)
		LeaveCriticalSection(&mCriticalSection->cs);
	#elif defined(FastOSUnixLike)
		pthread_mutex_unlock(&mCriticalSection->cs);
	#endif
	}

	const String& Mutex::GetName() const {
		return mName;
	}

	Int Mutex::GetLockCount() const {
		return mLockCount;
	}

	CriticalSection* Mutex::GetCriticalSection() {
		return mCriticalSection;
	}

	void Mutex::SetName(const String &name) {
		mName = name;
	}
}
