/******************************************************************************/
/*                                                                            */
/*  Rectangle.cpp                                                             */
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

#include <Fast/Rectangle.hpp>
#include <Fast/Point.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Rectangle::Rectangle() {
		mX = mY = mWidth = mHeight = 0;
	}

	Rectangle::Rectangle(Int x, Int y, Int width, Int height) {
		mX = x;
		mY = y;
		mWidth = width;
		mHeight = height;
	}

	Rectangle::Rectangle(const Rectangle &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		this->mWidth = that.mWidth;
		this->mHeight = that.mHeight;
	}

	Bool Rectangle::Encloses(const Point &point) const {
		return (point.mX >= mX && point.mX < (mX + mWidth) &&
			point.mY >= mY && point.mY < (mY + mHeight));
	}

	Rectangle& Rectangle::operator=(const Rectangle &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		this->mWidth = that.mWidth;
		this->mHeight = that.mHeight;
		return * this;
	}

	Bool Rectangle::operator==(const Rectangle &that) const {
		return (this->mX == that.mX && this->mY == that.mY &&
			this->mWidth == that.mWidth && this->mHeight == that.mHeight);
	}

	Bool Rectangle::operator!=(const Rectangle &that) const {
		return (this->mX != that.mX || this->mY != that.mY ||
			this->mWidth != that.mWidth || this->mHeight != that.mHeight);
	}
}
