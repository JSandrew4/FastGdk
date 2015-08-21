/******************************************************************************/
/*                                                                            */
/*  Quaternion.cpp                                                            */
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

#include <Fast/Quaternion.hpp>
#include <Fast/Vector3D.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Quaternion::Quaternion() {
		mX = mY = mZ = mW = 0.0f;
	}

	Quaternion::Quaternion(const Quaternion &that) {
		*this = that;
	}
	
	Quaternion::Quaternion(Float x, Float y, Float z, Float w) {
		mX = x;
		mY = y;
		mZ = z;
		mW = w;
	}
	
	Quaternion::Quaternion(Float angle, const Vector3D &axis) {
		mW = angle;
		mX = axis.mX;
		mY = axis.mY;
		mZ = axis.mZ;
	}
	
	Quaternion::~Quaternion() { }
	
	void Quaternion::Reset() {

	}
	
	void Quaternion::SetAxis() {

	}

	Quaternion& Quaternion::operator=(const Quaternion &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		this->mZ = that.mZ;
		this->mW = that.mW;
		return *this;
	}

	Bool Quaternion::operator==(const Quaternion &that) const {
		if (this->mX != that.mX)
			return false;
		if (this->mY != that.mY)
			return false;
		if (this->mZ != that.mZ)
			return false;
		if (this->mW != that.mW)
			return false;
		return true;
	}

	Bool Quaternion::operator!=(const Quaternion &that) const {
		if (this->mX != that.mX)
			return true;
		if (this->mY != that.mY)
			return true;
		if (this->mZ != that.mZ)
			return true;
		if (this->mW != that.mW)
			return true;
		return false;
	}
}
