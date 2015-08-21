/******************************************************************************/
/*                                                                            */
/*  Vector2D.hpp                                                              */
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

#ifndef FastVector2DHppIncluded
#define FastVector2DHppIncluded

#include <Fast/Types.hpp>

#define kFastVector2DZero	Vector2D(0.0f, 0.0f)
#define kFastVector2DUnitX	Vector2D(1.0f, 0.0f)
#define kFastVector2DUnitY	Vector2D(0.0f, 1.0f)
#define kFastVector2DOne	Vector2D(1.0f, 1.0f)

namespace Fast
{
	class Matrix;
	class Quaternion;

	class FastApi Vector2D
	{
	public:
		// Members
		Float mX;
		Float mY;
		// (Con/De)structors
		Vector2D();
		Vector2D(const Vector2D &that);
		Vector2D(Float x, Float y);
		Vector2D(Float xy);
		// Get functions
		Float			GetLength() const;
		Float			GetLengthSquared() const;
		// Modify functions
		void			Normalize();
		void			Reflect(const Vector2D &normal);
		// Assignment operators
		Vector2D&		operator= (const Vector2D	&that);
		Vector2D&		operator= (const Float		 that);
		Vector2D&		operator+=(const Vector2D	&that);
		Vector2D&		operator-=(const Vector2D	&that);
		Vector2D&		operator*=(const Vector2D	&that);
		Vector2D&		operator*=(const Float		 that);
		Vector2D&		operator/=(const Vector2D	&that);
		Vector2D&		operator/=(const Float		 that);
		// Add operators
		Vector2D		operator+ (const Vector2D	&that);
		const Vector2D	operator+ (const Vector2D	&that) const;
		// Subtract operators
		Vector2D		operator- (const Vector2D	&that);
		const Vector2D	operator- (const Vector2D	&that) const;
		// Product operators
		Vector2D		operator* (const Vector2D	&that);
		Vector2D		operator* (const Float		 that);
		const Vector2D	operator* (const Vector2D	&that) const;
		const Vector2D	operator* (const Float		 that)  const;
		// Division operators
		Vector2D		operator/ (const Vector2D	&that);
		Vector2D		operator/ (const Float		 that);
		const Vector2D	operator/ (const Vector2D	&that) const;
		const Vector2D	operator/ (const Float		 that)  const;
		// Comparison operators
		Bool			operator==(const Vector2D	&that) const;
		Bool			operator==(const Float		 that) const;
		Bool			operator!=(const Vector2D	&that) const;
		Bool			operator!=(const Float		 that) const;
		// Other operators
		friend const Vector2D	operator-(const Vector2D &that);
	};

	FastApi Bool	operator==(const Float f, const Vector2D &v);
	FastApi Bool	operator!=(const Float f, const Vector2D &v);
}

#endif // FastVector2DHppIncluded
