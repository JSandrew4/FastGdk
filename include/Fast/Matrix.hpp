/******************************************************************************/
/*                                                                            */
/*  Matrix.hpp                                                                */
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

#ifndef FastMatrixHppIncluded
#define FastMatrixHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Quaternion.hpp>

#define kFastMatrixIdentity Matrix(	\
		1.0f, 0.0f, 0.0f, 0.0f,			\
		0.0f, 1.0f, 0.0f, 0.0f,			\
		0.0f, 0.0f, 1.0f, 0.0f,			\
		0.0f, 0.0f, 0.0f, 1.0f			\
	)
#define kFastMatrixZero Matrix(		\
		0.0f, 0.0f, 0.0f, 0.0f,			\
		0.0f, 0.0f, 0.0f, 0.0f,			\
		0.0f, 0.0f, 0.0f, 0.0f,			\
		0.0f, 0.0f, 0.0f, 0.0f			\
	)
#define kFastMatrixUnit Matrix(		\
		1.0f, 1.0f, 1.0f, 1.0f,			\
		1.0f, 1.0f, 1.0f, 1.0f,			\
		1.0f, 1.0f, 1.0f, 1.0f,			\
		1.0f, 1.0f, 1.0f, 1.0f			\
	)

namespace Fast
{
	class Box2D;

