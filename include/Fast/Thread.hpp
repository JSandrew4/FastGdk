/******************************************************************************/
/*                                                                            */
/*  Thread.hpp                                                                */
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

#ifndef FastThreadHppIncluded
#define FastThreadHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/ThreadHandle.hpp>
#include <Fast/StopWatch.hpp>
#include <Fast/SystemConsole.hpp>
#include <Fast/Mutex.hpp>
#include <Fast/Conditional.hpp>
/*
#if defined(_DEBUG)
// We need a different timeout function for debugging
//	since we can't have our application timing out
//	constantly while we step through code.
// TODO: Implement logger here instead of SystemConsole
#	define FastThreadSync(conditional, target, timeoutMS) { \
		SystemConsole console; \
		StopWatch sw; \
		sw.Start(); \
		while (target != conditional) { \
			if (sw.GetElapsedMilliseconds() > timeoutMS) { \
				console.Print("Warning: Thread timed out.\n"); \
				while (target != conditional); \
			} \
		} \
	}
#else
#	define FastThreadSync(conditional, target, timeoutMS) { \
		StopWatch sw; \
		sw.Start(); \
		while (target != conditional) \
			if (sw.GetElapsedMilliseconds() > timeoutMS) \
				Exception::Throw(kExceptionThreadTimedOut); \
	}
#endif
*/
namespace Fast
{
#if defined(FastOSWindows)
	typedef unsigned int ThreadFunction;
#else
	typedef void ThreadFunction;
#endif

	struct ThreadData;

	class FastApi Thread
	{
	private:
		ThreadData	*mThreadData;
		Mutex		mCreationMutex;
		Conditional	mCreationConditional;
		Bool		mShouldEnd;
		Bool		mIsRunning;
		Int			mStackSize;
		static ThreadFunction	Start(void *args);
		// Hide these. No copying threads!
		Thread(const Thread &that) : mCreationMutex("CreationMutex") { }
		Thread& operator=(const Thread &that) { return *this; }
	protected:
		virtual void	Main()	= 0;
	public:
		// Static functions
		static void			Rest(Long microseconds);
		static ThreadHandle	GetCurrentThreadHandle();
		// (Con/De)structors
		Thread();
		~Thread();
		// Misc functions
		ErrorType	Run();
		void		AskToEnd();
		void		End();
		void		Murder();
		void		SetStackSize(Int stackSize);
		Bool		ShouldEnd();
		Bool		IsRunning();
		Int			GetStackSize() const;
	};
}

#endif // FastThreadHppIncluded
