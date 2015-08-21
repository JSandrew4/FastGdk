/******************************************************************************/
/*                                                                            */
/*  Matrix.cpp                                                                */
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

#include <Fast/Matrix.hpp>
#include <Fast/Math.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Vector3DMath.hpp>
#include <Fast/Vector4D.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Box2D.hpp>

#include <cmath>
#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	void MatrixMultiply(Float *m1, const Float *m2) {
		Float m[16];
		for (Int i = 0; i < 4; i++) {
			for (Int j = 0; j <= 12; j += 4) {
				m[i+j] =
					m1[i   ] * m2[j  ] +
					m1[i+4 ] * m2[j+1] +
					m1[i+8 ] * m2[j+2] +
					m1[i+12] * m2[j+3];
			}
		}
		memcpy(m1, m, 64);
	}

	void MatrixAdd(Float *m1, const Float *m2) {
		Float m[16];
		for (Int i = 0; i < 16; i++)
			m[i] = m1[i] + m2[i];
		memcpy(m1, m, 64);
	}

	void MatrixSubtract(Float *m1, const Float *m2) {
		Float m[16];
		for (Int i = 0; i < 16; i++)
			m[i] = m1[i] - m2[i];
		memcpy(m1, m, 64);
	}

	Matrix::Matrix() {
		*this = kFastMatrixIdentity;
	}

	Matrix::Matrix(const Matrix &that) {
		*this = that;
	}

	Matrix::Matrix(
		Float m11, Float m12, Float m13, Float m14,
		Float m21, Float m22, Float m23, Float m24,
		Float m31, Float m32, Float m33, Float m34,
		Float m41, Float m42, Float m43, Float m44)
	{
		Float *m = mElements; // Make initialization cleaner
		m[ 0] = m11; m[ 4] = m12; m[ 8] = m13; m[12] = m14;
		m[ 1] = m21; m[ 5] = m22; m[ 9] = m23; m[13] = m24;
		m[ 2] = m31; m[ 6] = m32; m[10] = m33; m[14] = m34;
		m[ 3] = m41; m[ 7] = m42; m[11] = m43; m[15] = m44;
	}

	Matrix::Matrix(const Float *m) {
		*this = m;
	}

	Matrix::~Matrix() { }

	Float Matrix::GetElement(Int x, Int y) const {
		return mElements[(4 * x) + y];
	}

	Float Matrix::GetDeterminant() const {
		// TODO
		return 0.0f;
	}

	Vector3D Matrix::GetTranslation() const {
		// TODO
		return Vector3D();
	}

	Vector3D Matrix::GetScale() const {
		// TODO
		return Vector3D();
	}

	Quaternion Matrix::GetRotation() const {
		// TODO
		return Quaternion();
	}

	void Matrix::SetElement(Int x, Int y, Float element) {
		mElements[(4 * x) + y] = element;
	}

	void Matrix::Transpose() {
		Float temp;
		Float *m = mElements;
		for (Int i = 0; i < 3; i++) {
			for (Int j = (4*i); j <= 12; j += 4) {
				temp = m[i+j];
				m[i+j] = m[(j/4)+(4*i)];
				m[(j/4)+(4*i)] = temp;
			}
		}
	}

	void Matrix::Invert() {
		// TODO
	}

	void Matrix::Transform(const Quaternion &rotation) {
		// TODO
	}

	Matrix Matrix::CreateBillboard(const Vector3D &objectPosition,
		const Vector3D &camPosition, const Vector3D &camUp,
		const Vector3D &camForward)
	{
		Matrix m;
		CreateBillboard(objectPosition, camPosition, camUp, camForward, &m);
		return m;
	}

	void Matrix::CreateBillboard(const Vector3D &objectPosition,
		const Vector3D &camPosition, const Vector3D &camUp,
		const Vector3D &camForward, Matrix *result)
	{
		// TODO
	}

	Matrix Matrix::CreateConstrainedBillboard(const Vector3D &objectPosition,
		const Vector3D &camPosition, const Vector3D &rotateAxis,
		const Vector3D &camForward, const Vector3D &objectForward)
	{
		Matrix m;
		CreateConstrainedBillboard(objectPosition, camPosition,
			rotateAxis, camForward, objectForward, &m);
		return m;
	}

	void Matrix::CreateConstrainedBillboard(const Vector3D &objectPosition,
		const Vector3D &camPosition, const Vector3D &rotateAxis,
		const Vector3D &camForward, const Vector3D &objectForward,
		Matrix *result)
	{
		// TODO
	}

	Matrix Matrix::CreateFromPitchYawRoll(const Vector3D &pitchYawRoll) {
		Matrix m;
		CreateFromPitchYawRoll(pitchYawRoll, &m);
		return m;
	}

	void Matrix::CreateFromPitchYawRoll(
		const Vector3D &pitchYawRoll, Matrix *result)
	{
		Float *m = result->mElements;
		Float cx = cos(pitchYawRoll.mX);
		Float sx = sin(pitchYawRoll.mX);
		Float cy = cos(pitchYawRoll.mY);
		Float sy = sin(pitchYawRoll.mY);
		Float cz = cos(pitchYawRoll.mZ);
		Float sz = sin(pitchYawRoll.mZ);
		*result = kFastMatrixIdentity;
		/* FIXME:
		m[ 0] =    cy * cz;
		m[ 1] =  -(sy * cz);
		m[ 2] =    sz;
		m[ 4] =   (cy * sz * sx) + (sy * cx);
		m[ 5] = -((sy * sz * sx) - (cy * cx));
		m[ 6] =  -(cz * sx);
		m[ 8] = -((cy * sz * cx) - (sy * sx));
		m[ 9] =   (sy * sz * cx) + (cy * sx);
		m[10] =    cz * cx; */
	}

	Matrix Matrix::CreateLookAt(const Vector3D &camPosition,
		const Vector3D &camTarget, const Vector3D &camUp)
	{
		Matrix m;
		CreateLookAt(camPosition, camTarget, camUp, &m);
		return m;
	}

	void Matrix::CreateLookAt(const Vector3D &camPosition,
		const Vector3D &camTarget, const Vector3D &camUp, Matrix *result)
	{
		Vector3D forward, side, up = camUp;
		Float *m = result->mElements;
		*result = kFastMatrixIdentity;
		Vector3DMath::Normalize(camTarget - camPosition, &forward);
		Vector3DMath::Cross(forward, up, &side);
		side.Normalize();
		Vector3DMath::Cross(side, forward, &up);
		m[ 0] =  side.mX;
		m[ 1] =  up.mX;
		m[ 2] = -forward.mX;
		m[ 3] =  0.0f;
		m[ 4] =  side.mY;
		m[ 5] =  up.mY;
		m[ 6] = -forward.mY;
		m[ 7] =  0.0f;
		m[ 8] =  side.mZ;
		m[ 9] =  up.mZ;
		m[10] = -forward.mZ;
		m[11] =  0.0f;
		m[12] = -Vector3DMath::Dot(side, camPosition);
		m[13] = -Vector3DMath::Dot(up, camPosition);
		m[14] =  Vector3DMath::Dot(forward, camPosition);
		m[15] =  1.0f;
	}

	Matrix Matrix::CreateOrthographic(Float width,
		Float height, Float znear, Float zfar)
	{
		Matrix m;
		CreateOrthographic(width, height, znear, zfar, &m);
		return m;
	}

	void Matrix::CreateOrthographic(Float width,
		Float height, Float znear, Float zfar, Matrix *result)
	{
		CreateOrthographicOffCenter(
			Box2D(-width/2.0f, -height/2.0f, width, height),
			znear, zfar, result);
	}

	Matrix Matrix::CreateOrthographicOffCenter(
		const Box2D &box2D, Float nearPlane, Float farPlane)
	{
		Matrix m;
		CreateOrthographicOffCenter(box2D, nearPlane, farPlane, &m);
		return m;
	}

	void Matrix::CreateOrthographicOffCenter(
		const Box2D &box2D, Float nearPlane, Float farPlane, Matrix *result)
	{
		*result = kFastMatrixIdentity;
		Float farMinusNear = farPlane - nearPlane;
		Float widthPlusXOFfset = box2D.mSize.mX + box2D.mOrigin.mX;
		Float heightPlusYOFfset = box2D.mSize.mY + box2D.mOrigin.mY;
		if (farMinusNear == 0.0f || box2D.mSize.mX == 0.0f ||
			box2D.mSize.mY == 0.0f)
		{
			return;
		}
		Float *m = result->mElements;
		m[ 0] =  2.0f / box2D.mSize.mX;
		m[ 5] =  2.0f / box2D.mSize.mY;
		m[10] = -2.0f / farMinusNear;
		m[12] = -( widthPlusXOFfset+box2D.mOrigin.mX) / box2D.mSize.mX;
		m[13] = -(heightPlusYOFfset+box2D.mOrigin.mY) / box2D.mSize.mY;
		m[14] = -(farPlane+nearPlane) / farMinusNear;
	}

	Matrix Matrix::CreateReflection(const Vector3D &normal, Float distance) {
		Matrix m;
		CreateReflection(normal, distance, &m);
		return m;
	}

	void Matrix::CreateReflection(const Vector3D &normal,
		Float distance, Matrix *result)
	{
		// TODO
	}

	Matrix Matrix::CreateShadow(const Vector3D &lightDirection,
		const Vector3D &normal, Float distance)
	{
		Matrix m;
		CreateShadow(lightDirection, normal, distance, &m);
		return m;
	}

	void Matrix::CreateShadow(const Vector3D &lightDirection,
		const Vector3D &normal, Float distance, Matrix *result)
	{
		// TODO
	}

	Matrix Matrix::CreateWorld(const Vector3D &position,
		const Vector3D &forward, const Vector3D &up)
	{
		Matrix m;
		CreateWorld(position, forward, up, &m);
		return m;
	}

	void Matrix::CreateWorld(const Vector3D &position, const Vector3D &forward,
		const Vector3D &up, Matrix *result)
	{
		// TODO
	}

	Matrix Matrix::CreateLerp(const Matrix &a, const Matrix &b, Float t) {
		Matrix m;
		CreateLerp(a, b, t, &m);
		return m;
	}

	void Matrix::CreateLerp(const Matrix &a,
		const Matrix &b, Float t, Matrix *result)
	{
		// TODO
	}

	Matrix Matrix::CreateTransform(const Matrix &matrix,
		const Quaternion &rotation)
	{
		Matrix m;
		CreateTransform(matrix, rotation, &m);
		return m;
	}

	void Matrix::CreateTransform(const Matrix &matrix,
		const Quaternion &rotation, Matrix *result)
	{
		// TODO
	}

	Matrix Matrix::CreateTranspose(const Matrix &m) {
		Matrix tm;
		CreateTranspose(m, &tm);
		return tm;
	}

	void Matrix::CreateTranspose(const Matrix &m, Matrix *result) {
		*result = m;
		result->Transpose();
	}

	Matrix Matrix::CreateFrustumOffCenter(
		const Box2D &box2D, Float znear, Float zfar)
	{
		Matrix m;
		CreateFrustumOffCenter(box2D, znear, zfar, &m);
		return m;
	}

	void Matrix::CreateFrustumOffCenter(const Box2D &box2D,
		Float znear, Float zfar, Matrix *result)
	{
		Float zdelta = (zfar - znear);
		Float right  = (box2D.mOrigin.mX + box2D.mSize.mX);
		Float bottom = (box2D.mOrigin.mY + box2D.mSize.mY);
		Float znear2 = 2.0f * znear;
		*result = kFastMatrixIdentity;
		if (zfar < 0.0f || znear < 0.0f)
			return;
		result->mElements[ 0] =  znear2 / box2D.mSize.mX;
		result->mElements[ 1] =  0.0f;
		result->mElements[ 2] =  0.0f;
		result->mElements[ 3] =  0.0f;
		result->mElements[ 4] =  0.0f;
		result->mElements[ 5] =  znear2 / box2D.mSize.mY;
		result->mElements[ 6] =  0.0f;
		result->mElements[ 7] =  0.0f;
		result->mElements[ 8] =  (right + box2D.mOrigin.mX) / box2D.mSize.mX;
		result->mElements[ 9] =  (bottom + box2D.mOrigin.mY) / box2D.mSize.mY;
		result->mElements[10] = -(zfar + znear) / zdelta;
		result->mElements[11] = -1.0f;
		result->mElements[12] =  0.0f;
		result->mElements[13] =  0.0f;
		result->mElements[14] = -znear2 * zfar / zdelta;
		result->mElements[15] =  0.0f;
	}

	Matrix Matrix::CreateFrustum(Float width,
		Float height, Float znear, Float zfar)
	{
		Matrix m;
		CreateFrustum(width, height, znear, zfar, &m);
		return m;
	}

	void Matrix::CreateFrustum(Float width, Float height,
		Float znear, Float zfar, Matrix *result)
	{
		Float whalf = width / 2.0f;
		Float hhalf = height / 2.0f;
		CreateFrustumOffCenter(Box2D(-whalf, -hhalf, whalf, hhalf),
			znear, zfar, result);
	}

	Matrix Matrix::CreatePerspective(Float yfovDegrees,
		Float aspect, Float nearDistance, Float farDistance)
	{
		Matrix m;
		CreatePerspective(yfovDegrees, aspect, nearDistance, farDistance, &m);
		return m;
	}

	void Matrix::CreatePerspective(Float yfovDegrees, Float aspect,
		Float nearDistance, Float farDistance, Matrix *result)
	{
		Float zdelta = nearDistance - farDistance;
		Float f = (1.0f / tan(yfovDegrees / 360.0f * kFastMathPi));
		Float *m = result->mElements;
		*result = kFastMatrixIdentity;
		m[ 0] =  f / aspect;
		m[ 5] =  f;
		m[10] = (farDistance + nearDistance) / zdelta;
		m[11] = -1.0f;
		m[14] = (2.0f * farDistance * nearDistance) / zdelta;
		m[15] = 0.0f;
	}

	Matrix Matrix::CreateFromQuaternion(const Quaternion &q) {
		Matrix m;
		CreateFromQuaternion(q, &m);
		return m;
	}

	void Matrix::CreateFromQuaternion(const Quaternion &q, Matrix *result) {
		Float xx = q.mX * q.mX;
		Float xy = q.mX * q.mY;
		Float xz = q.mX * q.mZ;
		Float xw = q.mX * q.mZ;
		Float yy = q.mY * q.mY;
		Float yz = q.mY * q.mZ;
		Float yw = q.mY * q.mW;
		Float zz = q.mZ * q.mZ;
		Float zw = q.mZ * q.mW;
		*result = kFastMatrixIdentity;
		result->mElements[ 0] = 1.0f - 2.0f * (yy + zz);
		result->mElements[ 1] = 2.0f        * (xy - zw);
		result->mElements[ 2] = 2.0f        * (xz + yw);
		result->mElements[ 3] = 0.0f                   ;
		result->mElements[ 4] = 2.0f        * (xy + zw);
		result->mElements[ 5] = 1.0f - 2.0f * (xx + zz);
		result->mElements[ 6] = 2.0f        * (yz - xw);
		result->mElements[ 7] = 0.0f                   ;
		result->mElements[ 8] = 2.0f        * (xz - yw);
		result->mElements[ 9] = 2.0f        * (yz + xw);
		result->mElements[10] = 1.0f - 2.0f * (xx + yy);
		result->mElements[11] = 0.0f                   ;
		result->mElements[12] = 0.0f                   ;
		result->mElements[13] = 0.0f                   ;
		result->mElements[14] = 0.0f                   ;
		result->mElements[15] = 1.0f                   ;
	}

	Matrix Matrix::CreateTranslation(const Vector3D &position) {
		Matrix m;
		CreateTranslation(position, &m);
		return m;
	}

	void Matrix::CreateTranslation(const Vector3D &position, Matrix *result) {
		*result = kFastMatrixIdentity;
		result->mElements[12] = position.mX;
		result->mElements[13] = position.mY;
		result->mElements[14] = position.mZ;
	}

	Matrix Matrix::CreateScale(const Vector3D &scales) {
		Matrix m;
		CreateScale(scales, &m);
		return m;
	}

	void Matrix::CreateScale(const Vector3D &scales, Matrix *result) {
		*result = kFastMatrixIdentity;
		result->mElements[ 0] = scales.mX;
		result->mElements[ 5] = scales.mY;
		result->mElements[10] = scales.mZ;
	}

	Matrix Matrix::CreateScale(Float scale) {
		Matrix m;
		CreateScale(scale, &m);
		return m;
	}

	void Matrix::CreateScale(Float scale, Matrix *result) {
		*result = kFastMatrixIdentity;
		result->mElements[ 0] = scale;
		result->mElements[ 5] = scale;
		result->mElements[10] = scale;
	}

	Matrix Matrix::CreateRotationX(Float radians) {
		Matrix m;
		CreateRotationX(radians, &m);
		return m;
	}

	void Matrix::CreateRotationX(Float radians, Matrix *result) {
		*result = kFastMatrixIdentity;
		result->mElements[ 0] =  cos(radians);
		result->mElements[ 1] = -sin(radians);
		result->mElements[ 4] =  sin(radians);
		result->mElements[ 5] =  cos(radians);
	}

	Matrix Matrix::CreateRotationY(Float radians) {
		Matrix m;
		CreateRotationY(radians, &m);
		return m;
	}

	void Matrix::CreateRotationY(Float radians, Matrix *result) {
		*result = kFastMatrixIdentity;
		result->mElements[ 5] =  cos(radians);
		result->mElements[ 6] = -sin(radians);
		result->mElements[ 9] =  sin(radians);
		result->mElements[10] =  cos(radians);
	}

	Matrix Matrix::CreateRotationZ(Float radians) {
		Matrix m;
		CreateRotationZ(radians, &m);
		return m;
	}

	void Matrix::CreateRotationZ(Float radians, Matrix *result) {
		*result = kFastMatrixIdentity;
		result->mElements[ 0] =  cos(radians);
		result->mElements[ 2] =  sin(radians);
		result->mElements[ 8] = -sin(radians);
		result->mElements[10] =  cos(radians);
	}

	Matrix Matrix::CreateFromAxisAngle(const Vector3D &axis, Float radians) {
		Matrix m;
		CreateFromAxisAngle(axis, radians, &m);
		return m;
	}

	void Matrix::CreateFromAxisAngle(const Vector3D &axis,
		Float radians, Matrix *result)
	{
		Float c = cos(radians);
		Float s = sin(radians);
		Float t = 1.0f - c;
		*result = kFastMatrixIdentity;
		result->mElements[ 0] = t * axis.mX * axis.mX + c;
		result->mElements[ 1] = t * axis.mX * axis.mY + axis.mZ * s;
		result->mElements[ 2] = t * axis.mX * axis.mZ - axis.mY * s;
		result->mElements[ 4] = t * axis.mX * axis.mY - axis.mZ * s;
		result->mElements[ 5] = t * axis.mY * axis.mY + c;
		result->mElements[ 6] = t * axis.mY * axis.mZ + axis.mX * s;
		result->mElements[ 8] = t * axis.mX * axis.mZ + axis.mY * s;
		result->mElements[ 9] = t * axis.mY * axis.mZ - axis.mX * s;
		result->mElements[10] = t * axis.mZ * axis.mZ + c;
	}

	Matrix& Matrix::operator=(const Matrix &that) {
		memcpy(this->mElements, that.mElements, 64);
		return *this;
	}

	Matrix& Matrix::operator*=(const Matrix &that) {
		MatrixMultiply(this->mElements, that.mElements);
		return *this;
	}

	Matrix& Matrix::operator+=(const Matrix &that) {
		MatrixAdd(this->mElements, that.mElements);
		return *this;
	}

	Matrix& Matrix::operator-=(const Matrix &that) {
		MatrixSubtract(this->mElements, that.mElements);
		return *this;
	}

	Matrix Matrix::operator*(const Matrix &that) {
		Matrix m = *this;
		MatrixMultiply(m.mElements, that.mElements);
		return m;
	}

	const Matrix Matrix::operator*(const Matrix &that) const {
		Matrix m = *this;
		MatrixMultiply(m.mElements, that.mElements);
		return m;
	}

	Matrix Matrix::operator+(const Matrix &that) {
		Matrix m = *this;
		MatrixAdd(m.mElements, that.mElements);
		return m;
	}

	const Matrix Matrix::operator+(const Matrix &that) const {
		Matrix m = *this;
		MatrixAdd(m.mElements, that.mElements);
		return m;
	}

	Matrix Matrix::operator-(const Matrix &that) {
		Matrix m = *this;
		MatrixSubtract(m.mElements, that.mElements);
		return m;
	}

	const Matrix Matrix::operator-(const Matrix &that) const {
		Matrix m = *this;
		MatrixSubtract(m.mElements, that.mElements);
		return m;
	}

	Bool Matrix::operator==(const Matrix &that) const {
		if (0 == memcmp(this->mElements, that.mElements, 64))
			return true;
		return false;
	}

	Bool Matrix::operator!=(const Matrix &that) const {
		if (0 == memcmp(this->mElements, that.mElements, 64))
			return false;
		return true;
	}

	Matrix& Matrix::operator=(const Float *that) {
		memcpy(this->mElements, that, 64);
		return *this;
	}

	Matrix& Matrix::operator*=(const Float *that) {
		MatrixMultiply(this->mElements, that);
		return *this;
	}

	Matrix& Matrix::operator+=(const Float *that) {
		MatrixAdd(this->mElements, that);
		return *this;
	}

	Matrix& Matrix::operator-=(const Float *that) {
		MatrixSubtract(this->mElements, that);
		return *this;
	}

	Matrix Matrix::operator*(const Float *that) {
		Matrix m = *this;
		MatrixMultiply(m.mElements, that);
		return m;
	}

	const Matrix Matrix::operator*(const Float *that) const {
		Matrix m = *this;
		MatrixMultiply(m.mElements, that);
		return m;
	}

	Matrix Matrix::operator+(const Float *that) {
		Matrix m = *this;
		MatrixAdd(m.mElements, that);
		return m;
	}

	const Matrix Matrix::operator+(const Float *that) const {
		Matrix m = *this;
		MatrixAdd(m.mElements, that);
		return m;
	}

	Matrix Matrix::operator-(const Float *that) {
		Matrix m = *this;
		MatrixSubtract(m.mElements, that);
		return m;
	}

	const Matrix Matrix::operator-(const Float *that) const {
		Matrix m = *this;
		MatrixSubtract(m.mElements, that);
		return m;
	}

	Bool Matrix::operator==(const Float *that) const {
		if (0 == memcmp(this->mElements, that, 64))
			return true;
		return false;
	}

	Bool Matrix::operator!=(const Float *that) const {
		if (0 == memcmp(this->mElements, that, 64))
			return false;
		return true;
	}

	Matrix& Matrix::operator=(const Float that) {
		for (Int i = 0; i < 16; i++)
			this->mElements[i] = that;
		return *this;
	}

	Matrix& Matrix::operator*=(const Float that) {
		for (Int i = 0; i < 16; i++)
			this->mElements[i] *= that;
		return *this;
	}

	Matrix& Matrix::operator+=(const Float that) {
		for (Int i = 0; i < 16; i++)
			this->mElements[i] += that;
		return *this;
	}

	Matrix& Matrix::operator-=(const Float that) {
		for (Int i = 0; i < 16; i++)
			this->mElements[i] -= that;
		return *this;
	}

	Matrix Matrix::operator*(const Float that) {
		Matrix m;
		for (Int i = 0; i < 16; i++)
			m.mElements[i] *= that;
		return m;
	}

	const Matrix Matrix::operator*(const Float that) const {
		Matrix m;
		for (Int i = 0; i < 16; i++)
			m.mElements[i] *= that;
		return m;
	}

	Matrix Matrix::operator+(const Float that) {
		Matrix m;
		for (Int i = 0; i < 16; i++)
			m.mElements[i] += that;
		return m;
	}

	const Matrix Matrix::operator+(const Float that) const {
		Matrix m;
		for (Int i = 0; i < 16; i++)
			m.mElements[i] += that;
		return m;
	}

	Matrix Matrix::operator-(const Float that) {
		Matrix m;
		for (Int i = 0; i < 16; i++)
			m.mElements[i] -= that;
		return m;
	}

	const Matrix Matrix::operator-(const Float that) const {
		Matrix m;
		for (Int i = 0; i < 16; i++)
			m.mElements[i] -= that;
		return m;
	}
}
