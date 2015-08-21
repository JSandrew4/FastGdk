/******************************************************************************/
/*                                                                            */
/*  SoundStreamData.hpp                                                       */
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

#ifndef FastSoundStreamDataHppIncluded
#define FastSoundStreamDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/SoundDataBase.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/SoundStreamFileType.hpp>
#include <Fast/SoundSeekable.hpp>

namespace Fast
{
	class String;
	struct OggStreamState;
	class StreamReader;

	class FastApi SoundStreamData : public SoundDataBase, public SoundSeekable
	{
	private:
		StreamReader		*mStreamReader;
		Bool				mAllocatedStreamReader;
		SoundStreamFileType	mFileType;
		OggStreamState		*mOggStreamState;
		Int					mNumTotalSamples;
		// Specific format open functions
		ErrorType	OpenOgg();
		ErrorType	ReadOggChunk();
		void		SeekOgg();
		void		CloseOgg();
		ErrorType	OpenWav();
		ErrorType	ReadWavChunk();
		void		SeekWav();
		void		CloseWav();
	public:
		// (Con/De)structors
		SoundStreamData();
		SoundStreamData(const SoundStreamData &that);
		SoundStreamData(const String &fileName, Int chunkSize = 2048);
		SoundStreamData(StreamReader *streamReader, Int chunkSize = 2048);
		~SoundStreamData();
		// File handling functions
		ErrorType	Open(const String &fileName, Int chunkSize = 2048);
		ErrorType	Open(StreamReader *streamReader, Int chunkSize = 2048);
		void		Close();
		void		Unload();
		ErrorType	ReadChunk();
		// Seekable functions
		Int			GetNumTotalSamples() const;
		Int			GetDuration() const;
		Bool		IsLooping() const;
		void		SetLooping(Bool setLooping);
		Int			GetSeekTime();
		void		SeekTo(Int millisecond);
		// Assignment operator
		SoundStreamData&	operator=(const SoundStreamData &that);
	};
}

#endif // FastSoundStreamDataHppIncluded
