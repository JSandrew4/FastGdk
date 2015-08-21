/******************************************************************************/
/*                                                                            */
/*  AsciiString.cpp                                                           */
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

#include <Fast/AsciiString.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	AsciiString::AsciiString() {
		mData = 0;
		mSize = 0;
	}

	AsciiString::AsciiString(const AsciiString &that) {
		mData = 0;
		mSize = 0;
		*this = that;
	}

	AsciiString::~AsciiString() {
		delete [] mData;
		mSize = 0;
	}

	AsciiString & AsciiString::operator=(const AsciiString &that) {
		delete [] mData;
		mSize = 0;
		this->mSize = that.mSize;
		this->mData = new Char[this->mSize];
		memcpy(this->mData, that.mData, this->mSize * sizeof(Char));
		return * this;
	}

	Bool AsciiString::operator==(const AsciiString &that) const {
		return memcmp(&this->mData[0], &that.mData[0],
			this->mSize * sizeof(Char)) ? false : true;
	}

	Bool AsciiString::operator!=(const AsciiString &that) const {
		return memcmp(&this->mData[0], &that.mData[0],
			this->mSize * sizeof(Char)) ? true : false;
	}
}
