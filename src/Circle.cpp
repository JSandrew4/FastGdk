/******************************************************************************/
/*                                                                            */
/*  Circle.cpp                                                                */
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

#include <Fast/Circle.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Circle::Circle() {
		mRadius = 0.0f;
	}

	Circle::Circle(const Circle &that) {
		*this = that;
	}

	Circle::Circle(const Vector2D &origin, Float radius) {
		mOrigin = origin;
		mRadius = radius;
	}

	Circle& Circle::operator=(const Circle &that) {
		this->mOrigin = that.mOrigin;
		this->mRadius = that.mRadius;
		return *this;
	}

	Bool Circle::operator==(const Circle &that) const {
		if (this->mOrigin != that.mOrigin)
			return false;
		if (this->mRadius != that.mRadius)
			return false;
		return true;
	}

	Bool Circle::operator!=(const Circle &that) const {
		if (this->mOrigin != that.mOrigin)
			return true;
		if (this->mRadius != that.mRadius)
			return true;
		return false;
	}
}