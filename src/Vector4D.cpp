/******************************************************************************/
/*                                                                            */
/*  Vector4D.cpp                                                              */
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

#include <Fast/Vector4D.hpp>
#include <Fast/Vector4DMath.hpp>
#include <Fast/Math.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	Vector4D::Vector4D() {
		mX = mY = mZ = mW = 0.0f;
	}

	Vector4D::Vector4D(const Vector4D &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		this->mZ = that.mZ;
		this->mW = that.mW;
	}

	Vector4D::Vector4D(Float x, Float y, Float z, Float w) {
		mX = x;
		mY = y;
		mZ = z;
		mW = w;
	}

	Vector4D::Vector4D(const Vector3D &xyz, Float w) {
		mX = xyz.mX;
		mY = xyz.mY;
		mZ = xyz.mZ;
		mW = w;
	}

	Vector4D::Vector4D(const Vector2D &xy, const Vector2D &zw) {
		mX = xy.mX;
		mY = xy.mY;
		mZ = zw.mX;
		mW = zw.mY;
	}

	Vector4D::Vector4D(Float xyzw) {
		mX = xyzw;
		mY = xyzw;
		mZ = xyzw;
		mW = xyzw;
	}

	Float Vector4D::GetLength() const {
		return sqrt((mX * mX) + (mY * mY) + (mZ * mZ) + (mW * mW));
	}

	Float Vector4D::GetLengthSquared() const {
		return ((mX * mX) + (mY * mY) + (mZ * mZ) + (mW * mW));
	}

	void Vector4D::Normalize() {
		Float f = sqrt((mX * mX) + (mY * mY) + (mZ * mZ) + (mW * mW));
		if (0.0f == f) {
			*this = kFastVector4DZero;
		} else {
			mX /= f;
			mY /= f;
			mZ /= f;
			mW /= f;
		}
	}

	void Vector4D::Reflect(const Vector4D &normal) {
		*this -= (normal * Vector4DMath::Dot(*this, normal) *
			Vector4D(2.0f, 2.0f, 2.0f, 2.0f));
	}
	
	Vector4D& Vector4D::operator=(const Vector4D &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		this->mZ = that.mZ;
		this->mW = that.mW;
		return *this;
	}

	Vector4D& Vector4D::operator=(const Float that) {
		this->mX = this->mY = this->mZ = this->mW = that;
		return *this;
	}

	Vector4D& Vector4D::operator+=(const Vector4D &that) {
		this->mX += that.mX;
		this->mY += that.mY;
		this->mZ += that.mZ;
		this->mW += that.mW;
		return *this;
	}

	Vector4D& Vector4D::operator-=(const Vector4D &that) {
		this->mX -= that.mX;
		this->mY -= that.mY;
		this->mZ -= that.mZ;
		this->mW -= that.mW;
		return *this;
	}

	Vector4D& Vector4D::operator*=(const Vector4D &that) {
		this->mX *= that.mX;
		this->mY *= that.mY;
		this->mZ *= that.mZ;
		this->mW *= that.mW;
		return *this;
	}

	Vector4D& Vector4D::operator*=(const Float that) {
		this->mX *= that;
		this->mY *= that;
		this->mZ *= that;
		this->mW *= that;
		return *this;
	}

	Vector4D& Vector4D::operator/=(const Vector4D &that) {
		this->mX /= that.mX;
		this->mY /= that.mY;
		this->mZ /= that.mZ;
		this->mW /= that.mW;
		return *this;
	}

	Vector4D& Vector4D::operator/=(const Float that) {
		this->mX /= that;
		this->mY /= that;
		this->mZ /= that;
		this->mW /= that;
		return *this;
	}

	Vector4D Vector4D::operator+(const Vector4D &that) {
		return Vector4D(this->mX + that.mX, this->mY + that.mY,
			this->mZ + that.mZ, this->mW + that.mW);
	}

	const Vector4D Vector4D::operator+(const Vector4D &that) const {
		return Vector4D(this->mX + that.mX, this->mY + that.mY,
			this->mZ + that.mZ, this->mW + that.mW);
	}

	Vector4D Vector4D::operator-(const Vector4D &that) {
		return Vector4D(this->mX - that.mX, this->mY - that.mY,
			this->mZ - that.mZ, this->mW - that.mW);
	}

	const Vector4D Vector4D::operator-(const Vector4D &that) const {
		return Vector4D(this->mX - that.mX, this->mY - that.mY,
			this->mZ - that.mZ, this->mW - that.mW);
	}

	Vector4D Vector4D::operator*(const Vector4D &that) {
		return Vector4D(this->mX * that.mX, this->mY * that.mY,
			this->mZ * that.mZ, this->mW * that.mW);
	}

	Vector4D Vector4D::operator*(const Float that) {
		return Vector4D(this->mX * that, this->mY * that,
			this->mZ * that, this->mW * that);
	}

	const Vector4D Vector4D::operator*(const Vector4D &that) const {
		return Vector4D(this->mX * that.mX, this->mY * that.mY,
			this->mZ * that.mZ, this->mW * that.mW);
	}

	const Vector4D Vector4D::operator*(const Float that) const {
		return Vector4D(this->mX * that, this->mY * that,
			this->mZ * that, this->mW * that);
	}

	Vector4D Vector4D::operator/(const Vector4D &that) {
		return Vector4D(this->mX / that.mX, this->mY / that.mY,
			this->mZ / that.mZ, this->mW / that.mW);
	}

	Vector4D Vector4D::operator/(const Float that) {
		return Vector4D(this->mX / that, this->mY / that,
			this->mZ / that, this->mW / that);
	}

	const Vector4D Vector4D::operator/(const Vector4D &that) const {
		return Vector4D(this->mX / that.mX, this->mY / that.mY,
			this->mZ / that.mZ, this->mW / that.mW);
	}

	const Vector4D Vector4D::operator/(const Float that) const {
		return Vector4D(this->mX / that, this->mY / that,
			this->mZ / that, this->mW / that);
	}

	Bool Vector4D::operator==(const Vector4D &that) const {
		return (this->mX == that.mX && this->mY == that.mY &&
			this->mZ == that.mZ && this->mW == that.mW);
	}

	Bool Vector4D::operator==(const Float that) const {
		return (this->mX == that && this->mY == that &&
			this->mZ == that && this->mW == that);
	}

	Bool Vector4D::operator!=(const Vector4D &that) const {
		return (this->mX != that.mX || this->mY != that.mY ||
			this->mZ != that.mZ || this->mW != that.mW);
	}

	Bool Vector4D::operator!=(const Float that) const {
		return (this->mX != that || this->mY != that ||
			this->mZ != that || this->mW != that);
	}

	const Vector4D operator-(const Vector4D &that) {
		return Vector4D(-that.mX, -that.mY, -that.mZ, that.mW);
	}

	Bool operator==(const Float f, const Vector4D &v) {
		return (v.mX == f && v.mY == f && v.mZ == f && v.mW == f);
	}

	Bool operator!=(const Float f, const Vector4D &v) {
		return (v.mX != f || v.mY != f || v.mZ != f || v.mW != f);
	}
}
