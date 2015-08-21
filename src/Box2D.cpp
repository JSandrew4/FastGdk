/******************************************************************************/
/*                                                                            */
/*  Box2D.cpp                                                                 */
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

#include <Fast/Box2D.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Box2D::Box2D() { }

	Box2D::Box2D(const Box2D &that) {
		*this = that;
	}

	Box2D::Box2D(const Vector2D &origin, const Vector2D &size) {
		mOrigin = origin;
		mSize = size;
	}

	Box2D::Box2D(Float originX, Float originY, Float sizeX, Float sizeY) {
		mOrigin = Vector2D(originX, originY);
		mSize = Vector2D(sizeX, sizeY);
	}

	Box2D::~Box2D() { }

	Box2D& Box2D::operator= (const Box2D &that) {
		this->mOrigin = that.mOrigin;
		this->mSize = that.mSize;
		return *this;
	}

	Bool Box2D::operator==(const Box2D &that) const {
		if (this->mOrigin != that.mOrigin)
			return false;
		if (this->mSize != that.mSize)
			return false;
		return true;
	}

	Bool Box2D::operator!=(const Box2D &that) const {
		if (this->mOrigin != that.mOrigin)
			return true;
		if (this->mSize != that.mSize)
			return true;
		return false;
	}
}