/******************************************************************************/
/*                                                                            */
/*  SoundStreamBase.hpp                                                       */
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

#ifndef FastSoundStreamBaseHppIncluded
#define FastSoundStreamBaseHppIncluded

#include <Fast/Types.hpp>
#include <Fast/SoundBase.hpp>
#include <Fast/Array.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/SoundStreamBuffer.hpp>

namespace Fast
{
	class AudioContext;

	template class FastApi Array<SoundStreamBuffer>;

	class FastApi SoundStreamBase : public SoundBase
	{
	protected:
		AudioContext				*mContext;
		Array<SoundStreamBuffer>	mBuffers;
		// Private functions
		void		RetrieveProcessedBuffers();
		void		RetrieveQueuedBuffers();
		void		SaveQueuedBufferStates();
		void		RequeueSavedBuffers();
		ErrorType	GenerateBuffers(Int numBuffers);
		void		DeleteBuffers();
		void		SetupSource(Int fadeInTime);
	public:
		// Load functions
		virtual void	Close()	= 0;
		// Control functions
		virtual void	Play(Int fadeInTime = 0)		= 0;
		virtual void	Pause(Int fadeOutTime = 0)		= 0;
		virtual void	Stop(Int fadeOutTime = 0)		= 0;
		virtual void	Update(Int elapsedMilliseconds)	= 0;
		// Get functions
		AudioContext*		GetAudioContext();
		const AudioContext&	GetAudioContext() const;
	};
}

#endif // FastSoundStreamBaseHppIncluded
