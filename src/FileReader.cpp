/******************************************************************************/
/*                                                                            */
/*  FileReader.cpp                                                            */
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

#include <Fast/FileReader.hpp>
#include <Fast/String.hpp>
#include <Fast/Error.hpp>

#include <cstdio>

#include "Undefs.hpp"

namespace Fast
{
	FileReader::FileReader() {
		mFile = 0;
	}

	FileReader::FileReader(const String &fileName) {
		mFile = 0;
		Open(fileName);
	}

	FileReader::~FileReader() {
		Close();
	}

	void FileReader::Close() {
		if (IsOpen()) {
			fclose((FILE*)mFile);
			mFile = 0;
		}
		mName.Clear();
	}

	void FileReader::Flush() {
		fflush((FILE*)mFile);
	}

	Bool FileReader::IsOpen() {
		return mFile ? true : false;
	}

	Long FileReader::GetSize() {
		long oldPosition, endOfFile;
		oldPosition = ftell((FILE*)mFile);
		fseek((FILE*)mFile, 0, SEEK_END);
		endOfFile = ftell((FILE*)mFile);
		fseek((FILE*)mFile, oldPosition, SEEK_SET);
		return (Long)endOfFile;
	}

	ErrorType FileReader::GetError() {
		ErrorType error = kErrorNone;
		if (IsOpen()) {
			if (ferror((FILE*)mFile)) {
				if (feof((FILE*)mFile))
					error = kErrorEndOfStream;
				else
					error = kErrorBadStream;
			}
			clearerr((FILE*)mFile);
		} else {
			error = kErrorFileNotFound;
		}
		return error;
	}

	void FileReader::SeekTo(Long seekPosition) {
		fseek((FILE*)mFile, (long)seekPosition, SEEK_SET);
	}

	Long FileReader::GetSeekPosition() {
		return (Long)ftell((FILE*)mFile);
	}

	void FileReader::Read(Byte *data, Long size) {
		fread(data, 1, (size_t)size, (FILE*)mFile);
	}

	void FileReader::Open(const String & fileName) {
		if (fileName.IsEmpty())
			return;
	#if defined(FastOSWindows)
		_wfopen_s((FILE**)&mFile, fileName.GetWString().mData, L"rb");
	#else
		mFile = (CFILE*)fopen(fileName.GetData(), "rb");
	#endif
		mName = fileName;
	}
}
