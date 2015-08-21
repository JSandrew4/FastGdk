/******************************************************************************/
/*                                                                            */
/*  SoundFileStream.cpp                                                       */
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

#include <Fast/SoundFileStream.hpp>
#include <Fast/SoundBase.hpp>
#include <Fast/String.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	void SoundFileStream::QueueBuffers() {
		if (mOpenALSourceID) {
			for (Int i = 0; i < mBuffers.GetElementCount(); i++) {
				if (!mBuffers[i].mIsActive) {
					mStreamData.ReadChunk();
					alBufferData(mBuffers[i].mOpenALBufferID,
						mStreamData.GetProperties()->GetFormat(),
						mStreamData.GetSamples().GetData(),
						mStreamData.GetSamples().GetElementCount(),
						mStreamData.GetProperties()->GetFrequency());
					alSourceQueueBuffers(mOpenALSourceID, 1,
						&mBuffers[i].mOpenALBufferID);
					mBuffers[i].mIsActive = true;
				}
			}
		}
	}

	SoundFileStream::SoundFileStream(AudioContext *context) {
		mContext = context;
		Close();
	}

	SoundFileStream::SoundFileStream(const String &fileName,
		AudioContext *context, Int numBuffers)
	{
		mContext = context;
		Close();
		Open(fileName, numBuffers);
	}

	SoundFileStream::SoundFileStream(StreamReader *streamReader,
		AudioContext *context, Int numBuffers)
	{
		mContext = context;
		Close();
		Open(streamReader, numBuffers);
	}

	SoundFileStream::~SoundFileStream() {
		Close();
	}

	ErrorType SoundFileStream::Open(const String &fileName, Int numBuffers) {
		Close();
		ErrorType error = GenerateBuffers(numBuffers);
		if (error) {
			Close();
			return Error::Throw(error, String("[%s(\"%s\", %d)]",
				FastFunctionName, fileName.GetCString(), numBuffers));
		}
		error = mStreamData.Open(fileName);
		if (error) {
			Close();
			return Error::Throw(error, String("[%s(\"%s\", %d)]",
				FastFunctionName, fileName.GetCString(), numBuffers));
		}
		return kErrorNone;
	}

	ErrorType SoundFileStream::Open(StreamReader *streamReader, Int numBuffers)
	{
		Close();
		ErrorType error = GenerateBuffers(numBuffers);
		if (error) {
			Close();
			return Error::Throw(error,
				String("[%s(%p, %d): streamReader.mName=\"%s\"]",
					FastFunctionName, streamReader, numBuffers,
					streamReader->GetName().GetCString()));
		}
		error = mStreamData.Open(streamReader);
		if (error) {
			Close();
			return Error::Throw(error,
				String("[%s(%p, %d): streamReader.mName=\"%s\"]",
					FastFunctionName, streamReader, numBuffers,
					streamReader->GetName().GetCString()));
		}
		return kErrorNone;
	}

	void SoundFileStream::Close() {
		// Clean up everything
		Stop();
		if (mBuffers.GetElementCount() > 0)
			DeleteBuffers();
		mStreamData.Close();
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

	void SoundFileStream::Play(Int fadeInTime) {
		SetupSource(fadeInTime);
		if (mOpenALSourceID) {
			RequeueSavedBuffers();
			QueueBuffers();
			alSourcePlay(mOpenALSourceID);
			mIsStopped = false;
			mIsPaused = false;
			mIsPlaying = true;
		}
	}

	void SoundFileStream::Pause(Int fadeOutTime) {
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

	void SoundFileStream::Stop(Int fadeOutTime) {
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

	void SoundFileStream::Update(Int elapsedMilliseconds) {
		if (mOpenALSourceID) {
			QueueBuffers();
			ALint alState;
			alGetSourcei(mOpenALSourceID, AL_SOURCE_STATE, &alState);
			if (alState != AL_PLAYING)
				alSourcePlay(mOpenALSourceID);
			HandleFading(elapsedMilliseconds);
		}
	}

	Int SoundFileStream::GetNumTotalSamples() const {
		return mStreamData.GetNumTotalSamples();
	}

	Int SoundFileStream::GetDuration() const {
		return mStreamData.GetDuration();
	}

	Bool SoundFileStream::IsLooping() const {
		return mStreamData.IsLooping();
	}

	void SoundFileStream::SetLooping(Bool setLooping) {
		return mStreamData.SetLooping(setLooping);
	}

	Int SoundFileStream::GetSeekTime() {
		return mStreamData.GetSeekTime();
	}

	void SoundFileStream::SeekTo(Int millisecond) {
		return mStreamData.SeekTo(millisecond);
	}
}
