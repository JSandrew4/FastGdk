/******************************************************************************/
/*                                                                            */
/*  ZipFileReader.cpp                                                         */
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

#include <Fast/ZipFileReader.hpp>
#include <Fast/ZipArchive.hpp>

#include <zip.h>

#include "Undefs.hpp"

namespace Fast
{
	ZipFileReader::ZipFileReader() {
		mFile = 0;
		Close();
	}

	ZipFileReader::ZipFileReader(const String &fileName, ZipArchive *archive) {
		mFile = 0;
		Open(fileName, archive);
	}

	ZipFileReader::~ZipFileReader() {
		Close();
	}

	void ZipFileReader::Close() {
		if (IsOpen()) {
			zip_fclose((zip_file*)mFile);
		}
		mFile = 0;
		mArchive = 0;
		mName.Clear();
		mSeekPosition = 0;
	}

	void ZipFileReader::Flush() {
		// Do nothing
	}

	Bool ZipFileReader::IsOpen() {
		return mFile ? true : false;
	}

	Long ZipFileReader::GetSize() {
		if (!IsOpen())
			return 0;
		struct zip_stat zipStat;
		zip_stat_init(&zipStat);
		zip_stat((zip*)mArchive->GetZipHandle(),
			mName.GetData(), 0, &zipStat);
		return zipStat.size;
	}

	ErrorType ZipFileReader::GetError() {
		// TODO
		return kErrorNone;
	}

	void ZipFileReader::SeekTo(Long seekPosition) {
		if (!IsOpen())
			return;
		if (seekPosition == mSeekPosition)
			return;
		else if (seekPosition < mSeekPosition) {
			Open(mName, mArchive);
			SeekTo(seekPosition);
		} else if (seekPosition > mSeekPosition) {
			Long diff = seekPosition - mSeekPosition;
			Byte *dummyBytes = (Byte*)malloc((size_t)diff);
			Read(dummyBytes, diff);
			free(dummyBytes);
		}
	}

	Long ZipFileReader::GetSeekPosition() {
		return mSeekPosition;
	}

	void ZipFileReader::Read(Byte *data, Long size) {
		if (!IsOpen())
			return;
		mSeekPosition += size;
		zip_fread((zip_file*)mFile, data, size);
	}

	void ZipFileReader::Open(const String &fileName, ZipArchive *archive) {
		Close();
		if (!archive->IsOpen()) {
			// TODO: Set error
			return;	
		}
		mArchive = archive;
		mFile = (Czip_file*)zip_fopen((zip*)mArchive->GetZipHandle(),
			fileName.GetCString(), 0);
		mName = fileName;
	}
}