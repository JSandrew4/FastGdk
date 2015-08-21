/******************************************************************************/
/*                                                                            */
/*  Vector3DMath.cpp                                                          */
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

#include <Fast/Vector3DMath.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Math.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Vector2D.hpp>

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	namespace Vector3DMath
	{
		Float Distance(const Vector3D &a, const Vector3D &b) {
			Vector3D c = a - b;
			return (sqrt((c.mX * c.mX) + (c.mY * c.mY) + (c.mZ * c.mZ)));
		}

		Float DistanceSquared(const Vector3D &a, const Vector3D &b) {
			Vector3D c = a - b;
			return ((c.mX * c.mX) + (c.mY * c.mY) + (c.mZ * c.mZ));
		}

		Float Dot(const Vector3D &a, const Vector3D &b) {
			return ((a.mX * b.mX) + (a.mY * b.mY) + (a.mZ * b.mZ));
		}

		Vector3D Cross(const Vector3D &a, const Vector3D &b) {
			return Vector3D((a.mY * b.mZ) - (a.mZ * b.mY),
				(a.mZ * b.mX) - (a.mX * b.mZ),
				(a.mX * b.mY) - (a.mY * b.mX));
		}

		void Cross(const Vector3D &a,
			const Vector3D &b, Vector3D *result)
		{
			result->mX = (a.mY * b.mZ) - (a.mZ * b.mY);
			result->mY = (a.mZ * b.mX) - (a.mX * b.mZ);
			result->mZ = (a.mX * b.mY) - (a.mY * b.mX);
		}

		Vector3D Normalize(const Vector3D &v) {
			if (0.0f == v) {
				return kFastVector3DZero;
			} else {
				return v / sqrt((v.mX * v.mX) + (v.mY * v.mY) + (v.mZ * v.mZ));
			}
		}

		void Normalize(const Vector3D &v, Vector3D *result) {
			if (0.0f == v) {
				*result = kFastVector3DZero;
			} else {
				*result = v / sqrt((v.mX * v.mX) + (v.mY * v.mY) + (v.mZ * v.mZ));
			}
		}

		Vector3D Reflect(const Vector3D &v, const Vector3D &normal) {
			return (v - (normal * Dot(v, normal) * 2.0f));
		}

		void Reflect(const Vector3D &v,
			const Vector3D &normal, Vector3D *result)
		{
			*result = (v - (normal * Dot(v, normal) * 2.0f));
		}

		Bool IsSimilar(const Vector3D &a,
			const Vector3D &b, Float error)
		{
			return (Math::IsSimilar(a.mX, b.mX, error) &&
				Math::IsSimilar(a.mY, b.mY, error) &&
				Math::IsSimilar(a.mZ, b.mZ, error));
		}
	
		Vector3D Clamp(const Vector3D &value,
			const Vector3D &min, const Vector3D &max)
		{
			return Vector3D(Math::WrapFloat(value.mX, min.mX, max.mX),
				Math::WrapFloat(value.mY, min.mY, max.mY),
				Math::WrapFloat(value.mZ, min.mZ, max.mZ));
		}
	
		void Clamp(const Vector3D &value, const Vector3D &min,
			const Vector3D &max, Vector3D *result)
		{
			result->mX = Math::WrapFloat(value.mX, min.mX, max.mX);
			result->mY = Math::WrapFloat(value.mY, min.mY, max.mY);
			result->mZ = Math::WrapFloat(value.mZ, min.mZ, max.mZ);
		}
	
		Vector3D Accelerate(const Vector3D &a,
			const Vector3D &b, Float t)
		{
			return Vector3D(Math::Accelerate(a.mX, b.mX, t),
				Math::Accelerate(a.mY, b.mY, t),
				Math::Accelerate(a.mZ, b.mZ, t));
		}
	
		void Accelerate(const Vector3D &a,
			const Vector3D &b, Float t, Vector3D *result)
		{
			result->mX = Math::Accelerate(a.mX, b.mX, t);
			result->mY = Math::Accelerate(a.mY, b.mY, t);
			result->mZ = Math::Accelerate(a.mZ, b.mZ, t);
		}
	
		Vector3D Barycentric(const Vector3D &a, const Vector3D &b,
			const Vector3D &c, Float t1, Float t2)
		{
			return Vector3D(Math::Barycentric(a.mX, b.mX, c.mX, t1, t2),
				Math::Barycentric(a.mY, b.mY, c.mY, t1, t2),
				Math::Barycentric(a.mZ, b.mZ, c.mZ, t1, t2));
		}
	
		void Barycentric(const Vector3D &a, const Vector3D &b,
			const Vector3D &c, Float t1, Float t2, Vector3D *result)
		{
			result->mX = Math::Barycentric(a.mX, b.mX, c.mX, t1, t2);
			result->mY = Math::Barycentric(a.mX, b.mX, c.mX, t1, t2);
			result->mZ = Math::Barycentric(a.mZ, b.mZ, c.mZ, t1, t2);
		}
	
		Vector3D CatmullRom(const Vector3D &a, const Vector3D &b,
			const Vector3D &c, const Vector3D &d, Float t)
		{
			return Vector3D(Math::CatmullRom(a.mX, b.mX, c.mX, d.mX, t),
				Math::CatmullRom(a.mY, b.mY, c.mY, d.mY, t),
				Math::CatmullRom(a.mZ, b.mZ, c.mZ, d.mZ, t));
		}
	
		void CatmullRom(const Vector3D &a, const Vector3D &b,
			const Vector3D &c, const Vector3D &d, Float t, Vector3D *result)
		{
			result->mX = Math::CatmullRom(a.mX, b.mX, c.mX, d.mX, t);
			result->mY = Math::CatmullRom(a.mY, b.mY, c.mY, d.mY, t);
			result->mZ = Math::CatmullRom(a.mZ, b.mZ, c.mZ, d.mZ, t);
		}
	
		Vector3D Cerp(const Vector3D &a, const Vector3D &b, Float t) {
			return Vector3D(Math::Cerp(a.mX, b.mX, t), Math::Cerp(a.mY, b.mY, t),
				Math::Cerp(a.mZ, b.mZ, t));
		}
	
		void Cerp(const Vector3D &a,
			const Vector3D &b, Float t, Vector3D *result)
		{
			result->mX = Math::Cerp(a.mX, b.mX, t);
			result->mY = Math::Cerp(a.mY, b.mY, t);
			result->mZ = Math::Cerp(a.mZ, b.mZ, t);
		}
	
		Vector3D Decelerate(const Vector3D &a,
			const Vector3D &b, Float t)
		{
			return Vector3D(Math::Decelerate(a.mX, b.mX, t),
				Math::Decelerate(a.mY, b.mY, t),
				Math::Decelerate(a.mZ, b.mZ, t));
		}
	
		void Decelerate(const Vector3D &a,
			const Vector3D &b, Float t, Vector3D *result)
		{
			result->mX = Math::Decelerate(a.mX, b.mX, t);
			result->mY = Math::Decelerate(a.mY, b.mY, t);
			result->mZ = Math::Decelerate(a.mZ, b.mZ, t);
		}
	
		Vector3D Hermite(const Vector3D &a, const Vector3D &aTangent,
			const Vector3D &b, const Vector3D &bTangent, Float t)
		{
			return Vector3D(Math::Hermite(a.mX, aTangent.mX, b.mX, bTangent.mX, t),
				Math::Hermite(a.mY, aTangent.mY, b.mY, bTangent.mY, t),
				Math::Hermite(a.mZ, aTangent.mZ, b.mZ, bTangent.mZ, t));
		}
	
		void Hermite(const Vector3D &a, const Vector3D &aTangent,
			const Vector3D &b, const Vector3D &bTangent, Float t, Vector3D *result)
		{
			result->mX = Math::Hermite(a.mX, aTangent.mX, b.mX, bTangent.mX, t);
			result->mY = Math::Hermite(a.mY, aTangent.mY, b.mY, bTangent.mY, t);
			result->mZ = Math::Hermite(a.mZ, aTangent.mZ, b.mZ, bTangent.mZ, t);
		}
	
		Vector3D Lerp(const Vector3D &a, const Vector3D &b, Float t) {
			return Vector3D(Math::Lerp(a.mX, b.mX, t), Math::Lerp(a.mY, b.mY, t),
				Math::Lerp(a.mZ, b.mZ, t));
		}
	
		void Lerp(const Vector3D &a,
			const Vector3D &b, Float t, Vector3D *result)
		{
			result->mX = Math::Lerp(a.mX, b.mX, t);
			result->mY = Math::Lerp(a.mY, b.mY, t);
			result->mZ = Math::Lerp(a.mZ, b.mZ, t);
		}

		Vector3D Nlerp(const Vector3D &a, const Vector3D &b, Float t) {
			Vector3D v;
			Lerp(a, b, t, &v);
			v.Normalize();
			return v;
		}

		void Nlerp(const Vector3D &a,
			const Vector3D &b, Float t, Vector3D *result)
		{
			Lerp(a, b, t, result);
			result->Normalize();
		}

		Vector3D Slerp(const Vector3D &a, const Vector3D &b, Float t) {
			 Float dot = Math::WrapFloat(Dot(a, b), -1.0f, 1.0f);
			 Float theta = acos(dot) * t;
			 Vector3D relativeVec = b - (a * dot);
			 relativeVec.Normalize();
			 return ((a*cos(theta)) + (relativeVec*sin(theta)));
		}

		void Slerp(const Vector3D &a,
			const Vector3D &b, Float t, Vector3D *result)
		{
			 Float dot = Math::WrapFloat(Dot(a, b), -1.0f, 1.0f);
			 Float theta = acos(dot) * t;
			 *result = b - (a * dot);
			 result->Normalize();
			 *result = ((a*cos(theta)) + (*result*sin(theta)));
		}
	
		Vector3D SmoothStep(const Vector3D &a,
			const Vector3D &b, Float t)
		{
			return Vector3D(Math::SmoothStep(a.mX, b.mX, t),
				Math::SmoothStep(a.mY, b.mY, t),
				Math::SmoothStep(a.mZ, b.mZ, t));
		}
	
		void SmoothStep(const Vector3D &a,
			const Vector3D &b, Float t, Vector3D *result)
		{
			result->mX = Math::SmoothStep(a.mX, b.mX, t);
			result->mY = Math::SmoothStep(a.mY, b.mY, t);
			result->mZ = Math::SmoothStep(a.mZ, b.mZ, t);
		}

		Vector3D Wrap(const Vector3D &value,
			const Vector3D &min, const Vector3D &max)
		{
			return Vector3D(Math::WrapFloat(value.mX, min.mX, max.mX),
				Math::WrapFloat(value.mY, min.mY, max.mY),
				Math::WrapFloat(value.mZ, min.mZ, max.mZ));
		}

		void Wrap(const Vector3D &value, const Vector3D &min,
			const Vector3D &max, Vector3D *result)
		{
			result->mX = Math::WrapFloat(value.mX, min.mX, max.mX);
			result->mY = Math::WrapFloat(value.mY, min.mY, max.mY);
			result->mZ = Math::WrapFloat(value.mZ, min.mZ, max.mZ);
		}
	}
}
