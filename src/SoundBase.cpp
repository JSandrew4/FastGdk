/******************************************************************************/
/*                                                                            */
/*  SoundBase.cpp                                                             */
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

#include <Fast/SoundBase.hpp>
#include <Fast/Math.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	void SoundBase::ResetBaseSourceProperties() {
		mOpenALSourceID		= 0;
		mImportance			= 0;
		mVolume				= 1.0f;
		mPitch				= 1.0f;
		mPosition			= kFastVector3DZero;
		mIsRelativePosition	= false;
	}

	void SoundBase::ResetBaseStateProperties() {
		mIsPlaying		= false;
		mIsPaused		= false;
		mIsStopped		= true;
		mIsFadingIn		= false;
		mIsFadingOut	= false;
		mFadeTime		= 0;
	}

	void SoundBase::HandleFading(Int elapsedMilliseconds) {
		ALfloat currentVolume;
		if (mIsFadingIn) {
			alGetSourcef(mOpenALSourceID, AL_GAIN, &currentVolume);
			currentVolume += (ALfloat)((mVolume / mFadeTime) /
				(1000.0f / elapsedMilliseconds));
			if (currentVolume >= mVolume) {
				alSourcef(mOpenALSourceID, AL_GAIN, mVolume);
				mIsFadingIn = false;
				mFadeTime = 0;
			} else
				alSourcef(mOpenALSourceID, AL_GAIN, currentVolume);
		}
		if (mIsFadingOut) {
			alGetSourcef(mOpenALSourceID, AL_GAIN, &currentVolume);
			currentVolume -= (ALfloat)((mVolume / mFadeTime) /
				(1000.0f / (Float)elapsedMilliseconds));
			if (currentVolume <= 0.0f) {
				if (mIsStopped)
					Stop();
				else if (mIsPaused)
					Pause();
			} else
				alSourcef(mOpenALSourceID, AL_GAIN, currentVolume);
		}
	}

	UInt SoundBase::GetOpenALSourceID() const {
		return mOpenALSourceID;
	}

	Int SoundBase::GetImportance() const {
		return mImportance;
	}

	Float SoundBase::GetVolume() const {
		return mVolume;
	}

	Float SoundBase::GetPitch() const {
		return mPitch;
	}

	const Vector3D & SoundBase::GetPosition() const {
		return mPosition;
	}

	Bool SoundBase::IsRelativePosition() const {
		return mIsRelativePosition;
	}

	void SoundBase::SetImportance(Int importance) {
		mImportance = importance;
	}

	void SoundBase::SetVolume(Float aVolume) {
		mVolume = Math::ClampFloat(aVolume, 0.0f, 1.0f);
		if (mOpenALSourceID)
			alSourcef(mOpenALSourceID, AL_GAIN, mVolume);
	}

	void SoundBase::SetPitch(Float pitch) {
		mPitch = pitch;
		if (mOpenALSourceID)
			alSourcef(mOpenALSourceID, AL_PITCH, mPitch);
	}

	void SoundBase::SetPosition(const Vector3D &position) {
		mPosition = position;
		if (mOpenALSourceID)
			alSource3f(mOpenALSourceID, AL_POSITION,
				mPosition.mX, mPosition.mY, mPosition.mZ);
	}

	void SoundBase::SetRelativePosition(Bool isRelativePosition) {
		mIsRelativePosition = isRelativePosition;
		if (mOpenALSourceID)
			alSourcei(mOpenALSourceID, AL_SOURCE_RELATIVE,
				mIsRelativePosition ? AL_TRUE : AL_FALSE);
	}

	Bool SoundBase::IsPlaying() const {
		return mIsPlaying;
	}

	Bool SoundBase::IsPaused() const {
		return mIsPaused;
	}

	Bool SoundBase::IsStopped() const {
		return mIsStopped;
	}

	Bool SoundBase::IsFadingIn() const {
		return mIsFadingIn;
	}

	Bool SoundBase::IsFadingOut() const {
		return mIsFadingOut;
	}
}
