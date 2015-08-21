/******************************************************************************/
/*                                                                            */
/*  Vector4DMath.cpp                                                          */
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

#include <Fast/Vector4DMath.hpp>
#include <Fast/Vector4D.hpp>
#include <Fast/Math.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	namespace Vector4DMath
	{
		Float Distance(const Vector4D &a, const Vector4D &b) {
			Vector4D c = a - b;
			return (sqrt((c.mX * c.mX) + (c.mY * c.mY) +
				(c.mZ * c.mZ) + (c.mW * c.mW)));
		}

		Float DistanceSquared(const Vector4D &a, const Vector4D &b) {
			Vector4D c = a - b;
			return ((c.mX * c.mX) + (c.mY * c.mY) +
				(c.mZ * c.mZ) + (c.mW * c.mW));
		}

		Float Dot(const Vector4D &a, const Vector4D &b) {
			return ((a.mX * b.mX) + (a.mY * b.mY) +
				(a.mZ * b.mZ) + (a.mW * b.mW));
		}

		Vector4D Normalize(const Vector4D &v) {
			if (0.0f == v) {
				return kFastVector4DZero;
			} else {
				return v / sqrt((v.mX * v.mX) + (v.mY * v.mY) +
					(v.mZ * v.mZ) + (v.mW * v.mW));
			}
		}

		void Normalize(const Vector4D &v, Vector4D *result) {
			if (0.0f == v) {
				*result = kFastVector4DZero;
			} else {
				*result = v / sqrt((v.mX * v.mX) + (v.mY * v.mY) +
					(v.mZ * v.mZ) + (v.mW * v.mW));
			}
		}

		Vector4D Reflect(const Vector4D &v, const Vector4D &normal) {
			return (v - (normal * Dot(v, normal) * 2.0f));
		}

		void Reflect(const Vector4D &v,
			const Vector4D &normal, Vector4D *result)
		{
			*result = (v - (normal * Dot(v, normal) * 2.0f));
		}

		Bool IsSimilar(const Vector4D &a,
			const Vector4D &b, Float error)
		{
			return (Math::IsSimilar(a.mX, b.mX, error) &&
				Math::IsSimilar(a.mY, b.mY, error) &&
				Math::IsSimilar(a.mZ, b.mZ, error) &&
				Math::IsSimilar(a.mW, b.mW, error));
		}
	
		Vector4D Clamp(const Vector4D &value,
			const Vector4D &min, const Vector4D &max)
		{
			return Vector4D(Math::WrapFloat(value.mX, min.mX, max.mX),
				Math::WrapFloat(value.mY, min.mY, max.mY),
				Math::WrapFloat(value.mZ, min.mZ, max.mZ),
				Math::WrapFloat(value.mW, min.mW, max.mW));
		}
	
		void Clamp(const Vector4D &value,
			const Vector4D &min, const Vector4D &max, Vector4D *result)
		{
			result->mX = Math::WrapFloat(value.mX, min.mX, max.mX);
			result->mY = Math::WrapFloat(value.mY, min.mY, max.mY);
			result->mZ = Math::WrapFloat(value.mZ, min.mZ, max.mZ);
			result->mW = Math::WrapFloat(value.mW, min.mW, max.mW);
		}
	
		Vector4D Accelerate(const Vector4D &a,
			const Vector4D &b, Float t)
		{
			return Vector4D(Math::Accelerate(a.mX, b.mX, t),
				Math::Accelerate(a.mY, b.mY, t),
				Math::Accelerate(a.mZ, b.mZ, t),
				Math::Accelerate(a.mW, b.mW, t));
		}
	
		void Accelerate(const Vector4D &a,
			const Vector4D &b, Float t, Vector4D *result)
		{
			result->mX = Math::Accelerate(a.mX, b.mX, t);
			result->mY = Math::Accelerate(a.mY, b.mY, t);
			result->mZ = Math::Accelerate(a.mZ, b.mZ, t);
			result->mW = Math::Accelerate(a.mW, b.mW, t);
		}
	
		Vector4D Barycentric(const Vector4D &a,
			const Vector4D &b, const Vector4D &c, Float t1, Float t2)
		{
			return Vector4D(Math::Barycentric(a.mX, b.mX, c.mX, t1, t2),
				Math::Barycentric(a.mY, b.mY, c.mY, t1, t2),
				Math::Barycentric(a.mZ, b.mZ, c.mZ, t1, t2),
				Math::Barycentric(a.mW, b.mW, c.mW, t1, t2));
		}
	
		void Barycentric(const Vector4D &a, const Vector4D &b,
			const Vector4D &c, Float t1, Float t2, Vector4D *result)
		{
			result->mX = Math::Barycentric(a.mX, b.mX, c.mX, t1, t2);
			result->mY = Math::Barycentric(a.mX, b.mX, c.mX, t1, t2);
			result->mZ = Math::Barycentric(a.mZ, b.mZ, c.mZ, t1, t2);
			result->mW = Math::Barycentric(a.mW, b.mW, c.mW, t1, t2);
		}
	
		Vector4D CatmullRom(const Vector4D &a, const Vector4D &b,
			const Vector4D &c, const Vector4D &d, Float t) {
			return Vector4D(Math::CatmullRom(a.mX, b.mX, c.mX, d.mX, t),
				Math::CatmullRom(a.mY, b.mY, c.mY, d.mY, t),
				Math::CatmullRom(a.mZ, b.mZ, c.mZ, d.mZ, t),
				Math::CatmullRom(a.mW, b.mW, c.mW, d.mW, t));
		}
	
		void CatmullRom(const Vector4D &a, const Vector4D &b,
			const Vector4D &c, const Vector4D &d, Float t, Vector4D *result)
		{
			result->mX = Math::CatmullRom(a.mX, b.mX, c.mX, d.mX, t);
			result->mY = Math::CatmullRom(a.mY, b.mY, c.mY, d.mY, t);
			result->mZ = Math::CatmullRom(a.mZ, b.mZ, c.mZ, d.mZ, t);
			result->mW = Math::CatmullRom(a.mW, b.mW, c.mW, d.mW, t);
		}
	
		Vector4D Cerp(const Vector4D &a, const Vector4D &b, Float t) {
			return Vector4D(
				Math::Cerp(a.mX, b.mX, t), Math::Cerp(a.mY, b.mY, t),
				Math::Cerp(a.mZ, b.mZ, t), Math::Cerp(a.mW, b.mW, t));
		}
	
		void Cerp(const Vector4D &a,
			const Vector4D &b, Float t, Vector4D *result)
		{
			result->mX = Math::Cerp(a.mX, b.mX, t);
			result->mY = Math::Cerp(a.mY, b.mY, t);
			result->mZ = Math::Cerp(a.mZ, b.mZ, t);
			result->mW = Math::Cerp(a.mW, b.mW, t);
		}
	
		Vector4D Decelerate(const Vector4D &a,
			const Vector4D &b, Float t)
		{
			return Vector4D(Math::Decelerate(a.mX, b.mX, t),
				Math::Decelerate(a.mY, b.mY, t),
				Math::Decelerate(a.mZ, b.mZ, t),
				Math::Decelerate(a.mW, b.mW, t));
		}
	
		void Decelerate(const Vector4D &a,
			const Vector4D &b, Float t, Vector4D *result)
		{
			result->mX = Math::Decelerate(a.mX, b.mX, t);
			result->mY = Math::Decelerate(a.mY, b.mY, t);
			result->mZ = Math::Decelerate(a.mZ, b.mZ, t);
			result->mW = Math::Decelerate(a.mW, b.mW, t);
		}
	
		Vector4D Hermite(const Vector4D &a, const Vector4D &aTangent,
			const Vector4D &b, const Vector4D &bTangent, Float t)
		{
			return Vector4D(
				Math::Hermite(a.mX, aTangent.mX, b.mX, bTangent.mX, t),
				Math::Hermite(a.mY, aTangent.mY, b.mY, bTangent.mY, t),
				Math::Hermite(a.mZ, aTangent.mZ, b.mZ, bTangent.mZ, t),
				Math::Hermite(a.mW, aTangent.mW, b.mW, bTangent.mW, t));
		}
	
		void Hermite(const Vector4D &a, const Vector4D &aTangent,
			const Vector4D &b, const Vector4D &bTangent,
			Float t, Vector4D *result)
		{
			result->mX = Math::Hermite(a.mX, aTangent.mX, b.mX, bTangent.mX, t);
			result->mY = Math::Hermite(a.mY, aTangent.mY, b.mY, bTangent.mY, t);
			result->mZ = Math::Hermite(a.mZ, aTangent.mZ, b.mZ, bTangent.mZ, t);
			result->mW = Math::Hermite(a.mW, aTangent.mW, b.mW, bTangent.mW, t);
		}
	
		Vector4D Lerp(const Vector4D &a, const Vector4D &b, Float t) {
			return Vector4D(
				Math::Lerp(a.mX, b.mX, t), Math::Lerp(a.mY, b.mY, t),
				Math::Lerp(a.mZ, b.mZ, t), Math::Lerp(a.mW, b.mW, t));
		}
	
		void Lerp(const Vector4D &a,
			const Vector4D &b, Float t, Vector4D *result)
		{
			result->mX = Math::Lerp(a.mX, b.mX, t);
			result->mY = Math::Lerp(a.mY, b.mY, t);
			result->mZ = Math::Lerp(a.mZ, b.mZ, t);
			result->mW = Math::Lerp(a.mW, b.mW, t);
		}

		Vector4D Nlerp(const Vector4D &a, const Vector4D &b, Float t) {
			Vector4D v;
			Lerp(a, b, t, &v);
			v.Normalize();
			return v;
		}

		void Nlerp(const Vector4D &a,
			const Vector4D &b, Float t, Vector4D *result)
		{
			Lerp(a, b, t, result);
			result->Normalize();
		}

		Vector4D Slerp(const Vector4D &a, const Vector4D &b, Float t) {
			 Float dot = Math::WrapFloat(Dot(a, b), -1.0f, 1.0f);
			 Float theta = acos(dot) * t;
			 Vector4D relativeVec = b - (a * dot);
			 relativeVec.Normalize();
			 return ((a*cos(theta)) + (relativeVec*sin(theta)));
		}

		void Slerp(const Vector4D &a,
			const Vector4D &b, Float t, Vector4D *result)
		{
			 Float dot = Math::WrapFloat(Dot(a, b), -1.0f, 1.0f);
			 Float theta = acos(dot) * t;
			 *result = b - (a * dot);
			 result->Normalize();
			 *result = ((a*cos(theta)) + (*result*sin(theta)));
		}
	
		Vector4D SmoothStep(const Vector4D &a,
			const Vector4D &b, Float t)
		{
			return Vector4D(Math::SmoothStep(a.mX, b.mX, t),
				Math::SmoothStep(a.mY, b.mY, t),
				Math::SmoothStep(a.mZ, b.mZ, t),
				Math::SmoothStep(a.mW, b.mW, t));
		}
	
		void SmoothStep(const Vector4D &a,
			const Vector4D &b, Float t, Vector4D *result)
		{
			result->mX = Math::SmoothStep(a.mX, b.mX, t);
			result->mY = Math::SmoothStep(a.mY, b.mY, t);
			result->mZ = Math::SmoothStep(a.mZ, b.mZ, t);
			result->mW = Math::SmoothStep(a.mW, b.mW, t);
		}

		Vector4D Wrap(const Vector4D &value,
			const Vector4D &min, const Vector4D &max)
		{
			return Vector4D(Math::WrapFloat(value.mX, min.mX, max.mX),
				Math::WrapFloat(value.mY, min.mY, max.mY),
				Math::WrapFloat(value.mZ, min.mZ, max.mZ),
				Math::WrapFloat(value.mW, min.mW, max.mW));
		}

		void Wrap(const Vector4D &value, const Vector4D &min,
			const Vector4D &max, Vector4D *result)
		{
			result->mX = Math::WrapFloat(value.mX, min.mX, max.mX);
			result->mY = Math::WrapFloat(value.mY, min.mY, max.mY);
			result->mZ = Math::WrapFloat(value.mZ, min.mZ, max.mZ);
			result->mW = Math::WrapFloat(value.mW, min.mW, max.mW);
		}
	}
}
