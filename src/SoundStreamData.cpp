/******************************************************************************/
/*                                                                            */
/*  SoundStreamData.cpp                                                       */
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

#include <Fast/SoundStreamData.hpp>
#include <Fast/String.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/Error.hpp>

#include "OggStream.hpp"
#include "Undefs.hpp"

namespace Fast
{
	struct OggStreamState
	{
		OggVorbis_File	mVorbisFile;
	};

	ErrorType SoundStreamData::OpenOgg() {
		Int ret;
		ov_callbacks ovCallbacks;
		vorbis_info *vorbisInfo;
		mOggStreamState = new OggStreamState;
		ovCallbacks.read_func = OggStream::Read;
		ovCallbacks.seek_func = OggStream::Seek;
		ovCallbacks.close_func = OggStream::Close;
		ovCallbacks.tell_func = OggStream::Tell;
		ret = ov_open_callbacks((void*)mStreamReader,
			&mOggStreamState->mVorbisFile, NULL, -1, ovCallbacks);
		vorbisInfo = ov_info(&mOggStreamState->mVorbisFile, -1);
		if (vorbisInfo->channels == 1)
			mProperties.SetFormat(kSoundFormatMono16);
		else
			mProperties.SetFormat(kSoundFormatStereo16);
		mProperties.SetFrequency(vorbisInfo->rate);
		mNumTotalSamples =
			(Int)ov_pcm_total(&mOggStreamState->mVorbisFile, -1);
		return kErrorNone;
	}

	ErrorType SoundStreamData::ReadOggChunk() {
		Int bytes;
		Int bitStream;
		Int readSize = mProperties.GetSampleCount() *
			mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount();
		mSamples.SetElementCount(readSize);
		bytes = ov_read(&mOggStreamState->mVorbisFile,
			(char*)mSamples.GetData(),
			readSize, 0, 2, 1, &bitStream);
		if (bytes < 0) {
			Unload();
			return Error::Throw(kErrorEndOfStream,
				String("[%s()]", FastFunctionName));
		} else if (bytes < readSize) {
			if (mIsLooping)
				SeekTo(0);
			else
				Close();
			return kErrorNone;
		} else {
			mSampleOffset += mProperties.GetSampleCount();
			return kErrorNone;
		}
	}

	void SoundStreamData::SeekOgg() {
		ov_pcm_seek(&mOggStreamState->mVorbisFile, mSampleOffset);
	}

	void SoundStreamData::CloseOgg() {
		ov_clear(&mOggStreamState->mVorbisFile);
		delete mOggStreamState;
	}

