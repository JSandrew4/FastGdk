/******************************************************************************/
/*                                                                            */
/*  StopWatch.hpp                                                             */
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

#ifndef FastStopWatchHppIncluded
#define FastStopWatchHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class FastApi StopWatch
	{
	private:
		Long	mTotalTime;
		Long	mTime;
		Long	mOldTime;
		Bool	mIsCounting;
		void	GetTotalTime();
	public:
		// (Con/De)structors
		StopWatch();
		StopWatch(const StopWatch &that);
		~StopWatch();
		// Control functions
		void	Start();
		void	Pause(); // Stops timer but retains totalTime value
		void	Reset(); // Stops timer and resets totalTime
		// Get functions
		Double	GetElapsedMinutes();
		Double	GetElapsedSeconds();
		Long	GetElapsedMilliseconds();
		Long	GetElapsedMicroseconds();
		Bool	IsCounting() const;
		// Operators
		StopWatch&	operator= (const StopWatch &that);
		Bool		operator==(const StopWatch &that) const;
		Bool		operator!=(const StopWatch &that) const;
	};
}

#endif // FastStopWatchHppIncluded
