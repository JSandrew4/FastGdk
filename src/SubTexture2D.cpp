/******************************************************************************/
/*                                                                            */
/*  SubTexture2D.cpp                                                          */
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

#include <Fast/SubTexture2D.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SubTexture2D::SubTexture2D() { }

	SubTexture2D::SubTexture2D(const SubTexture2D &that) {
		*this = that;
	}

	SubTexture2D::SubTexture2D(const String &name, const Rectangle &bounds) {
		mName = name;
		mBounds = bounds;
	}

	SubTexture2D& SubTexture2D::operator=(const SubTexture2D &that) {
		this->mName = that.mName;
		this->mBounds = that.mBounds;
		return *this;
	}

	Bool SubTexture2D::operator==(const SubTexture2D &that) const {
		if (this->mName != that.mName)
			return false;
		if (this->mBounds != that.mBounds)
			return false;
		return true;
	}

	Bool SubTexture2D::operator!=(const SubTexture2D &that) const {
		if (this->mName != that.mName)
			return true;
		if (this->mBounds != that.mBounds)
			return true;
		return false;
	}
}