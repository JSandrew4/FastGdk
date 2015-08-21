/******************************************************************************/
/*                                                                            */
/*  NetworkByteStream.cpp                                                     */
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

#include <Fast/NetworkByteStream.hpp>
#include <Fast/System.hpp>
#include <Fast/ExceptionType.hpp>

#include <cstring>

#include "Undefs.hpp"

#define kFastNumCryptPasses	2

namespace Fast
{
	NetworkByteStream::NetworkByteStream() {
		mIsEndianAware = true;
		Clear();
	}

	NetworkByteStream::NetworkByteStream(const NetworkByteStream &that) {
		mIsEndianAware = true;
		Clear();
		*this = that;
	}

	NetworkByteStream::~NetworkByteStream() { }

	void NetworkByteStream::Encrypt() {
		for (Short j = 1; j <= kFastNumCryptPasses; j++) {
			Int factor = (mData.GetElementCount() % 11);
			for (UShort i = 0; i < mData.GetElementCount(); i++) {
				mData[i] -= factor;
				if (i > 0)
					mData[i] += (mData[i-1] + (factor * 2));
			}
		}
	}

	void NetworkByteStream::Decrypt() {
		for (Short j = 1; j <= kFastNumCryptPasses; j++) {
			Int factor = (mData.GetElementCount() % 11);
			for (Short i = (mData.GetElementCount()-1); i >= 0; i--) {
				if (i > 0)
					mData[i] -= (mData[i-1] + (factor * 2));
				mData[i] += factor;
			}
		}
	}

	NetworkByteStream& NetworkByteStream::operator=(
		const NetworkByteStream &that)
	{
		this->Clear();
		this->mData = that.mData;
		return *this;
	}

	Bool NetworkByteStream::operator==(const NetworkByteStream &that) const {
		if (this->mData.GetElementCount() == that.mData.GetElementCount()) {
			if (0 == memcmp(this->mData.GetData(),
				that.mData.GetData(), this->mData.GetElementCount()))
			{
				return true;
			}
		}
		return false;
	}

	Bool NetworkByteStream::operator!=(const NetworkByteStream &that) const {
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
