/******************************************************************************/
/*                                                                            */
/*  Vector4D.hpp                                                              */
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

#ifndef FastVector4DHppIncluded
#define FastVector4DHppIncluded

#include <Fast/Types.hpp>

#define kFastVector4DZero	Vector4D(0.0f, 0.0f, 0.0f, 0.0f)
#define kFastVector4DUnitX	Vector4D(1.0f, 0.0f, 0.0f, 0.0f)
#define kFastVector4DUnitY	Vector4D(0.0f, 1.0f, 0.0f, 0.0f)
#define kFastVector4DUnitZ	Vector4D(0.0f, 0.0f, 1.0f, 0.0f)
#define kFastVector4DUnitW	Vector4D(0.0f, 0.0f, 0.0f, 1.0f)
#define kFastVector4DOne	Vector4D(1.0f, 1.0f, 1.0f, 1.0f)

namespace Fast
{
	class Matrix;
	class Quaternion;
	class Vector2D;
	class Vector3D;

	class FastApi Vector4D
	{
	public:
		// Members
		Float mX;
		Float mY;
		Float mZ;
		Float mW;
		// (Con/De)structors
		Vector4D();
		Vector4D(const Vector4D &that);
		Vector4D(Float x, Float y, Float z, Float w);
		Vector4D(const Vector3D &xyz, Float w);
		Vector4D(const Vector2D &xy, const Vector2D &zw);
		Vector4D(Float xyzw);
		// Get functions
		Float			GetLength() const;
		Float			GetLengthSquared() const;
		// Modify functions
		void			Normalize();
		void			Reflect(const Vector4D &normal);
		// Assignment operators
		Vector4D&		operator= (const Vector4D	&that);
		Vector4D&		operator= (const Float		 that);
		Vector4D&		operator+=(const Vector4D	&that);
		Vector4D&		operator-=(const Vector4D	&that);
		Vector4D&		operator*=(const Vector4D	&that);
		Vector4D&		operator*=(const Float		 that);
		Vector4D&		operator/=(const Vector4D	&that);
		Vector4D&		operator/=(const Float		 that);
		// Add operators
		Vector4D		operator+ (const Vector4D	&that);
		const Vector4D	operator+ (const Vector4D	&that) const;
		// Subtract operators
		Vector4D		operator- (const Vector4D	&that);
		const Vector4D	operator- (const Vector4D	&that) const;
		// Product operators
		Vector4D		operator* (const Vector4D	&that);
		Vector4D		operator* (const Float		 that);
		const Vector4D	operator* (const Vector4D	&that) const;
		const Vector4D	operator* (const Float		 that)  const;
		// Division operators
		Vector4D		operator/ (const Vector4D	&that);
		Vector4D		operator/ (const Float		 that);
		const Vector4D	operator/ (const Vector4D	&that) const;
		const Vector4D	operator/ (const Float		 that)  const;
		// Comparison operators
		Bool			operator==(const Vector4D	&that) const;
		Bool			operator==(const Float		 that) const;
		Bool			operator!=(const Vector4D	&that) const;
		Bool			operator!=(const Float		 that) const;
		// Other operators
		friend const Vector4D	operator-(const Vector4D &that);
	};

	FastApi Bool	operator==(const Float f, const Vector4D &v);
	FastApi Bool	operator!=(const Float f, const Vector4D &v);
}

#endif // FastVector4DHppIncluded
