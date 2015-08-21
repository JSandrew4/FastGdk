/******************************************************************************/
/*                                                                            */
/*  SoundCollection.cpp                                                       */
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

#include <Fast/SoundCollection.hpp>
#include <Fast/SoundData.hpp>
#include <Fast/SoundSource.hpp>
#include <Fast/SoundFormat.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/SoundSource.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{/* TODO: Remove
	void SoundCollection::BuildDefaultResource() {
		mResources.SetElementCount(1);
		SoundProperties sp(kSoundFormatMono8, 44100, 1024);
		SoundData sd(sp, Array<Byte>(sp.GetSamplesByteCount() *
			sp.GetChannelCount() * sp.GetSampleCount(), 0));
		sd.SetName("DefaultSound");
		SoundSource ss(sd, this);
		SetResourceRetained(AddResource(ss.GetResource(), &ss), true);
	}
	*/
	SoundCollection::SoundCollection(AudioContext *audioContext) :
		mAudioContext(*audioContext)
	{ }

	SoundCollection::~SoundCollection() {
		UnloadAllResources();
	}

	ErrorType SoundCollection::LoadResource(const String &fileName) {
		SoundSource sound;
		ErrorType error = sound.Load(fileName, this);
		if (!error)
			SetResourceRetained(sound.GetID(), true);
		return error;
	}

	ErrorType SoundCollection::LoadResource(StreamReader *streamReader) {
		SoundSource sound;
		ErrorType error = sound.Load(streamReader, this);
		if (!error)
			SetResourceRetained(sound.GetID(), true);
		return error;
	}

	ErrorType SoundCollection::LoadResource(const AssetData &assetData) {
		SoundSource sound;
		ErrorType error = sound.Load((SoundData&)assetData, this);
		if (!error)
			SetResourceRetained(sound.GetID(), true);
		return error;
	}

	void SoundCollection::UnloadResource(Int id) {
		UInt openALBufferID = mResources[id].GetOpenALBufferID();
		UnloadReferences(id);
		alDeleteBuffers(1, &openALBufferID);
		mResources[id].SetActive(false);
	}

	AudioContext* SoundCollection::GetAudioContext() {
		return &mAudioContext;
	}

	const AudioContext& SoundCollection::GetAudioContext() const {
		return mAudioContext;
	}
}
