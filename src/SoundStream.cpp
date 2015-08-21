/******************************************************************************/
/*                                                                            */
/*  SoundStream.cpp                                                           */
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

#include <Fast/SoundStream.hpp>
#include <Fast/SoundStreamData.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/Error.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	SoundStream::SoundStream(AudioContext *context) {
		mContext = context;
		Close();
	}

	SoundStream::~SoundStream() {
		Close();
	}

	ErrorType SoundStream::Open(Int numBuffers) {
		Close();
		ErrorType error = GenerateBuffers(numBuffers);
		if (error) {
			Close();
			return Error::Throw(error, String("[%s(%d)]",
				FastFunctionName, numBuffers));
		}
		return kErrorNone;
	}

	void SoundStream::Close() {
		// Clean up everything
		Stop();
		if (mBuffers.GetElementCount() > 0)
			DeleteBuffers();
		// Set SoundBase variables to defaults
		mContext =				NULL;
		mOpenALSourceID =		0;
		mImportance =			0;
		mVolume =				1.0f;
		mPitch =				1.0f;
		mPosition =				kFastVector3DZero;
		mIsRelativePosition =	false;
		mIsPlaying =			false;
		mIsPaused =				false;
		mIsStopped =			true;
		mIsFadingIn =			false;
		mIsFadingOut =			false;
		mFadeTime =				0;
	}

	Int SoundStream::GetNumAvailableBuffers() {
		if (!mOpenALSourceID)
			return 0;
		Int numAvailableBuffers = 0;
		RetrieveProcessedBuffers();
		for (Int i = 0; i < mBuffers.GetElementCount(); i++)
			if (!mBuffers[i].mIsActive)
				numAvailableBuffers++;
		return numAvailableBuffers;
	}

	ErrorType SoundStream::BufferData(const SoundDataBase &data) {
		if (mOpenALSourceID) {
			ErrorType error = kErrorNone;
			RetrieveProcessedBuffers();
			for (Int i = 0; i < mBuffers.GetElementCount(); i++) {
				if (!mBuffers[i].mIsActive) {
					alBufferData(mBuffers[i].mOpenALBufferID,
						data.GetProperties().GetFormat(),
						data.GetSamples().GetData(),
						data.GetSamples().GetElementCount(),
						data.GetProperties().GetFrequency());
					alSourceQueueBuffers(mOpenALSourceID, 1,
						&mBuffers[i].mOpenALBufferID);
					mBuffers[i].mIsActive = true;
					error = kErrorNone;
					break;
				}
				error = kErrorOpenALNoBuffersAvailable;
			}
			// Play our newly buffered data if needed
			ALint state;
			alGetSourcei(mOpenALSourceID, AL_SOURCE_STATE, &state);
			if (state != AL_PLAYING)
				alSourcePlay(mOpenALSourceID);
			return error ? Error::Throw(error, String("[%s(%p)]",
				FastFunctionName, &data)) : kErrorNone;
		} else
			return Error::Throw(kErrorOpenALNoActiveSource,
				String("[%s(%p)]", FastFunctionName, &data));
	}

	void SoundStream::Play(Int fadeInTime) {
		SetupSource(fadeInTime);
		if (mOpenALSourceID) {
			RequeueSavedBuffers();
			alSourcePlay(mOpenALSourceID);
			mIsStopped = false;
			mIsPaused = false;
			mIsPlaying = true;
		}
	}

	void SoundStream::Pause(Int fadeOutTime) {
		if (mOpenALSourceID) {
			mFadeTime = fadeOutTime;
			if (mFadeTime < 1) {
				alSourceStop(mOpenALSourceID);
				RetrieveProcessedBuffers();
				SaveQueuedBufferStates();
				mContext->FreeSourceID(this);
				mOpenALSourceID = 0;
				mIsFadingOut = false;
			} else
				mIsFadingOut = true;
			mIsStopped = false;
			mIsPaused = true;
			mIsStopped = false;
		}
	}

	void SoundStream::Stop(Int fadeOutTime) {
		if (mOpenALSourceID) {
			mFadeTime = fadeOutTime;
			if (mFadeTime < 1) {
				alSourceStop(mOpenALSourceID);
				RetrieveProcessedBuffers();
				mContext->FreeSourceID(this);
				mOpenALSourceID = 0;
				mIsFadingOut = false;
			} else
				mIsFadingOut = true;
		}
		mIsStopped = false;
		mIsPaused = false;
		mIsStopped = true;
	}

	void SoundStream::Update(Int elapsedMilliseconds) {
		if (mOpenALSourceID) {
			ALint alState;
			alGetSourcei(mOpenALSourceID, AL_SOURCE_STATE, &alState);
			if (alState != AL_PLAYING)
				alSourcePlay(mOpenALSourceID);
			HandleFading(elapsedMilliseconds);
		}
	}
}
