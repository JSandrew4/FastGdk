/******************************************************************************/
/*                                                                            */
/*  SoundFileStream.hpp                                                       */
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

#ifndef FastSoundFileStreamHppIncluded
#define FastSoundFileStreamHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/SoundStreamBase.hpp>
#include <Fast/SoundStreamData.hpp>
#include <Fast/SoundSeekable.hpp>

namespace Fast
{
	class SoundManager;
	class String;
	class AudioContext;
	class StreamReader;

	class FastApi SoundFileStream :
		public SoundStreamBase, public SoundSeekable
	{
	private:
		void	QueueBuffers();
		SoundStreamData	mStreamData;
		// Hide these functions. No copying file streams!
		SoundFileStream(const SoundFileStream &that);
		SoundFileStream& operator=(const SoundFileStream &that)
			{ return *this; }
	public:
		// (Con/De)structors
		SoundFileStream(AudioContext *context);
		SoundFileStream(const String &fileName,
			AudioContext *context, Int numBuffers = 4);
		SoundFileStream(StreamReader *streamReader,
			AudioContext *context, Int numBuffers = 4);
		~SoundFileStream();
		// Misc functions
		ErrorType	Open(const String &fileName ,Int numBuffers = 4);
		ErrorType	Open(StreamReader *streamReader, Int numBuffers = 4);
		void	Close();
		// Control functions
		void	Play(Int fadeInTime = 0);
		void	Pause(Int fadeOutTime = 0);
		void	Stop(Int fadeOutTime = 0);
		void	Update(Int elapsedMilliseconds);
		// Seekable functions
		Int		GetNumTotalSamples() const;
		Int		GetDuration() const;
		Bool	IsLooping() const;
		void	SetLooping(Bool setLooping);
		Int		GetSeekTime();
		void	SeekTo(Int millisecond);
	};
}

#endif // FastSoundFileStreamHppIncluded
