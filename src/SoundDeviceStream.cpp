/******************************************************************************/
/*                                                                            */
/*  SoundDeviceStream.cpp                                                     */
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

#include <Fast/SoundDeviceStream.hpp>
#include <Fast/SoundCapture.hpp>
#include <Fast/SoundBase.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/Error.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	SoundDeviceStream::SoundDeviceStream(AudioContext *context) : mContext(context) {
		mCapture = NULL;
		Close();
	}

	SoundDeviceStream::~SoundDeviceStream() {
		Close();
	}

	ErrorType SoundDeviceStream::Open(SoundCapture *capture, Int numBuffers)
	{
		Close();
		mCapture = capture;
		ErrorType error = GenerateBuffers(numBuffers);
		if (error) {
			Close();
			return Error::Throw(error,
				String("[%s(%p, %d)]", FastFunctionName,
					capture, numBuffers));
		}
		return kErrorNone;
	}

	void SoundDeviceStream::Close() {
		// Clean up everything
		Stop();
		if (mBuffers.GetElementCount() > 0)
			DeleteBuffers();
		mCapture =				0;
		// Set SoundBase variables to defaults
		mContext =				0;
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

	void SoundDeviceStream::Play(Int fadeInTime) {
		SetupSource(fadeInTime);
		if (mOpenALSourceID) {
			// Start capturing sound now and source
			//  will start to play in Update() as
			//  soon as we have some data to work with
			mCapture->StartCapturing();
			mIsStopped = false;
			mIsPaused = false;
			mIsPlaying = true;
		}
	}

	void SoundDeviceStream::Pause(Int fadeOutTime) {
		if (mOpenALSourceID) {
			mFadeTime = fadeOutTime;
			if (mFadeTime < 1) {
				alSourceStop(mOpenALSourceID);
				RetrieveProcessedBuffers();
				RetrieveQueuedBuffers();
				mContext->FreeSourceID(this);
				mOpenALSourceID = 0;
				mCapture->StopCapturing();
				mIsFadingOut = false;
			} else
				mIsFadingOut = true;
			mIsStopped = false;
			mIsPaused = true;
			mIsStopped = false;
		}
	}

	void SoundDeviceStream::Stop(Int fadeOutTime) {
		if (mOpenALSourceID) {
			mFadeTime = fadeOutTime;
			if (mFadeTime < 1) {
				alSourceStop(mOpenALSourceID);
				RetrieveProcessedBuffers();
				RetrieveQueuedBuffers();
				mContext->FreeSourceID(this);
				mOpenALSourceID = 0;
				mCapture->StopCapturing();
				mIsFadingOut = false;
			} else
				mIsFadingOut = true;
		}
		mIsStopped = false;
		mIsPaused = false;
		mIsStopped = true;
	}

	void SoundDeviceStream::Update(Int elapsedMilliseconds) {
		if (mOpenALSourceID) {
			// Queue sound data if needed
			RetrieveProcessedBuffers();
			for (Int i = 0; i < mBuffers.GetElementCount() &&
				mCapture->GetNumBuffersToBeRead() > 0; i++)
			{
				if (!mBuffers[i].mIsActive) {
					SoundData soundData;
					mCapture->GetBufferData(&soundData);
					alBufferData(mBuffers[i].mOpenALBufferID,
						soundData.GetProperties()->GetFormat(),
						soundData.GetSamples().GetData(),
						soundData.GetSamples().GetElementCount(),
						soundData.GetProperties()->GetFrequency());
					alSourceQueueBuffers(mOpenALSourceID, 1,
						&mBuffers[i].mOpenALBufferID);
					mBuffers[i].mIsActive = true;
				}
			}
			// Keep sound playing
			ALint alState;
			alGetSourcei(mOpenALSourceID, AL_SOURCE_STATE, &alState);
			if (alState != AL_PLAYING)
				alSourcePlay(mOpenALSourceID);
			// Handle fading in and out
			HandleFading(elapsedMilliseconds);
		}
	}
}
