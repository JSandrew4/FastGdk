/******************************************************************************/
/*                                                                            */
/*  Point.cpp                                                                 */
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

#include <Fast/Point.hpp>
#include <Fast/Rectangle.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Point::Point() {
		mX = mY = 0;
	}

	Point::Point(Int x, Int y) {
		mX = x;
		mY = y;
	}

	Point::Point(const Point &that) {
		this->mX = that.mX;
		this->mY = that.mY;
	}

	Bool Point::IsInside(const Rectangle &rect) const {
		return (mX >= rect.mX && mX < (rect.mX + rect.mWidth) &&
			mY >= rect.mY && mY < (rect.mY + rect.mHeight));
	}

	Point & Point::operator=(const Point &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		return * this;
	}

	Bool Point::operator==(const Point &that) const {
		return (this->mX == that.mX && this->mY == that.mY);
	}

	Bool Point::operator!=(const Point &that) const {
		return (this->mX != that.mX || this->mY != that.mY);
	}
}
