/******************************************************************************/
/*                                                                            */
/*  SoundData.cpp                                                             */
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

#include <Fast/SoundData.hpp>
#include <Fast/String.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/FileWriter.hpp>
#include <Fast/Error.hpp>

#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>
#include <ogg/ogg.h>

#include "OpenAL.hpp"
#include "OggStream.hpp"
#include "Undefs.hpp"

namespace Fast
{
	ErrorType SoundData::LoadOgg(const String &fileName) {
		FileReader fileReader(fileName);
		return LoadOgg(&fileReader);
	}

	ErrorType SoundData::LoadOgg(StreamReader *streamReader) {
		if (!streamReader->IsOpen()) {
			Unload();
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		Int bitStream;
		Int bytes;
		ALubyte chunk[kFastSoundBufferSize];
		ov_callbacks ovCallbacks;
		Int ret;
		OggVorbis_File vorbisFile;
		ovCallbacks.read_func = OggStream::Read;
		ovCallbacks.seek_func = OggStream::Seek;
		ovCallbacks.close_func = OggStream::Close;
		ovCallbacks.tell_func = OggStream::Tell;
		ret = ov_open_callbacks((void*)streamReader,
			&vorbisFile, NULL, -1, ovCallbacks);
		vorbis_info *vorbisInfo = ov_info(&vorbisFile, -1);
		if (vorbisInfo->channels == 1)
			mProperties.SetFormat(kSoundFormatMono16);
		else
			mProperties.SetFormat(kSoundFormatStereo16);
		mProperties.SetFrequency(vorbisInfo->rate);
		mProperties.SetSampleCount((Int)ov_pcm_total(&vorbisFile, -1));
		mSamples.SetElementCount(mProperties.GetSampleCount() *
			mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount());
		if (mSamples.GetElementCount() == 0) {
			Unload();
			return Error::Throw(kErrorEndOfStream,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		/* Decompress each chunk and feed into a byte array */
		Int i = 0;
		Int j = 0;
		do {
			bytes = ov_read(&vorbisFile, (char*)chunk,
				kFastSoundBufferSize, 0, 2, 1, &bitStream);
			// TODO: Proper error checking
			if (bytes < 0) {
				Unload();
				return Error::Throw(kErrorEndOfStream,
					String("[%s(%p): streamReader->mName=\"%s\"]",
					FastFunctionName, streamReader,
					streamReader->GetName().GetCString()));
			}
			for (j = 0; j < bytes; j++) {
				mSamples[i+j] = chunk[j];
			}
			i += bytes;
		} while (bytes > 0);
		ov_clear(&vorbisFile);
		return kErrorNone;
	}

	ErrorType SoundData::LoadWav(const String &fileName) {
		FileReader fr(fileName);
		return LoadWav(&fr);
	}

	ErrorType SoundData::LoadWav(StreamReader *streamReader) {
		if (!streamReader->IsOpen()) {
			Unload();
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		// Read header
		Char		id[4];
		Int			fileSize;
		Short		fmtTag, channels, blockAlign, bitsPerSample;
		Int			fmtLength, frequency, avgBytesPerSec, dataSize;
		ErrorType	error = kErrorNone;
		streamReader->Read((Byte*)id, 4);
		if (memcmp(id, "RIFF", 4)) {
			streamReader->Close();
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		fileSize = streamReader->ReadInt();
		streamReader->Read((Byte*)id, 4);
		if (memcmp(id, "WAVE", 4)) {
			streamReader->Close();
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->Read((Byte*)id, 4); // "fmt "
		fmtLength = streamReader->ReadInt();
		fmtTag = streamReader->ReadShort();
		channels = streamReader->ReadShort();
		frequency = streamReader->ReadInt();
		avgBytesPerSec = streamReader->ReadShort();
		blockAlign = streamReader->ReadShort();
		bitsPerSample = streamReader->ReadShort();
		streamReader->Read((Byte*)id, 4); // "data"
		dataSize = streamReader->ReadInt();
		if ((channels != 1 && channels != 2) ||
			(bitsPerSample != 8 && bitsPerSample != 16) ||
			(fmtLength != 16) || (fmtTag != 1))
		{
			streamReader->Close();
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
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
		mProperties.SetSampleCount(dataSize / (mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount()));
		mSamples.SetElementCount(dataSize);
		streamReader->Read((Byte*)mSamples.GetData(), dataSize);
		error = streamReader->GetError();
		if (error) {
			streamReader->Close();
			Unload();
			return Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->Close();
		return kErrorNone;
	}

	SoundData::SoundData() { }

	SoundData::SoundData(const SoundProperties &properties) {
		mProperties = properties;
		mSamples.SetElementCount(mProperties.GetSampleCount() *
			mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount());
	}

	SoundData::SoundData(const SoundProperties &properties,
		const Array<Byte> &samples)
	{
		Int byteCount = properties.GetSampleCount() *
			properties.GetChannelCount() * properties.GetSamplesByteCount();
		if (samples.GetElementCount() == byteCount) {
			mProperties = properties;
			mSamples = samples;
		}
	}

	SoundData::SoundData(const SoundData &that) {
		*this = that;
	}

	SoundData::SoundData(const String &fileName) {
		Load(fileName);
	}

	SoundData::SoundData(StreamReader *streamReader) {
		Load(streamReader);
	}

	SoundData::~SoundData() { }

	ErrorType SoundData::Load(const String &fileName) {
		Unload();
		FileReader file(fileName);
		if (!file.IsOpen())
			return Error::Throw(kErrorFileNotFound, String("[%s(\"%s\")]",
				FastFunctionName, fileName.GetCString()));
		mName = fileName;
		Char check = file.ReadByte();
		file.Close();
		switch(check)
		{
		case '\x4f':
			return LoadOgg(fileName);
		case '\x52':
			return LoadWav(fileName);
		default:
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(\"%s\")]", FastFunctionName,
				fileName.GetCString()));
		}
	}

	ErrorType SoundData::Load(StreamReader *streamReader) {
		Unload();
		if (!streamReader->IsOpen())
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		mName = streamReader->GetName();
		streamReader->SeekTo(0);
		Char check = streamReader->ReadByte();
		streamReader->SeekTo(0);
		switch (check)
		{
		case '\x4f':
			return LoadOgg(streamReader);
		case '\x52':
			return LoadWav(streamReader);
		default:
			Unload();
			return Error::Throw(kErrorSoundFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
	}

	void SoundData::Unload() {
		mProperties = SoundProperties();
		mSamples.Clear();
	}

	ErrorType SoundData::SaveAsOgg(const String &fileName, Int kbitRate, Float vbrQuality) {
		FileWriter			file;
		Int					chunkSize;
		Int					sampleFrameSize;
		ogg_stream_state	oggStreamState;
		ogg_page			oggPage;
		ogg_packet			oggPacket;
		ogg_packet			oggHeader;
		ogg_packet			oggHeaderComment;
		ogg_packet			oggHeaderCode;
		vorbis_info			vorbisInfo;
		vorbis_comment		vorbisComment;
		vorbis_dsp_state	vorbisDspState;
		vorbis_block		vorbisBlock;
		Int					ret;
		Int					streamID;
		Int					isEndOfStream;
		Int					i;

		vorbis_info_init(&vorbisInfo);
		if (kbitRate)
			ret = vorbis_encode_init(&vorbisInfo, mProperties.GetChannelCount(),
				mProperties.GetFrequency(), -1, kbitRate, -1);
		else
			ret = vorbis_encode_init_vbr(&vorbisInfo, mProperties.GetChannelCount(),
				mProperties.GetFrequency(), vbrQuality);
		switch (ret)
		{
		case 0:
			break;
		case OV_EFAULT:
			return Error::Throw(kErrorVorbisStackCorruption,
				String("[%s(\"%s\", %d, %f)]", FastFunctionName,
					fileName.GetCString(), kbitRate, vbrQuality));
		case OV_EINVAL:
			return Error::Throw(kErrorVorbisInvalidSetupRequest,
				String("[%s(\"%s\", %d, %f)]", FastFunctionName,
					fileName.GetCString(), kbitRate, vbrQuality));
		case OV_EIMPL:
			return Error::Throw(kErrorVorbisUnimplementedMode,
				String("[%s(\"%s\", %d, %f)]", FastFunctionName,
					fileName.GetCString(), kbitRate, vbrQuality));
		default:
			return Error::Throw(kErrorGeneric,
				String("[%s(\"%s\", %d, %f)]", FastFunctionName,
					fileName.GetCString(), kbitRate, vbrQuality));
		};
		vorbis_comment_init(&vorbisComment);
		vorbis_comment_add_tag(&vorbisComment, "ENCODER", "FastGdk");
		vorbis_analysis_init(&vorbisDspState, &vorbisInfo);
		vorbis_block_init(&vorbisDspState, &vorbisBlock);
		streamID = 1;
		ogg_stream_init(&oggStreamState, streamID);

		vorbis_analysis_headerout(&vorbisDspState, &vorbisComment,
			&oggHeader, &oggHeaderComment, &oggHeaderCode);
		ogg_stream_packetin(&oggStreamState, &oggHeader);
		ogg_stream_packetin(&oggStreamState, &oggHeaderComment);
		ogg_stream_packetin(&oggStreamState, &oggHeaderCode);

		isEndOfStream = 0;
		file.Open(fileName);
		while (!isEndOfStream) {
			ret = ogg_stream_flush(&oggStreamState, &oggPage);
			if (!ret)
				break;
			file.Write((Byte*)oggPage.header, (Int)oggPage.header_len);
			file.Write((Byte*)oggPage.body, (Int)oggPage.body_len);
		}

		// OpenAL get sound buffer, into 'buf' variable
		sampleFrameSize = mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount();
		chunkSize = sampleFrameSize * kFastSoundBufferSize;
		for (i = 0; !isEndOfStream; i++) {
			Int j;
			Int bytesLeft;
			Int bytes;

			bytesLeft = mSamples.GetElementCount() - (i * chunkSize);
			if (bytesLeft < chunkSize)
				bytes = bytesLeft;
			else
				bytes = chunkSize;
			if (chunkSize * i == mSamples.GetElementCount())
				vorbis_analysis_wrote(&vorbisDspState, 0);
			else {
				Float **buffer = vorbis_analysis_buffer(
					&vorbisDspState, kFastSoundBufferSize);
				for (j = 0; j < bytes / sampleFrameSize; j++) {
					buffer[0][j] = ((mSamples[(i * chunkSize) +
						(j * sampleFrameSize + 1)] << 8) |
						(0x00ff & (Int)mSamples[(i * chunkSize) +
						(j * sampleFrameSize)])) /
						32786.0f;
					buffer[1][j] = ((mSamples[(i * chunkSize) +
						(j * sampleFrameSize + 3)] << 8) |
						(0x00ff & (Int)mSamples[(i * chunkSize) +
						(j * sampleFrameSize + 2)])) /
						32768.0f;
				}
				vorbis_analysis_wrote(&vorbisDspState, j);
			}

			while (vorbis_analysis_blockout(&vorbisDspState, &vorbisBlock) == 1)
			{
				vorbis_analysis(&vorbisBlock, NULL);
				vorbis_bitrate_addblock(&vorbisBlock);
				while(vorbis_bitrate_flushpacket(&vorbisDspState, &oggPacket)) {
					ogg_stream_packetin(&oggStreamState, &oggPacket);
					while (!isEndOfStream) {
						ret = ogg_stream_pageout(&oggStreamState, &oggPage);
						if (!ret)
							break;
						file.Write((Byte*)oggPage.header,
							(Int)oggPage.header_len);
						file.Write((Byte*)oggPage.body, (Int)oggPage.body_len);
						if (ogg_page_eos(&oggPage))
							isEndOfStream = 1;
					}
				}
			}
		}

		ogg_stream_clear(&oggStreamState);
		vorbis_block_clear(&vorbisBlock);
		vorbis_dsp_clear(&vorbisDspState);
		vorbis_comment_clear(&vorbisComment);
		vorbis_info_clear(&vorbisInfo);
		//ogg_stream_destroy(&oggStreamState);

		return kErrorNone;
	}

	ErrorType SoundData::SaveAsWav(const String &fileName) {
		ErrorType error;
		FileWriter fileWriter;
		if (mSamples.GetElementCount() == 0)
			return Error::Throw(kErrorEndOfStream, String("[%s(\"%s\")]",
				FastFunctionName, fileName.GetCString()));
		error = kErrorNone;
		fileWriter.Open(fileName);
		if (!fileWriter.IsOpen())
			return Error::Throw(kErrorFileCreationFailure,
			String("[%s(\"%s\")]", FastFunctionName, fileName.GetCString()));
		fileWriter.Write("RIFF", 4);							// ChunkID
		fileWriter.WriteInt(36 + mSamples.GetElementCount());	// ChunkSize
		fileWriter.Write("WAVE", 4);							// Format
		fileWriter.Write("fmt ", 4);							// Subchunk1ID
		fileWriter.WriteInt(16);								// SubChunk1Size
		fileWriter.WriteShort(1);								// AudioFormat
		fileWriter.WriteShort((Short)
			mProperties.GetChannelCount());						// NumChannels
		fileWriter.WriteInt(mProperties.GetFrequency());		// SampleRate
		fileWriter.WriteInt(mProperties.GetFrequency() *		// ByteRate
			mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount());
		fileWriter.WriteShort((Short)							// BlockAlign
			(mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount()));
		fileWriter.WriteShort((Short)							// BitsPerSample
			(mProperties.GetSamplesByteCount() * 8));
		fileWriter.Write("data", 4);							// Subchunk2ID
		fileWriter.WriteInt(mSamples.GetElementCount());		// Subchunk2Size
		fileWriter.Write(mSamples.GetData(),					// Data
			mSamples.GetElementCount());
		error = fileWriter.GetError();
		fileWriter.Close();
		return error ? Error::Throw(error, String("[%s(\"%s\")]",
			FastFunctionName, fileName.GetCString())) : kErrorNone;
	}

	SoundData & SoundData::operator=(const SoundData &that) {
		this->Unload();
		this->mSamples = that.mSamples;
		this->mProperties = that.mProperties;
		return *this;
	}

	Bool SoundData::operator==(const SoundData &that) const {
		if (this->mProperties != that.mProperties)
			return false;
		if (memcmp(this->mSamples.GetData(), that.mSamples.GetData(),
			this->mSamples.GetElementCount()))
		{
			return false;
		}
		return true;
	}

	Bool SoundData::operator!=(const SoundData &that) const {
		if (this->mProperties != that.mProperties)
			return true;
		if (memcmp(this->mSamples.GetData(), that.mSamples.GetData(),
			this->mSamples.GetElementCount()))
		{
			return true;
		}
		return false;
	}
}
