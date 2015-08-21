/******************************************************************************/
/*                                                                            */
/*  Vector3D.hpp                                                              */
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

#ifndef FastVector3DHppIncluded
#define FastVector3DHppIncluded

#include <Fast/Types.hpp>

#define kFastVector3DZero	Vector3D(0.0f, 0.0f, 0.0f)
#define kFastVector3DUnitX	Vector3D(1.0f, 0.0f, 0.0f)
#define kFastVector3DUnitY	Vector3D(0.0f, 1.0f, 0.0f)
#define kFastVector3DUnitZ	Vector3D(0.0f, 0.0f, 1.0f)
#define kFastVector3DOne	Vector3D(1.0f, 1.0f, 1.0f)

namespace Fast
{
	class Vector2D;

	class FastApi Vector3D
	{
	public:
		// Members
		Float mX;
		Float mY;
		Float mZ;
		// (Con/De)structors
		Vector3D();
		Vector3D(const Vector3D &that);
		Vector3D(Float x, Float y, Float z);
		Vector3D(const Vector2D &xy, Float z);
		Vector3D(Float xyz);
		~Vector3D();
		// Get functions
		Float			GetLength() const;
		Float			GetLengthSquared() const;
		// Modify functions
		void			Normalize();
		void			Reflect(const Vector3D &aNormal);
		// Assignment operators
		Vector3D&		operator= (const Vector3D	&that);
		Vector3D&		operator= (const Float		 that);
		Vector3D&		operator+=(const Vector3D	&that);
		Vector3D&		operator-=(const Vector3D	&that);
		Vector3D&		operator*=(const Vector3D	&that);
		Vector3D&		operator*=(const Float		 that);
		Vector3D&		operator/=(const Vector3D	&that);
		Vector3D&		operator/=(const Float		 that);
		// Add operators
		Vector3D		operator+ (const Vector3D	&that);
		const Vector3D	operator+ (const Vector3D	&that) const;
		// Subtract operators
		Vector3D		operator- (const Vector3D	&that);
		const Vector3D	operator- (const Vector3D	&that) const;
		// Product operators
		Vector3D		operator* (const Vector3D	&that);
		Vector3D		operator* (const Float		 that);
		const Vector3D	operator* (const Vector3D	&that) const;
		const Vector3D	operator* (const Float		 that) const;
		// Division operators
		Vector3D		operator/ (const Vector3D	&that);
		Vector3D		operator/ (const Float		 that);
		const Vector3D	operator/ (const Vector3D	&that) const;
		const Vector3D	operator/ (const Float		 that) const;
		// Comparison operators
		Bool			operator==(const Vector3D	&that) const;
		Bool			operator==(const Float		 that) const;
		Bool			operator!=(const Vector3D	&that) const;
		Bool			operator!=(const Float		 that) const;
		// Other operators
		friend const Vector3D	operator-(const Vector3D &that);
	};
	
	FastApi Bool	operator==(const Float f, const Vector3D &v);
	FastApi Bool	operator!=(const Float f, const Vector3D &v);
}

#endif // FastVector3DHppIncluded
