/******************************************************************************/
/*                                                                            */
/*  ByteStream.cpp                                                            */
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

#include <Fast/ByteStream.hpp>
#include <Fast/String.hpp>
#include <Fast/Error.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	ByteStream::ByteStream() {
		mIsEndianAware = false;
		Clear();
	}

	ByteStream::ByteStream(const ByteStream &that) {
		mIsEndianAware = false;
		Clear();
		*this = that;
	}

	ByteStream::~ByteStream() { }

	void ByteStream::Read(Byte *data, Long size) {
		if (mData.GetElementCount() >= (Int)(mSeekPosition + size)) {
			memcpy(&data[0], &mData[(Int)mSeekPosition], (size_t)size);
			mSeekPosition += size;
		} else mError = kErrorEndOfStream;
	}

	void ByteStream::Write(const Byte *data, Long size) {
		if ((Int)(mSeekPosition+size) > mData.GetElementCount())
			mData.SetElementCount((Int)(mSeekPosition+size));
		memcpy(&mData[(UInt)mSeekPosition], &data[0], (size_t)size);
		mSeekPosition += size;
	}

	Long ByteStream::GetSeekPosition() {
		return mSeekPosition;
	}

	void ByteStream::SeekTo(Long seekPosition) {
		mSeekPosition = seekPosition;
	}

	void ByteStream::Close() {
		mSeekPosition = 0;
		mError = kErrorNone;
	}

	void ByteStream::Flush() {
		// Do nothing
	}

	Bool ByteStream::IsOpen() {
		// Always open
		return true;
	}

	void ByteStream::Clear() {
		Close();
		mData.Clear();
	}

	Long ByteStream::GetSize() {
		return mData.GetElementCount();
	}

	Long ByteStream::GetSize() const {
		return mData.GetElementCount();
	}

	ErrorType ByteStream::GetError() {
		return kErrorNone;
	}

	Byte* ByteStream::GetData() {
		return &mData[0];
	}

	const Byte* ByteStream::GetData() const {
		return &mData[0];
	}

	void ByteStream::SetName(const String &name) {
		mName = name;
	}

	ByteStream& ByteStream::operator=(const ByteStream &that) {
		this->Clear();
		this->mData = that.mData;
		return *this;
	}

	Bool ByteStream::operator==(const ByteStream &that) const {
		if (this->mData.GetElementCount() == that.mData.GetElementCount()) {
			if (0 == memcmp(this->mData.GetData(),
				that.mData.GetData(), this->mData.GetElementCount()))
			{
				return true;
			}
		}
		return false;
	}

	Bool ByteStream::operator!=(const ByteStream &that) const {
		if (this->mData.GetElementCount() != that.mData.GetElementCount())
			return true;
		if (0 != memcmp(this->mData.GetData(),
			that.mData.GetData(), this->mData.GetElementCount()))
		{
			return true;
		}
		return false;
	}
}
