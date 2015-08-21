/******************************************************************************/
/*                                                                            */
/*  FileWriter.cpp                                                            */
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

#include <Fast/FileWriter.hpp>
#include <Fast/String.hpp>
#include <Fast/Error.hpp>

#include <cstdio>

#include "Undefs.hpp"

namespace Fast
{
	FileWriter::FileWriter() {
		mFile = 0;
	}

	FileWriter::FileWriter(const String &fileName, Bool truncate) {
		mFile = 0;
		Open(fileName, truncate);
	}

	FileWriter::~FileWriter() {
		Close();
	}

	void FileWriter::Close() {
		if (IsOpen()) {
			fclose((FILE*)mFile);
			mFile = 0;
		}
		mName.Clear();
	}

	void FileWriter::Flush() {
		fflush((FILE*)mFile);
	}

	Bool FileWriter::IsOpen() {
		return mFile ? true : false;
	}

	Long FileWriter::GetSize() {
		long oldPosition, endOfFile;
		oldPosition = ftell((FILE*)mFile);
		fseek((FILE*)mFile, 0, SEEK_END);
		endOfFile = ftell((FILE*)mFile);
		fseek((FILE*)mFile, oldPosition, SEEK_SET);
		return (Long)endOfFile;
	}

	ErrorType FileWriter::GetError() {
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

	void FileWriter::SeekTo(Long seekPosition) {
		fseek((FILE*)mFile, (long)seekPosition, SEEK_SET);
	}

	Long FileWriter::GetSeekPosition() {
		return (Long)ftell((FILE*)mFile);
	}

	void FileWriter::Write(const Byte *data, Long size) {
		fwrite(data, 1, (size_t)size, (FILE*)mFile);
	}

	void FileWriter::Open(const String &fileName, Bool truncate) {
		if (fileName.IsEmpty())
			return;
	#if defined(FastOSWindows)
		_wfopen_s((FILE**)&mFile, fileName.GetWString().mData,
			truncate ? L"wb+" : L"rb+");
	#else
		mFile = (CFILE*)fopen(fileName.GetData(),
			truncate ? "wb+" : "rb+");
	#endif
		mName = fileName;
	}
}
