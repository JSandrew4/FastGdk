/******************************************************************************/
/*                                                                            */
/*  Version.cpp                                                               */
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

#include <Fast/Version.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Version::Version() {
		mMajor = mMinor = 0;
	}

	Version::Version(Int major, Int minor) {
		mMajor = major;
		mMinor = minor;
	}

	Version::Version(const Version &that) {
		this->mMajor = that.mMajor;
		this->mMinor = that.mMinor;
	}

	Version& Version::operator=(const Version &that) {
		this->mMajor = that.mMajor;
		this->mMinor = that.mMinor;
		return * this;
	}

	Bool Version::operator==(const Version &that) const {
		return (this->mMajor == that.mMajor && this->mMinor == that.mMinor);
	}

	Bool Version::operator!=(const Version &that) const {
		return (this->mMajor != that.mMajor || this->mMinor != that.mMinor);
	}
}
