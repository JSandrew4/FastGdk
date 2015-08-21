/******************************************************************************/
/*                                                                            */
/*  Vector2D.cpp                                                              */
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

#include <Fast/Vector2D.hpp>
#include <Fast/Vector2DMath.hpp>
#include <Fast/Math.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	Vector2D::Vector2D() {
		mX = mY = 0.0f;
	}

	Vector2D::Vector2D(const Vector2D &that) {
		this->mX = that.mX;
		this->mY = that.mY;
	}

	Vector2D::Vector2D(Float x, Float y) {
		mX = x;
		mY = y;
	}

	Vector2D::Vector2D(Float xy) {
		mX = mY = xy;
	}

	Float Vector2D::GetLength() const {
		return sqrt((mX * mX) + (mY * mY));
	}

	Float Vector2D::GetLengthSquared() const {
		return ((mX * mX) + (mY * mY));
	}

	void Vector2D::Normalize() {
		Float f = sqrt((mX * mX) + (mY * mY));
		if (0.0f == f) {
			*this = kFastVector2DZero;
		} else {
			mX /= f;
			mY /= f;
		}
	}

	void Vector2D::Reflect(const Vector2D &normal) {
		*this -= (normal * Vector2DMath::Dot(*this, normal) * Vector2D(2.0f, 2.0f));
	}
	
	Vector2D& Vector2D::operator=(const Vector2D &that) {
		this->mX = that.mX;
		this->mY = that.mY;
		return *this;
	}

	Vector2D& Vector2D::operator=(const Float that) {
		this->mX = this->mY = that;
		return *this;
	}

	Vector2D& Vector2D::operator+=(const Vector2D &that) {
		this->mX += that.mX;
		this->mY += that.mY;
		return *this;
	}

	Vector2D& Vector2D::operator-=(const Vector2D &that) {
		this->mX -= that.mX;
		this->mY -= that.mY;
		return *this;
	}

	Vector2D& Vector2D::operator*=(const Vector2D &that) {
		this->mX *= that.mX;
		this->mY *= that.mY;
		return *this;
	}

	Vector2D& Vector2D::operator*=(const Float that) {
		this->mX *= that;
		this->mY *= that;
		return *this;
	}

	Vector2D& Vector2D::operator/=(const Vector2D &that) {
		this->mX /= that.mX;
		this->mY /= that.mY;
		return *this;
	}

	Vector2D& Vector2D::operator/=(const Float that) {
		this->mX /= that;
		this->mY /= that;
		return *this;
	}

	Vector2D Vector2D::operator+(const Vector2D &that) {
		return Vector2D(this->mX + that.mX, this->mY + that.mY);
	}

	const Vector2D Vector2D::operator+(const Vector2D &that) const {
		return Vector2D(this->mX + that.mX, this->mY + that.mY);
	}

	Vector2D Vector2D::operator-(const Vector2D &that) {
		return Vector2D(this->mX - that.mX, this->mY - that.mY);
	}

	const Vector2D Vector2D::operator-(const Vector2D &that) const {
		return Vector2D(this->mX - that.mX, this->mY - that.mY);
	}

	Vector2D Vector2D::operator*(const Vector2D &that) {
		return Vector2D(this->mX * that.mX, this->mY * that.mY);
	}

	Vector2D Vector2D::operator*(const Float that) {
		return Vector2D(this->mX * that, this->mY * that);
	}

	const Vector2D Vector2D::operator*(const Vector2D &that) const {
		return Vector2D(this->mX * that.mX, this->mY * that.mY);
	}

	const Vector2D Vector2D::operator*(const Float that) const {
		return Vector2D(this->mX * that, this->mY * that);
	}

	Vector2D Vector2D::operator/(const Vector2D &that) {
		return Vector2D(this->mX / that.mX, this->mY / that.mY);
	}

	Vector2D Vector2D::operator/(const Float that) {
		return Vector2D(this->mX / that, this->mY / that);
	}

	const Vector2D Vector2D::operator/(const Vector2D &that) const {
		return Vector2D(this->mX / that.mX, this->mY / that.mY);
	}

	const Vector2D Vector2D::operator/(const Float that) const {
		return Vector2D(this->mX / that, this->mY / that);
	}

	Bool Vector2D::operator==(const Vector2D &that) const {
		return (this->mX == that.mX && this->mY == that.mY);
	}

	Bool Vector2D::operator==(const Float that) const {
		return (this->mX == that && this->mY == that);
	}

	Bool Vector2D::operator!=(const Vector2D &that) const {
		return (this->mX != that.mX || this->mY != that.mY);
	}

	Bool Vector2D::operator!=(const Float that) const {
		return (this->mX != that || this->mY != that);
	}

	const Vector2D operator-(const Vector2D &that) {
		return Vector2D(-that.mX, -that.mY);
	}

	Bool operator==(const Float f, const Vector2D &v) {
		return (v.mX == f && v.mY == f);
	}

	Bool operator!=(const Float f, const Vector2D &v) {
		return (v.mX != f || v.mY != f);
	}
}