	class FastApi Matrix
	{
	public:
		// Members
		Float	mElements[16];
		// (Con/De)structors
		Matrix();
		Matrix(const Matrix &that);
		Matrix(
			Float m11, Float m12, Float m13, Float m14,
			Float m21, Float m22, Float m23, Float m24,
			Float m31, Float m32, Float m33, Float m34,
			Float m41, Float m42, Float m43, Float m44);
		Matrix(const Float *m);
		~Matrix();
		// Get functions
		Float		GetElement(Int x, Int y) const;
		Float		GetDeterminant() const;
		Vector3D	GetTranslation() const;
		Vector3D	GetScale() const;
		Quaternion	GetRotation() const;
		// Modify functions
		void	SetElement(Int x, Int y, Float element);
		void	Transpose();
		void	Invert();
		void	Transform(const Quaternion &rotation);
		// Static functions
		static Matrix	CreateBillboard(const Vector3D &objectPosition,
							const Vector3D &camPosition, const Vector3D &camUp,
							const Vector3D &camForward);
		static void		CreateBillboard(const Vector3D &objectPosition,
							const Vector3D &camPosition, const Vector3D &camUp,
							const Vector3D &camForward, Matrix *result);
		static Matrix	CreateConstrainedBillboard(
							const Vector3D &objectPosition,
							const Vector3D &camPosition,
							const Vector3D &rotateAxis,
							const Vector3D &camForward,
							const Vector3D &objectForward);
		static void		CreateConstrainedBillboard(
							const Vector3D &objectPosition,
							const Vector3D &camPosition,
							const Vector3D &rotateAxis,
							const Vector3D &camForward,
							const Vector3D &objectForward, Matrix *result);
		static Matrix	CreateFromPitchYawRoll(const Vector3D &pitchYawRoll);
		static void		CreateFromPitchYawRoll(const Vector3D &pitchYawRoll,
							Matrix *result);
		static Matrix	CreateLookAt(const Vector3D &camPosition,
							const Vector3D &camTarget, const Vector3D &camUp);
		static void		CreateLookAt(const Vector3D &camPosition,
							const Vector3D &camTarget,
							const Vector3D &camUp, Matrix *result);
		static Matrix	CreateOrthographic(Float width, Float height,
							Float znear, Float zfar);
		static void		CreateOrthographic(Float width, Float height,
							Float znear, Float zfar, Matrix *result);
		static Matrix	CreateOrthographicOffCenter(const Box2D &box2D,
							Float nearPlane, Float farPlane);
		static void		CreateOrthographicOffCenter(const Box2D &box2D,
							Float nearPlane, Float farPlane, Matrix *result);
		static Matrix	CreateReflection(const Vector3D &normal,
							Float distance);
		static void		CreateReflection(const Vector3D &normal,
							Float distance, Matrix *result);
		static Matrix	CreateShadow(const Vector3D &lightDirection,
							const Vector3D &normal, Float distance);
		static void		CreateShadow(const Vector3D &lightDirection,
							const Vector3D &normal, Float distance,
							Matrix *result);
		static Matrix	CreateWorld(const Vector3D &position,
							const Vector3D &forward, const Vector3D &up);
		static void		CreateWorld(const Vector3D &position,
							const Vector3D &forward, const Vector3D &up,
							Matrix *result);
		static Matrix	CreateLerp(const Matrix &a, const Matrix &b, Float t);
		static void		CreateLerp(const Matrix &a, const Matrix &b, Float t,
							Matrix *result);
		static Matrix	CreateTransform(const Matrix &matrix,
							const Quaternion &rotation);
		static void		CreateTransform(const Matrix &matrix,
							const Quaternion &rotation,
							Matrix *result);
		static Matrix	CreateTranspose(const Matrix &m);
		static void		CreateTranspose(const Matrix &m, Matrix *result);
		static Matrix	CreateFrustumOffCenter(const Box2D &box2D,
							Float znear, Float zfar);
		static void		CreateFrustumOffCenter(const Box2D &box2D, Float znear,
							Float zfar, Matrix *result);
		static Matrix	CreateFrustum(Float width, Float height,
							Float znear, Float zfar);
		static void		CreateFrustum(Float width, Float height, Float znear,
							Float zfar, Matrix *result);
		static Matrix	CreatePerspective(Float yfovDegrees, Float aspect,
							Float nearDistance, Float farDistance);
		static void		CreatePerspective(Float yfovDegrees, Float aspect,
							Float nearDistance, Float farDistance,
							Matrix *result);
		static Matrix	CreateFromQuaternion(const Quaternion &q);
		static void		CreateFromQuaternion(const Quaternion &q,
							Matrix *result);
		static Matrix	CreateTranslation(const Vector3D &position);
		static void		CreateTranslation(const Vector3D &position,
							Matrix *result);
		static Matrix	CreateScale(const Vector3D &scales);
		static void		CreateScale(const Vector3D &scales, Matrix *result);
		static Matrix	CreateScale(Float scale);
		static void		CreateScale(Float scale, Matrix *result);
		static Matrix	CreateRotationX(Float radians);
		static void		CreateRotationX(Float radians, Matrix *result);
		static Matrix	CreateRotationY(Float radians);
		static void		CreateRotationY(Float radians, Matrix *result);
		static Matrix	CreateRotationZ(Float radians);
		static void		CreateRotationZ(Float radians, Matrix *result);
		static Matrix	CreateFromAxisAngle(const Vector3D &axis,
							Float radians);
		static void		CreateFromAxisAngle(const Vector3D &axis,
							Float radians, Matrix *result);
		// Operators (Matrix)
		Matrix&			operator= (const Matrix		&that);
		Matrix&			operator*=(const Matrix		&that);
		Matrix&			operator+=(const Matrix		&that);
		Matrix&			operator-=(const Matrix		&that);
		Matrix			operator* (const Matrix		&that);
		const Matrix	operator* (const Matrix		&that) const;
		Matrix			operator+ (const Matrix		&that);
		const Matrix	operator+ (const Matrix		&that) const;
		Matrix			operator- (const Matrix		&that);
		const Matrix	operator- (const Matrix		&that) const;
		Bool			operator==(const Matrix		&that) const;
		Bool			operator!=(const Matrix		&that) const;
		// Operators (Float[])
		Matrix&			operator= (const Float		*that);
		Matrix&			operator*=(const Float		*that);
		Matrix&			operator+=(const Float		*that);
		Matrix&			operator-=(const Float		*that);
		Matrix			operator* (const Float		*that);
		const Matrix	operator* (const Float		*that) const;
		Matrix			operator+ (const Float		*that);
		const Matrix	operator+ (const Float		*that) const;
		Matrix			operator- (const Float		*that);
		const Matrix	operator- (const Float		*that) const;
		Bool			operator==(const Float		*that) const;
		Bool			operator!=(const Float		*that) const;
		// Operators (Float)
		Matrix&			operator= (const Float		that);
		Matrix&			operator*=(const Float		that);
		Matrix&			operator+=(const Float		that);
		Matrix&			operator-=(const Float		that);
		Matrix			operator* (const Float		that);
		const Matrix	operator* (const Float		that) const;
		Matrix			operator+ (const Float		that);
		const Matrix	operator+ (const Float		that) const;
		Matrix			operator- (const Float		that);
		const Matrix	operator- (const Float		that) const;
	};
}

#endif // FastMatrixHppIncluded
