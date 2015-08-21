/******************************************************************************/
/*                                                                            */
/*  SoundStream.hpp                                                           */
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

#ifndef FastSoundStreamHppIncluded
#define FastSoundStreamHppIncluded

#include <Fast/Types.hpp>
#include <Fast/SoundStreamBase.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class SoundStreamData;

	class FastApi SoundStream : public SoundStreamBase
	{
	public:
		// (Con/De)structors
		SoundStream(AudioContext *context);
		SoundStream(const SoundStream &that);
		~SoundStream();
		// Misc functions
		ErrorType	Open(Int numBuffers = 4);
		void		Update();
		void		Close();
		Int			GetNumAvailableBuffers();
		ErrorType	BufferData(const SoundDataBase &data);
		// Control functions
		void	Play(Int fadeInTime = 0);
		void	Pause(Int fadeOutTime = 0);
		void	Stop(Int fadeOutTime = 0);
		void	Update(Int elapsedMilliseconds);
		// Assignment operator
		SoundStream&	operator=(const SoundStream &that);
		// Compare operator
		Bool	operator==(const SoundStream &that) const;
		Bool	operator!=(const SoundStream &that) const;
	};
}

#endif // FastSoundStreamHppIncluded
