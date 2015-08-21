/******************************************************************************/
/*                                                                            */
/*  SoundSource.cpp                                                           */
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

#include <Fast/SoundSource.hpp>
#include <Fast/SoundBase.hpp>
#include <Fast/SoundData.hpp>
#include <Fast/String.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/Checksum.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	void SoundSource::SetupSource(Int fadeInTime) {
		if (!mOpenALSourceID && GetResource().GetOpenALBufferID()) {
			mOpenALSourceID =
				GetCollection()->GetAudioContext()->GetSourceID(this);
			if (mOpenALSourceID) {
				alSourcei(mOpenALSourceID, AL_BUFFER, GetResource().GetOpenALBufferID());
				alSourcei(mOpenALSourceID, AL_SAMPLE_OFFSET, mSampleOffset);
				alSourcef(mOpenALSourceID, AL_PITCH, mPitch);
				alSourcei(mOpenALSourceID, AL_LOOPING, mIsLooping ?
					AL_TRUE : AL_FALSE);
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

	ErrorType SoundSource::LoadResource(const String &name,
		const SoundData &soundData, SoundCollection *collection)
	{
		// Check for existing sound with matching checksum
		Checksum checksum(soundData.GetSamples().GetData(),
			soundData.GetSamples().GetElementCount());
		Bind(collection, collection->GetIDByChecksum(checksum));
		if (-1 < mID)
			return kErrorNone;
		// No sound was found, generate new buffer
		UInt openALID;
		alGenBuffers(1, &openALID);
		if (!openALID)
			return Error::Throw(kErrorOpenALGenBuffersFailure,
				String("[%s(\"%s\", %p)]", FastFunctionName,
				name.GetCString(), &soundData));
		SoundResource soundResource;
		soundResource.SetName(name);
		soundResource.SetChecksum(checksum);
		soundResource.GetProperties()->SetFormat(soundData.GetProperties().GetFormat());
		soundResource.GetProperties()->SetFrequency(soundData.GetProperties().GetFrequency());
		soundResource.GetProperties()->SetSampleCount(soundData.GetProperties().GetSampleCount());
		soundResource.SetOpenALBufferID(openALID);
		soundResource.SetActive(true);
		mID = collection->AddResource(soundResource, this);
		mCollection = collection;
		{
			alBufferData(GetResource().GetOpenALBufferID(),
				GetResource().GetProperties().GetFormat(),
				soundData.GetSamples().GetData(),
				soundData.GetSamples().GetElementCount(),
				GetResource().GetProperties().GetFrequency());
			ALint alErr = alGetError();
			switch (alErr)
			{
			case AL_OUT_OF_MEMORY:
				Unbind();
				return Error::Throw(kErrorOutOfMemory,
					String("[%s(\"%s\", %p)]", FastFunctionName,
					name.GetCString(), &soundData));
			case AL_INVALID_ENUM:
			case AL_INVALID_VALUE:
				Unbind();
				return Error::Throw(kErrorInvalidValue,
					String("[%s(\"%s\", %p)]", FastFunctionName,
					name.GetCString(), &soundData));
			}
		}
		return kErrorNone;
	}

	SoundSource::SoundSource()
	:	AssetImplementer()
	{
		Unbind();
	}

	SoundSource::SoundSource(const SoundSource &that)
	:	AssetImplementer()
	{
		*this = that;
	}

	SoundSource::SoundSource(const String &fileName,
		SoundCollection *collection)
	:	AssetImplementer()
	{
		Load(fileName, collection);
	}

	SoundSource::SoundSource(StreamReader *streamReader,
		SoundCollection *collection)
	:	AssetImplementer()
	{
		Load(streamReader, collection);
	}

	SoundSource::SoundSource(const SoundData &soundData,
		SoundCollection *collection)
	:	AssetImplementer()
	{
		Load(soundData, collection);
	}

	SoundSource::~SoundSource() {
		Unbind();
	}

	ErrorType SoundSource::Load(const String &fileName,
		SoundCollection *collection)
	{
		Stop();
		Bind(collection, collection->GetIDByName(fileName));
		if (-1 < mID)
			return kErrorNone;
		// No sound was found, load the sound data
		SoundData soundData;
		ErrorType error = soundData.Load(fileName);
		if (error)
			return Error::Throw(error, String("[%s(\"%s\")]",
				FastFunctionName, fileName.GetCString()));
		return LoadResource(fileName, soundData, collection);
	}

	ErrorType SoundSource::Load(StreamReader *streamReader,
		SoundCollection *collection)
	{
		String name = streamReader->GetName();
		Stop();
		Bind(collection, collection->GetIDByName(name));
		if (-1 < mID)
			return kErrorNone;
		// No sound was found, load the sound data
		SoundData soundData;
		ErrorType error = soundData.Load(streamReader);
		if (error)
			return Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\"]",
					FastFunctionName, streamReader,
					streamReader->GetName().GetCString()));
		return LoadResource(name, soundData, collection);
	}

	ErrorType SoundSource::Load(const SoundData &soundData,
		SoundCollection *collection)
	{
		String name = soundData.GetName();
		Stop();
		Bind(collection, collection->GetIDByName(name));
		if (-1 < mID)
			return kErrorNone;
		// No sound was found, load the sound data
		return LoadResource(name, soundData, collection);
	}

	void SoundSource::Unbind() {
		Stop();
		Bind(NULL, -1);
		ResetBaseSeekableProperties();
		ResetBaseSourceProperties();
		ResetBaseStateProperties();
	}

	void SoundSource::Play(Int fadeInTime) {
		SetupSource(fadeInTime);
		if (mOpenALSourceID) {
			alSourcePlay(mOpenALSourceID);
			mIsStopped = false;
			mIsPaused = false;
			mIsPlaying = true;
		}
	}

	void SoundSource::Pause(Int fadeOutTime) {
		if (mOpenALSourceID) {
			GetSeekTime();
			mIsPaused = true;
			mIsPlaying = false;
			mIsStopped = false;
			mFadeTime = fadeOutTime;
			mIsFadingIn = false;
			if (fadeOutTime) {
				mIsFadingOut = true;
			} else {
				mIsFadingOut = false;
				alSourceStop(mOpenALSourceID);
				alSourcei(mOpenALSourceID, AL_BUFFER, AL_NONE);
				mOpenALSourceID = 0;
				GetCollection()->GetAudioContext()->FreeSourceID(this);
			}
		}
	}

	void SoundSource::Stop(Int fadeOutTime) {
		mIsPaused = false;
		mIsPlaying = false;
		mIsStopped = true;
		mFadeTime = fadeOutTime;
		mIsFadingIn = false;
		if (mOpenALSourceID) {
			if (fadeOutTime) {
				mIsFadingOut = true;
			} else {
				mIsFadingOut = false;
				mSampleOffset = 0;
				alSourceStop(mOpenALSourceID);
				alSourcei(mOpenALSourceID, AL_BUFFER, AL_NONE);
				mOpenALSourceID = 0;
				GetCollection()->GetAudioContext()->FreeSourceID(this);
			}
		}
	}

	void SoundSource::Update(Int elapsedMilliseconds) {
		if (mOpenALSourceID) {
			// Stop sound if source is done playing
			ALint alState;
			alGetSourcei(mOpenALSourceID, AL_SOURCE_STATE, &alState);
			if (alState == AL_STOPPED)
				Stop();
			// Handle fading in/out
			ALfloat currentVolume;
			if (mIsFadingIn) {
				alGetSourcef(mOpenALSourceID, AL_GAIN, &currentVolume);
				currentVolume += (ALfloat)((mVolume / mFadeTime) /
					(1000.0f / elapsedMilliseconds));
				if (currentVolume >= mVolume) {
					alSourcef(mOpenALSourceID, AL_GAIN, mVolume);
					mIsFadingIn = false;
					mFadeTime = 0;
				} else {
					alSourcef(mOpenALSourceID, AL_GAIN, currentVolume);
				}
			}
			if (mIsFadingOut) {
				alGetSourcef(mOpenALSourceID, AL_GAIN, &currentVolume);
				currentVolume -= (ALfloat)((mVolume / mFadeTime) /
					(1000.0f / elapsedMilliseconds));
				if (currentVolume <= 0.0f)
					Stop();
				else
					alSourcef(mOpenALSourceID, AL_GAIN, currentVolume);
			}
		}
	}

	Int SoundSource::GetDuration() const {
		if (0 > mID)
			return 0;
		return (GetResource().GetProperties().GetSampleCount() * 1000) /
			GetResource().GetProperties().GetFrequency();
	}

	Bool SoundSource::IsLooping() const {
		return mIsLooping;
	}

	void SoundSource::SetLooping(Bool setLooping) {
		mIsLooping = setLooping;
		if (mOpenALSourceID)
			alSourcei(mOpenALSourceID, AL_LOOPING,
				mIsLooping ? AL_TRUE : AL_FALSE);
	}

	Int SoundSource::GetSeekTime() {
		if (mOpenALSourceID)
			alGetSourcei(mOpenALSourceID, AL_SAMPLE_OFFSET, &mSampleOffset);
		return (mSampleOffset * 1000) /
			GetResource().GetProperties().GetFrequency();
	}

	void SoundSource::SeekTo(Int millisecond) {
		mSampleOffset = (millisecond *
			GetResource().GetProperties().GetFrequency()) / 1000;
		if (mSampleOffset >= GetResource().GetProperties().GetSampleCount()) {
			mSampleOffset = 0;
			if (!mIsLooping)
				Stop();
		}
		if (mOpenALSourceID)
			alSourcei(mOpenALSourceID, AL_SAMPLE_OFFSET, mSampleOffset);
	}

	SoundSource& SoundSource::operator=(const SoundSource &that) {
		this->Bind(that.mCollection, that.mID);
		return *this;
	}

	Bool SoundSource::operator==(const SoundSource &that) const {
		if (&this->GetCollection() != &that.GetCollection())
			return false;
		if (this->mID != that.mID)
			return false;
		return true;
	}

	Bool SoundSource::operator!=(const SoundSource &that) const {
		if (&this->GetCollection() != &that.GetCollection())
			return true;
		if (this->mID != that.mID)
			return true;
		return false;
	}
}
