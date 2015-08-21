/******************************************************************************/
/*                                                                            */
/*  Checksum.cpp                                                              */
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

#include <Fast/Checksum.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	Checksum::Checksum() {
		Clear();
	}

	Checksum::Checksum(const Checksum &that) {
		*this = that;
	}

	Checksum::Checksum(const Byte *data, Int size) {
		Calculate(data, size);
	}

	void Checksum::Calculate(const Byte *data, Int size) {
		Clear();
		for (Int i = 0; i < size; i++)
			for (Int j = 0; j < kFastChecksumSize && i < size; j++, i++)
				mSum[j] += (i + data[i]);
		mIsEmpty = false;
	}

	void Checksum::Clear() {
		memset(&mSum[0], 0, kFastChecksumSize);
		mIsEmpty = true;
	}

	Bool Checksum::IsEmpty() const {
		return mIsEmpty;
	}

	Checksum& Checksum::operator=(const Checksum &that) {
		memcpy((void*)&this->mSum[0], &that.mSum[0], kFastChecksumSize);
		this->mIsEmpty = that.mIsEmpty;
		return * this;
	}

	Bool Checksum::operator==(const Checksum &that) const {
		return memcmp(&this->mSum[0], &that.mSum[0], kFastChecksumSize)
			? false : true;
	}

	Bool Checksum::operator!=(const Checksum &that) const {
		return memcmp(&this->mSum[0], &that.mSum[0], kFastChecksumSize)
			? true : false;
	}
}
