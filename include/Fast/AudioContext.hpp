/******************************************************************************/
/*                                                                            */
/*  AudioContext.hpp                                                          */
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

#ifndef FastAudioContextHppIncluded
#define FastAudioContextHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/SoundSourceEntry.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/String.hpp>
#include <Fast/AudioListener.hpp>

namespace Fast
{
	class SoundBase;

	template class FastApi Array<SoundSourceEntry>;

	class FastApi AudioContext
	{
	private:
		// Don't use these
		AudioContext(const AudioContext &that) {}
		AudioContext& operator=(const AudioContext &that)
			{ return *this; }
	protected:
		CALCdevice				*mALCdevice;
		CALCcontext				*mALCcontext;
		Float					mMasterVolume;
		AudioListener			mListener;
		Array<SoundSourceEntry>	mSources;
	public:
		// (Con/De)structors
		AudioContext();
		AudioContext(Int frequency, Int refresh, Bool synchronous);
		~AudioContext();
		// Misc functions
		Bool	MakeCurrent(Bool makeCurrent = true);
		UInt	GetSourceID(SoundBase *sound);
		void	FreeSourceID(SoundBase *sound);
		void	Update(Int elapsedMilliseconds);
		// Get functions
		CALCdevice*				GetALCdevice();
		CALCcontext*			GetALCcontext();
		Float					GetMasterVolume() const;
		AudioListener*			GetListener();
		const AudioListener&	GetListener() const;
		// Set functions
		void	SetMasterVolume(Float volume);
	};
}

#endif // FastAudioContextHppIncluded
