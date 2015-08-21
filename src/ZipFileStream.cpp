/******************************************************************************/
/*                                                                            */
/*  ZipFileStream.cpp                                                         */
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

#include <Fast/ZipFileStream.hpp>
#include <Fast/ZipArchive.hpp>

#include <zip.h>

#include "Undefs.hpp"

namespace Fast
{
	ZipFileStream::ZipFileStream() {
		mFile = 0;
		mArchive = 0;
		mMadeChange = false;
		Close();
	}

	ZipFileStream::ZipFileStream(const String &fileName,
		ZipArchive *archive, Bool truncate)
	{
		mFile = 0;
		mArchive = 0;
		mMadeChange = false;
		Open(fileName, archive, truncate);
	}

	ZipFileStream::~ZipFileStream() {
		Close();
	}

	void ZipFileStream::Close() {
		if (IsOpen() && mMadeChange) {
			struct zip_source *zipSource = zip_source_buffer(
				(zip*)mArchive->GetZipHandle(), mBuffer.GetData(),
				mBuffer.GetSize(), 1);
			zip_file_add((zip*)mArchive->GetZipHandle(), mName.GetData(),
				zipSource, ZIP_FL_OVERWRITE);
		}
		mFile = 0;
		mArchive = 0;
		mMadeChange = false;
		mName.Clear();
		mBuffer.Clear();
	}

	void ZipFileStream::Flush() {
		// Do nothing
	}

	Bool ZipFileStream::IsOpen() {
		if (mArchive)
			return mArchive->IsOpen();
		return false;
	}

	Long ZipFileStream::GetSize() {
		return mBuffer.GetSize();
	}

	ErrorType ZipFileStream::GetError() {
		// TODO
		return kErrorNone;
	}

	void  ZipFileStream::SeekTo(Long seekPosition) {
		mBuffer.SeekTo(seekPosition);
	}

	Long ZipFileStream::GetSeekPosition() {
		return mBuffer.GetSeekPosition();
	}

	void ZipFileStream::Read(Byte *data, Long size) {
		mBuffer.Read(data, size);
	}

	void ZipFileStream::Write(const Byte *data, Long size) {
		mMadeChange = true;
		mBuffer.Write(data, size);
	}

	void ZipFileStream::Open(const String &fileName,
		ZipArchive *archive, Bool truncate)
	{
		Close();
		if (!archive->IsOpen()) {
			// TODO: Set error
			return;
		}
		struct zip_stat zipStat;
		zip_stat_init(&zipStat);
		Int error = zip_stat((zip*)archive->GetZipHandle(),
			fileName.GetCString(), 0, &zipStat);
		if (error)
			return;
		if (zipStat.size > 0 && !truncate) {
			Byte *data = (Byte*)malloc((size_t)zipStat.size);
			mFile = (Czip_file*)zip_fopen(
				(zip*)archive->GetZipHandle(), fileName.GetCString(), 0);
			zip_fread((zip_file*)mFile, data, zipStat.size);
			mBuffer.Write(data, zipStat.size);
			mBuffer.SeekTo(0);
			zip_fclose((zip_file*)mFile);
			free(data);
		}
		mName = fileName;
		mArchive = archive;
	}
}