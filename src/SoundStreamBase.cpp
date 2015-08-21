/******************************************************************************/
/*                                                                            */
/*  SoundStreamBase.cpp                                                       */
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

#include <Fast/SoundStreamBase.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/Error.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	void SoundStreamBase::RetrieveProcessedBuffers() {
		ALuint buffer = 0;
		ALint processedBuffers = 0;
		alGetSourcei(mOpenALSourceID, AL_BUFFERS_PROCESSED, &processedBuffers);
		for (ALint i = 0; i < processedBuffers; i++) {
			alSourceUnqueueBuffers(mOpenALSourceID, 1, &buffer);
			for (Int j = 0; j < mBuffers.GetElementCount(); j++)
				if (buffer == mBuffers[j].mOpenALBufferID)
					mBuffers[j].mIsActive = false;
		}
	}

	void SoundStreamBase::RetrieveQueuedBuffers() {
		ALuint buffer = 0;
		ALint queuedBuffers = 0;
		alGetSourcei(mOpenALSourceID, AL_BUFFERS_QUEUED, &queuedBuffers);
		for (ALint i = 0; i < queuedBuffers; i++) {
			alSourceUnqueueBuffers(mOpenALSourceID, 1, &buffer);
			for (Int j = 0; j < mBuffers.GetElementCount(); j++)
				if (buffer == mBuffers[j].mOpenALBufferID)
					mBuffers[j].mIsActive = false;
		}
	}

	void SoundStreamBase::SaveQueuedBufferStates() {
		ALuint buffer = 0;
		ALint queuedBuffers = 0;
		Int k = 1;
		alGetSourcei(mOpenALSourceID, AL_BUFFERS_QUEUED, &queuedBuffers);
		for (ALint i = 0; i < queuedBuffers; i++) {
			alSourceUnqueueBuffers(mOpenALSourceID, 1, &buffer);
			for (Int j = 0; j < mBuffers.GetElementCount(); j++) {
				if (buffer == mBuffers[j].mOpenALBufferID) {
					mBuffers[j].mIsActive = false;
					mBuffers[j].mQueueOrder = k;
					k++;
				}
			}
		}
	}

	void SoundStreamBase::RequeueSavedBuffers() {
		for (Int i = 1; true; i++) {
			Bool foundQueuableBuffer = false;
			for (Int j = 0; j < mBuffers.GetElementCount(); j++) {
				if (mBuffers[j].mQueueOrder == i) {
					mBuffers[j].mIsActive = true;
					alSourceQueueBuffers(mOpenALSourceID, 1,
						&mBuffers[j].mOpenALBufferID);
					foundQueuableBuffer = true;
				}
			}
			if (!foundQueuableBuffer)
				break;
		}
	}

	ErrorType SoundStreamBase::GenerateBuffers(Int numBuffers) {
		mBuffers.SetElementCount(numBuffers);
		for (Int i = 0; i < mBuffers.GetElementCount(); i++) {
			mBuffers[i].mOpenALBufferID = AL_NONE;
			mBuffers[i].mIsActive = false;
			mBuffers[i].mQueueOrder = 0;
		}
		for (Int i = 0; i < mBuffers.GetElementCount(); i++) {
			alGenBuffers(1, &mBuffers[i].mOpenALBufferID);
			if (!mBuffers[i].mOpenALBufferID) {
				for (Int j = 0; j < i; j++)
					alDeleteBuffers(1, &mBuffers[j].mOpenALBufferID);
				mBuffers.Clear();
				return Error::Throw(kErrorOpenALGenBuffersFailure,
					String("[%s(%d)]", FastFunctionName, numBuffers));
			}
		}
		return kErrorNone;
	}

	void SoundStreamBase::DeleteBuffers() {
		for (Int i = 0; i < mBuffers.GetElementCount(); i++)
			alDeleteBuffers(1, &mBuffers[i].mOpenALBufferID);
	}

	void SoundStreamBase::SetupSource(Int fadeInTime) {
		if (!mOpenALSourceID) {
			mOpenALSourceID = mContext->GetSourceID(this);
			if (mOpenALSourceID) {
				alSourcef(mOpenALSourceID, AL_PITCH, mPitch);
				alSourcei(mOpenALSourceID, AL_LOOPING, AL_FALSE);
				alSourcei(mOpenALSourceID, AL_SOURCE_RELATIVE,
					mIsRelativePosition ? AL_TRUE : AL_FALSE);
				alSource3f(mOpenALSourceID, AL_POSITION,
					mPosition.mX, mPosition.mY, mPosition.mZ);
				mFadeTime = fadeInTime;
				if (fadeInTime) {
					mIsFadingIn = true;
					alSourcef(mOpenALSourceID, AL_GAIN, 0.0f);
				} else {
					mIsFadingIn = false;
					alSourcef(mOpenALSourceID, AL_GAIN, mVolume);
				}
			}
		}
	}

	AudioContext* SoundStreamBase::GetAudioContext() {
		return mContext;
	}

	const AudioContext& SoundStreamBase::GetAudioContext() const {
		return *mContext;
	}
}
