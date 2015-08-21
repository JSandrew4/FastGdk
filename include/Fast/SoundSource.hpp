/******************************************************************************/
/*                                                                            */
/*  SoundSource.hpp                                                           */
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

#ifndef FastSoundSourceHppIncluded
#define FastSoundSourceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/SoundBase.hpp>
#include <Fast/SoundSeekable.hpp>
#include <Fast/SoundCache.hpp>
#include <Fast/SoundCollection.hpp>
#include <Fast/SoundResource.hpp>

namespace Fast
{
	class String;
	class SoundData;
	class StreamReader;
	
	class FastApi SoundSource : public SoundBase,
		public SoundSeekable,
		public AssetImplementer<SoundCollection, SoundResource>
	{
	protected:
		void		SetupSource(Int fadeInTime);
		ErrorType	LoadResource(const String &name, const SoundData &soundData,
						SoundCollection *collection);
	public:
		// (Con/De)structors
		SoundSource();
		SoundSource(const SoundSource &that);
		SoundSource(const String &fileName, SoundCollection *collection);
		SoundSource(StreamReader *streamReader, SoundCollection *collection);
		SoundSource(const SoundData &soundData, SoundCollection *collection);
		~SoundSource();
		// Load functions
		ErrorType	Load(const String &fileName, SoundCollection *collection);
		ErrorType	Load(StreamReader *streamReader,
						SoundCollection *collection);
		ErrorType	Load(const SoundData &soundData,
						SoundCollection *collection);
		void		Unbind();
		// Control functions
		void	Play(Int fadeInTime = 0);
		void	Pause(Int fadeOutTime = 0);
		void	Stop(Int fadeOutTime = 0);
		void	Update(Int elapsedMilliseconds);
		// Seekable functions
		Int		GetDuration() const;
		Bool	IsLooping() const;
		void	SetLooping(Bool setLooping);
		Int		GetSeekTime();
		void	SeekTo(Int millisecond);
		// Operators
		SoundSource&	operator= (const SoundSource &that);
		Bool			operator==(const SoundSource &that) const;
		Bool			operator!=(const SoundSource &that) const;
	};
}

#endif // FastSoundSourceHppIncluded
