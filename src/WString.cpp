/******************************************************************************/
/*                                                                            */
/*  WString.cpp                                                               */
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

#include <Fast/WString.hpp>

#include <cstring>
#include <cstdlib>

#include "Undefs.hpp"

namespace Fast
{
	WString::WString() {
		mData = 0;
		mSize = 0;
	}

	WString::WString(const WString &that) {
		mData = 0;
		mSize = 0;
		*this = that;
	}

	WString::~WString() {
		free(mData);
		mSize = 0;
	}

	WString& WString::operator=(const WString &that) {
		free(mData);
		mSize = 0;
		this->mSize = that.mSize;
		this->mData = (WChar*)calloc(this->mSize + 1, sizeof(WChar));
		memcpy(this->mData, that.mData, (this->mSize + 1) * sizeof(WChar));
		return *this;
	}

	Bool WString::operator==(const WString &that) const {
		return memcmp(this->mData, that.mData,
			this->mSize * sizeof(WChar)) ? false : true;
	}

	Bool WString::operator!=(const WString &that) const {
		return memcmp(this->mData, that.mData,
			this->mSize * sizeof(WChar)) ? true : false;
	}
}
