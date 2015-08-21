/******************************************************************************/
/*                                                                            */
/*  AudioContext.cpp                                                          */
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

#include <Fast/AudioContext.hpp>
#include <Fast/SoundBase.hpp>
#include <Fast/Exception.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	AudioContext::AudioContext() {
		AudioContext(0, 0, false);
	}
	
	AudioContext::AudioContext(Int frequency, Int refresh, Bool synchronous) {
		// Initialize
		mALCdevice = 0;
		mALCcontext = 0;
		mMasterVolume = 1.0f;
		// Setup OpenAL
		mALCdevice = (CALCdevice*)alcOpenDevice(0);
		if (!mALCdevice)
			Exception::Throw(kExceptionOpenALDeviceCreationFailure,
				String("(%s)", FastFunctionName));
		Int alcAttribs[] = {
			ALC_FREQUENCY,	frequency,
			ALC_REFRESH,	refresh,
			ALC_SYNC,		synchronous ? 1 : 0
		};
		mALCcontext = (CALCcontext*)alcCreateContext(
			(ALCdevice*)mALCdevice, alcAttribs);
		if (!mALCcontext) {
			alcCloseDevice((ALCdevice*)mALCdevice);
			Exception::Throw(kExceptionOpenALContextCreationFailure,
				String("(%s)", FastFunctionName));
		}
		if (!MakeCurrent()) {
			alcDestroyContext((ALCcontext*)mALCcontext);
			alcCloseDevice((ALCdevice*)mALCdevice);
			Exception::Throw(kExceptionOpenALContextCreationFailure,
				String("(%s)", FastFunctionName));
		}
		alcProcessContext((ALCcontext*)mALCcontext);
		// Get max sources
		UInt temp = 0;
		while (true) {
			alGenSources(1, &temp);
			if (AL_NO_ERROR == alGetError()) {
				SoundSourceEntry source;
				source.mID = temp;
				source.mSound = 0;
				mSources.Append(source);
			} else if (1 > mSources.GetElementCount()) {
				alcDestroyContext((ALCcontext*)mALCcontext);
				alcCloseDevice((ALCdevice*)mALCdevice);
				Exception::Throw(kExceptionOpenALGenSourcesFailure,
					String("(%s)", FastFunctionName));
			} else break;
			// Mac OS X gives us infinite sources?
			// Break loop at 255 sources. That should be enough.
			if (mSources.GetElementCount() >= 0xff)
				break;
		}
		// Apply everything
		Update(0);
	}
	
	AudioContext::~AudioContext() {
		for (Int i = 0; i < mSources.GetElementCount(); i++)
			alDeleteSources(1, &mSources[i].mID);
		alcDestroyContext((ALCcontext*)mALCcontext);
		alcCloseDevice((ALCdevice*)mALCdevice);
	}
	
	Bool AudioContext::MakeCurrent(Bool makeCurrent) {
		return alcMakeContextCurrent((ALCcontext*)mALCcontext) ? true : false;
	}
	
	UInt AudioContext::GetSourceID(SoundBase *sound) {
		for (Int i = 0; i < mSources.GetElementCount(); i++) {
			if (!mSources[i].mSound) {
				mSources[i].mSound = sound;
				return mSources[i].mID;
			}
		}
		return 0;
	}
	
	void AudioContext::FreeSourceID(SoundBase *sound) {
		for (Int i = 0; i < mSources.GetElementCount(); i++)
			if (mSources[i].mSound == sound)
				mSources[i].mSound = 0;
	}
	
	void AudioContext::Update(Int elapsedMilliseconds) {
		// Update OpenAL state
		alListenerf(AL_GAIN, mMasterVolume);
		alListener3f(AL_POSITION, mListener.GetPosition().mX,
			mListener.GetPosition().mY, mListener.GetPosition().mZ);
		ALfloat orientation[6] = {
			mListener.GetLookAt().mX, mListener.GetLookAt().mY,
			mListener.GetLookAt().mZ, mListener.GetUpVector().mX,
			mListener.GetUpVector().mY, mListener.GetUpVector().mZ
		};
		alListenerfv(AL_ORIENTATION, orientation);
		// Update sources
		for (Int i = 0; i < mSources.GetElementCount(); i++)
			if (mSources[i].mSound)
				mSources[i].mSound->Update(elapsedMilliseconds);
	}

	CALCdevice* AudioContext::GetALCdevice() {
		return mALCdevice;
	}

	CALCcontext* AudioContext::GetALCcontext() {
		return mALCcontext;
	}
	
	Float AudioContext::GetMasterVolume() const {
		return mMasterVolume;
	}

	const AudioListener& AudioContext::GetListener() const {
		return mListener;
	}

	AudioListener* AudioContext::GetListener() {
		return &mListener;
	}
	
	void AudioContext::SetMasterVolume(Float volume) {
		mMasterVolume = volume;
	}
}
