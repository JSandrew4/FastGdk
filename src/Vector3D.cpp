/******************************************************************************/
/*                                                                            */
/*  Vector3D.cpp                                                              */
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

#include <Fast/Vector3D.hpp>
#include <Fast/Vector3DMath.hpp>
#include <Fast/Math.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Vector2D.hpp>

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	Vector3D::Vector3D() {
		mX = mY = mZ = 0.0f;
	}

	Vector3D::Vector3D(const Vector3D &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		this->mZ = that.mZ;
	}

	Vector3D::Vector3D(Float x, Float y, Float z) {
		mX = x;
		mY = y;
		mZ = z;
	}

	Vector3D::Vector3D(const Vector2D &xy, Float z) {
		mX = xy.mX;
		mY = xy.mY;
		mZ = z;
	}

	Vector3D::Vector3D(Float xyz) {
		mZ = mY = mX = xyz;
	}

	Vector3D::~Vector3D() { }

	Float Vector3D::GetLength() const {
		return sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
	}

	Float Vector3D::GetLengthSquared() const {
		return ((mX * mX) + (mY * mY) + (mZ * mZ));
	}

	void Vector3D::Normalize() {
		Float f = sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
		if (0.0f == f) {
			*this = kFastVector3DZero;
		} else {
			mX /= f;
			mY /= f;
			mZ /= f;
		}
	}

	void Vector3D::Reflect(const Vector3D &normal) {
		*this -= (normal * Vector3DMath::Dot(*this, normal) *
			Vector3D(2.0f, 2.0f, 2.0f));
	}
	
	Vector3D& Vector3D::operator=(const Vector3D &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		this->mZ = that.mZ;
		return *this;
	}

	Vector3D& Vector3D::operator=(const Float that) {
		this->mX = this->mY = this->mZ = that;
		return *this;
	}

	Vector3D& Vector3D::operator+=(const Vector3D &that) {
		this->mX += that.mX;
		this->mY += that.mY;
		this->mZ += that.mZ;
		return *this;
	}

	Vector3D& Vector3D::operator-=(const Vector3D &that) {
		this->mX -= that.mX;
		this->mY -= that.mY;
		this->mZ -= that.mZ;
		return *this;
	}

	Vector3D& Vector3D::operator*=(const Vector3D &that) {
		this->mX *= that.mX;
		this->mY *= that.mY;
		this->mZ *= that.mZ;
		return *this;
	}

	Vector3D& Vector3D::operator*=(const Float that) {
		this->mX *= that;
		this->mY *= that;
		this->mZ *= that;
		return *this;
	}

	Vector3D& Vector3D::operator/=(const Vector3D &that) {
		this->mX /= that.mX;
		this->mY /= that.mY;
		this->mZ /= that.mZ;
		return *this;
	}

	Vector3D& Vector3D::operator/=(const Float that) {
		this->mX /= that;
		this->mY /= that;
		this->mZ /= that;
		return *this;
	}

	Vector3D Vector3D::operator+(const Vector3D &that) {
		return Vector3D(this->mX + that.mX,
			this->mY + that.mY, this->mZ + that.mZ);
	}

	const Vector3D Vector3D::operator+(const Vector3D &that) const {
		return Vector3D(this->mX + that.mX,
			this->mY + that.mY, this->mZ + that.mZ);
	}

	Vector3D Vector3D::operator-(const Vector3D &that) {
		return Vector3D(this->mX - that.mX,
			this->mY - that.mY, this->mZ - that.mZ);
	}

	const Vector3D Vector3D::operator-(const Vector3D &that) const {
		return Vector3D(this->mX - that.mX,
			this->mY - that.mY, this->mZ - that.mZ);
	}

	Vector3D Vector3D::operator*(const Vector3D &that) {
		return Vector3D(this->mX * that.mX,
			this->mY * that.mY, this->mZ * that.mZ);
	}

	Vector3D Vector3D::operator*(const Float that) {
		return Vector3D(this->mX * that,
			this->mY * that, this->mZ * that);
	}

	const Vector3D Vector3D::operator*(const Vector3D &that) const {
		return Vector3D(this->mX * that.mX,
			this->mY * that.mY, this->mZ * that.mZ);
	}

	const Vector3D Vector3D::operator*(const Float that) const {
		return Vector3D(this->mX * that,
			this->mY * that, this->mZ * that);
	}

	Vector3D Vector3D::operator/(const Vector3D &that) {
		return Vector3D(this->mX / that.mX,
			this->mY / that.mY, this->mZ / that.mZ);
	}

	Vector3D Vector3D::operator/(const Float that) {
		return Vector3D(this->mX / that,
			this->mY / that, this->mZ / that);
	}

	const Vector3D Vector3D::operator/(const Vector3D &that) const {
		return Vector3D(this->mX / that.mX,
			this->mY / that.mY, this->mZ / that.mZ);
	}

	const Vector3D Vector3D::operator/(const Float that) const {
		return Vector3D(this->mX / that,
			this->mY / that, this->mZ / that);
	}

	Bool Vector3D::operator==(const Vector3D &that) const {
		return (this->mX == that.mX &&
			this->mY == that.mY && this->mZ == that.mZ);
	}

	Bool Vector3D::operator==(const Float that) const {
		return (this->mX == that && this->mY == that && this->mZ == that);
	}

	Bool Vector3D::operator!=(const Vector3D &that) const {
		return (this->mX != that.mX ||
			this->mY != that.mY || this->mZ != that.mZ);
	}

	Bool Vector3D::operator!=(const Float that) const {
		return (this->mX != that || this->mY != that || this->mZ != that);
	}

	const Vector3D operator-(const Vector3D &that) {
		return Vector3D(-that.mX, -that.mY, -that.mZ);
	}

	Bool operator==(const Float f, const Vector3D &v) {
		return (v.mX == f && v.mY == f && v.mZ == f);
	}

	Bool operator!=(const Float f, const Vector3D &v) {
		return (v.mX != f || v.mY != f || v.mZ != f);
	}
}