	ErrorType SoundStreamData::OpenWav() {
		// Read header
		Char	id[4];
		Int		fileSize;
		Short	fmtTag, channels, blockAlign, bitsPerSample;
		Int		fmtLength, frequency, avgBytesPerSec, dataSize;
		mStreamReader->Read((Byte*)id, 4);
		if (memcmp(id, "RIFF", 4)) {
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(): streamReader->mName=\"%s\"]", FastFunctionName,
				mStreamReader->GetName().GetCString()));
		}
		fileSize = mStreamReader->ReadInt();
		mStreamReader->Read((Byte*)id, 4);
		if (memcmp(id, "WAVE", 4)) {
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(): streamReader->mName=\"%s\"]", FastFunctionName,
				mStreamReader->GetName().GetCString()));
		}
		mStreamReader->Read((Byte*)id, 4); // "fmt "
		fmtLength = mStreamReader->ReadInt();
		fmtTag = mStreamReader->ReadShort();
		channels = mStreamReader->ReadShort();
		frequency = mStreamReader->ReadInt();
		avgBytesPerSec = mStreamReader->ReadShort();
		blockAlign = mStreamReader->ReadShort();
		bitsPerSample = mStreamReader->ReadShort();
		mStreamReader->Read((Byte*)id, 4); // "data"
		dataSize = mStreamReader->ReadInt();
		if ((channels != 1 && channels != 2) ||
			(bitsPerSample != 8 && bitsPerSample != 16) ||
			(fmtLength != 16) || (fmtTag != 1))
		{
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(): streamReader->mName=\"%s\"]", FastFunctionName,
				mStreamReader->GetName().GetCString()));
		}
		// Set up SoundProperties
		mProperties.SetFrequency(frequency);
		if (channels == 1) {
			if (bitsPerSample == 8)
				mProperties.SetFormat(kSoundFormatMono8);
			else if (bitsPerSample == 16)
				mProperties.SetFormat(kSoundFormatMono16);
		} else if (channels == 2) {
			if (bitsPerSample == 8)
				mProperties.SetFormat(kSoundFormatStereo8);
			else if (bitsPerSample == 16)
				mProperties.SetFormat(kSoundFormatStereo16);
		}
		mNumTotalSamples = dataSize / (mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount());
		return kErrorNone;
	}

	ErrorType SoundStreamData::ReadWavChunk() {
		Long fileSize = 44 + mNumTotalSamples;
		Int readSize = mProperties.GetSampleCount() *
			mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount();
		Int bytesLeft = (Int)(fileSize - mStreamReader->GetSeekPosition());
		if (bytesLeft < readSize)
			mSamples.SetElementCount(bytesLeft);
		else
			mSamples.SetElementCount(readSize);
		mStreamReader->Read((Byte*)mSamples.GetData(),
			mSamples.GetElementCount());
		mSampleOffset += mSamples.GetElementCount() /
			(mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount());
		if (mSampleOffset >= mNumTotalSamples) {
			if (mIsLooping)
				SeekTo(0);
			else
				Close();
		}
		return kErrorNone;
	}

	void SoundStreamData::SeekWav() {
		mStreamReader->SeekTo(44 + (mSampleOffset *
			mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount()));
	}

	void SoundStreamData::CloseWav() {
		// Do nothing for now
	}

	SoundStreamData::SoundStreamData() {
		mStreamReader = 0;
		Unload();
	}

	SoundStreamData::SoundStreamData(const SoundStreamData &that) {
		mStreamReader = 0;
		Unload();
		*this = that;
	}

	SoundStreamData::SoundStreamData(
		const String &fileName, Int chunkSize)
	{
		mStreamReader = 0;
		Unload();
		Open(fileName, chunkSize);
	}

	SoundStreamData::SoundStreamData(
		StreamReader *streamReader, Int chunkSize)
	{
		mStreamReader = 0;
		Unload();
		Open(streamReader, chunkSize);
	}

	SoundStreamData::~SoundStreamData() {
		Unload();
	}

	ErrorType SoundStreamData::Open(
		const String &fileName, Int chunkSize)
	{
		Unload();
		mStreamReader = new FileReader(fileName);
		if (!mStreamReader->IsOpen()) {
			delete (FileReader*)mStreamReader;
			mStreamReader = 0;
			return Error::Throw(kErrorFileNotFound, String("[%s(\"%s\", %d)]",
				FastFunctionName, fileName.GetCString(), chunkSize));
		}
		mProperties.SetSampleCount(chunkSize);
		mAllocatedStreamReader = true;
		Char check = mStreamReader->ReadByte();
		mStreamReader->SeekTo(0);
		switch(check)
		{
		case '\x4f':
			return OpenOgg();
		case '\x52':
			return OpenWav();
		default:
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(\"%s\", %d)]", FastFunctionName,
				fileName.GetCString(), chunkSize));
		}
	}

	ErrorType SoundStreamData::Open(
		StreamReader *streamReader, Int chunkSize)
	{
		Unload();
		if (!streamReader->IsOpen())
			return Error::Throw(kErrorFileNotFound,
				String("(%s(%p, %d): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader, chunkSize,
				streamReader->GetName().GetCString()));
		mStreamReader = streamReader;
		mProperties.SetSampleCount(chunkSize);
		mStreamReader->SeekTo(0);
		Char check = mStreamReader->ReadByte();
		mStreamReader->SeekTo(0);
		switch(check)
		{
		case '\x4f':
			return OpenOgg();
		case '\x52':
			return OpenWav();
		default:
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("(%s(%p, %d): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader, chunkSize,
				streamReader->GetName().GetCString()));
		}
	}

	void SoundStreamData::Close() {
		if (!mStreamReader)
			return;
		if (!mStreamReader->IsOpen())
			return;
		switch (mFileType)
		{
		case kSoundStreamFileOgg:
			CloseOgg();
			break;
		case kSoundStreamFileWav:
			CloseWav();
			break;
		default:
			break;
		};
		mStreamReader->Close();
		if (mAllocatedStreamReader)
			delete (FileReader*)mStreamReader;
		mStreamReader = 0;
		mAllocatedStreamReader = false;
		mFileType = kSoundStreamFileNone;
		if (mSamples.IsEmpty())
			mProperties = SoundProperties();
	}

	void SoundStreamData::Unload() {
		Close();
		mSamples.Clear();
		mProperties = SoundProperties();
		mNumTotalSamples = 0;
		mAllocatedStreamReader = false;
		mFileType = kSoundStreamFileNone;
		mOggStreamState = 0;
	}

	ErrorType SoundStreamData::ReadChunk() {
		if (!mStreamReader)
			return Error::Throw(kErrorBadStream,
				String("[%s(): streamReader->mName=\"%s\"]", FastFunctionName,
				mStreamReader->GetName().GetCString()));
		if (!mStreamReader->IsOpen())
			return Error::Throw(kErrorFileNotFound,
				String("[%s(): streamReader->mName=\"%s\"]", FastFunctionName,
				mStreamReader->GetName().GetCString()));
		switch (mFileType)
		{
		case kSoundStreamFileOgg:
			return ReadOggChunk();
		case kSoundStreamFileWav:
			return ReadWavChunk();
		case kSoundStreamFileNone:
		default:
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(): streamReader->mName=\"%s\"]", FastFunctionName,
				mStreamReader->GetName().GetCString()));
		};
	}

	Int SoundStreamData::GetNumTotalSamples() const {
		return mNumTotalSamples;
	}

	Int SoundStreamData::GetDuration() const {
		if (mProperties.GetFrequency() == 0)
			return 0;
		return (mNumTotalSamples * 1000) / mProperties.GetFrequency();
	}

	Bool SoundStreamData::IsLooping() const {
		return mIsLooping;
	}

	void SoundStreamData::SetLooping(Bool setLooping) {
		mIsLooping = setLooping;
	}

	Int SoundStreamData::GetSeekTime() {
		if (!mStreamReader)
			return 0;
		if (!mStreamReader->IsOpen() || mProperties.GetFrequency() == 0)
			return 0;
		return (mSampleOffset * 1000) / mProperties.GetFrequency();
	}

	void SoundStreamData::SeekTo(Int millisecond) {
		if (!mStreamReader)
			return;
		if (!mStreamReader->IsOpen())
			return;
		mSampleOffset = (millisecond * mProperties.GetFrequency()) / 1000;
		if (mSampleOffset >= mNumTotalSamples) {
			mSampleOffset = 0;
			if (!mIsLooping)
				Close();
		}
		switch (mFileType)
		{
		case kSoundStreamFileOgg:
			SeekOgg();
			return;
		case kSoundStreamFileWav:
			SeekWav();
			return;
		default:
			return;
		};
	}

	SoundStreamData& SoundStreamData::operator=(const SoundStreamData &that) {
		this->Unload();
		this->mSamples = that.mSamples;
		this->mProperties = that.mProperties;
		this->mNumTotalSamples = that.mNumTotalSamples;
		return *this;
	}
}
