/******************************************************************************/
/*                                                                            */
/*  SoundSeekable.hpp                                                         */
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

#ifndef FastSoundSeekableHppIncluded
#define FastSoundSeekableHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class FastApi SoundSeekable
	{
	protected:
		Int		mSampleOffset;
		Bool	mIsLooping;
		// Protected functions
		void	ResetBaseSeekableProperties();
	public:
		virtual Int		GetDuration() const			= 0;
		virtual Bool	IsLooping() const			= 0;
		virtual void	SetLooping(Bool setLooping)	= 0;
		virtual Int		GetSeekTime()				= 0;
		virtual void	SeekTo(Int millisecond)		= 0;
	};
}

#endif // FastSoundSeekableHppIncluded
