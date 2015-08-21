/******************************************************************************/
/*                                                                            */
/*  SoundDeviceStream.hpp                                                     */
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

#ifndef FastSoundDeviceStreamHppIncluded
#define FastSoundDeviceStreamHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/SoundStreamBase.hpp>

namespace Fast
{
	class SoundCapture;
	class SoundManager;

	class FastApi SoundDeviceStream : public SoundStreamBase
	{
	private:
		AudioContext	*mContext;
		SoundCapture	*mCapture;
		// Hide these functions. No copying device sound streams!
		SoundDeviceStream(const SoundDeviceStream &that) {}
		SoundDeviceStream& operator=(const SoundDeviceStream &that)
			{ return *this; }
	public:
		// (Con/De)structors
		SoundDeviceStream(AudioContext *context);
		~SoundDeviceStream();
		// Load functions
		ErrorType	Open(SoundCapture *capture, Int numBuffers = 4);
		void		Close();
		// Control functions
		void	Play(Int fadeInTime = 0);
		void	Pause(Int fadeOutTime = 0);
		void	Stop(Int fadeOutTime = 0);
		void	Update(Int elapsedMilliseconds);
	};
}

#endif // FastSoundDeviceStreamHppIncluded
