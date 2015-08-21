/******************************************************************************/
/*                                                                            */
/*  ThreadHandle.cpp                                                          */
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

#include <Fast/ThreadHandle.hpp>

#include <cstring>

#include "Multithreading.hpp"

#include "Undefs.hpp"

namespace Fast
{
	ThreadHandle::ThreadHandle() {
		mThreadData = new ThreadData;
	}

	ThreadHandle::ThreadHandle(const ThreadHandle &that) {
		mThreadData = new ThreadData;
		*this = that;
	}

	ThreadHandle::~ThreadHandle() {
		delete mThreadData;
	}

	ThreadHandle& ThreadHandle::operator=(const ThreadHandle &that) {
		memcpy(this->mThreadData, that.mThreadData, sizeof(ThreadData));
		return *this;
	}

	Bool ThreadHandle::operator==(const ThreadHandle &that) const {
	#if defined(FastOSWindows)
		return (this->mThreadData->mHandle == that.mThreadData->mHandle);
	#elif defined(FastOSUnixLike)
		return pthread_equal(this->mThreadData->mPThread,
			that.mThreadData->mPThread) ? true : false;
	#endif
		return false;
	}
}