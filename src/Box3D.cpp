/******************************************************************************/
/*                                                                            */
/*  Box3D.cpp                                                                 */
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

#include <Fast/Box3D.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Box3D::Box3D() { }

	Box3D::Box3D(const Box3D &that) {
		*this = that;
	}

	Box3D::Box3D(const Vector3D &origin, const Vector3D &size) {
		mOrigin = origin;
		mSize = size;
	}

	Box3D::Box3D(Float originX, Float originY, Float originZ,
		Float sizeX, Float sizeY, Float sizeZ)
	{
		mOrigin = Vector3D(originX, originY, originZ);
		mSize = Vector3D(sizeX, sizeY, sizeZ);
	}

	Box3D::~Box3D() { }

	Box3D& Box3D::operator= (const Box3D &that) {
		this->mOrigin = that.mOrigin;
		this->mSize = that.mSize;
		return *this;
	}

	Bool Box3D::operator==(const Box3D &that) const {
		if (this->mOrigin != that.mOrigin)
			return false;
		if (this->mSize != that.mSize)
			return false;
		return true;
	}

	Bool Box3D::operator!=(const Box3D &that) const {
		if (this->mOrigin != that.mOrigin)
			return true;
		if (this->mSize != that.mSize)
			return true;
		return false;
	}
}