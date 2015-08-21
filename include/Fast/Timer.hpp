/******************************************************************************/
/*                                                                            */
/*  Timer.hpp                                                                 */
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

#ifndef FastTimerHppIncluded
#define FastTimerHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class FastApi Timer
	{
	private:
		// Members
		Long	mTicks;
		Long	mTime;
		Long	mOldTime;
		Long	mPerformanceCounterFrequency;
		Bool	mHasPerformanceCounter;
		Long	mElapsedMicroseconds;
		Long	mTargetFps;
		Long	mTimeout;
		Long	mUptimeBase;
	public:
		// (Con/De)structors
		Timer();
		~Timer();
		// Control functions
		void	Start();
		void	Update();
		// Get/Set functions
		Long	GetMicrosecondsSinceUpdate() const;
		Float	GetMillisecondsSinceUpdate() const;
		Float	GetSecondsSinceUpdate() const;
		Long	GetUpTimeInMicroseconds() const;
		Float	GetUpTimeInMilliseconds() const;
		Float	GetUpTimeInSeconds() const;
		void	SetTargetFps(Long fps);
		Long	GetTargetFps() const;
		Long	GetElapsedMicroseconds() const;
		Float	GetElapsedMilliseconds() const;
		Float	GetElapsedSeconds() const;
		Long	GetTickCount() const;
	};
}

#endif // FastTimerHppIncluded
