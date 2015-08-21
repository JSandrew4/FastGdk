/******************************************************************************/
/*                                                                            */
/*  Vector2DMath.cpp                                                          */
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

#include <Fast/Vector2DMath.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Math.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	namespace Vector2DMath
	{
		Float Distance(const Vector2D &a, const Vector2D &b) {
			Vector2D c = a - b;
			return (sqrt((c.mX * c.mX) + (c.mY * c.mY)));
		}

		Float DistanceSquared(const Vector2D &a, const Vector2D &b) {
			Vector2D c = a - b;
			return ((c.mX * c.mX) + (c.mY * c.mY));
		}

		Float Dot(const Vector2D &a, const Vector2D &b) {
			return ((a.mX * b.mX) + (a.mY * b.mY));
		}

		Vector2D Normalize(const Vector2D &v) {
			if (0.0f == v) {
				return kFastVector2DZero;
			} else {
				return v / sqrt((v.mX * v.mX) + (v.mY * v.mY));
			}
		}

		void Normalize(const Vector2D &v, Vector2D *result) {
			if (0.0f == v) {
				*result = kFastVector2DZero;
			} else {
				*result = v / sqrt((v.mX * v.mX) + (v.mY * v.mY));
			}
		}

		Vector2D Reflect(const Vector2D &v, const Vector2D &normal) {
			return (v - (normal * Dot(v, normal) * 2.0f));
		}

		void Reflect(const Vector2D &v,
			const Vector2D &normal, Vector2D *result)
		{
			*result = (v - (normal * Dot(v, normal) * 2.0f));
		}

		Float Reflect(Float direction, const Vector2D &normal) {
			Vector2D v(cos(direction), sin(direction));
			v = (v - (normal * Dot(v, normal) * Vector2D(2.0f, 2.0f)));
			return atan2(v.mY, v.mX);
		}

		Bool IsSimilar(const Vector2D &a, const Vector2D &b, Float error) {
			return (Math::IsSimilar(a.mX, b.mX, error) &&
				Math::IsSimilar(a.mY, b.mY, error));
		}
	
		Vector2D Clamp(const Vector2D &value,
			const Vector2D &min, const Vector2D &max)
		{
			return Vector2D(Math::WrapFloat(value.mX, min.mX, max.mX),
				Math::WrapFloat(value.mY, min.mY, max.mY));
		}
	
		void Clamp(const Vector2D &value, const Vector2D &min,
			const Vector2D &max, Vector2D *result)
		{
			result->mX = Math::WrapFloat(value.mX, min.mX, max.mX);
			result->mY = Math::WrapFloat(value.mY, min.mY, max.mY);
		}
	
		Vector2D Accelerate(const Vector2D &a, const Vector2D &b, Float t) {
			return Vector2D(Math::Accelerate(a.mX, b.mX, t),
				Math::Accelerate(a.mY, b.mY, t));
		}
	
		void Accelerate(const Vector2D &a,
			const Vector2D &b, Float t, Vector2D *result)
		{
			result->mX = Math::Accelerate(a.mX, b.mX, t);
			result->mY = Math::Accelerate(a.mY, b.mY, t);
		}
	
		Vector2D Barycentric(const Vector2D &a, const Vector2D &b,
			const Vector2D &c, Float t1, Float t2)
		{
			return Vector2D(Math::Barycentric(a.mX, b.mX, c.mX, t1, t2),
				Math::Barycentric(a.mY, b.mY, c.mY, t1, t2));
		}
	
		void Barycentric(const Vector2D &a, const Vector2D &b,
			const Vector2D &c, Float t1, Float t2, Vector2D *result)
		{
			result->mX = Math::Barycentric(a.mX, b.mX, c.mX, t1, t2);
			result->mY = Math::Barycentric(a.mX, b.mX, c.mX, t1, t2);
		}
	
		Vector2D CatmullRom(const Vector2D &a, const Vector2D &b,
			const Vector2D &c, const Vector2D &d, Float t)
		{
			return Vector2D(Math::CatmullRom(a.mX, b.mX, c.mX, d.mX, t),
				Math::CatmullRom(a.mY, b.mY, c.mY, d.mY, t));
		}
	
		void CatmullRom(const Vector2D &a, const Vector2D &b,
			const Vector2D &c, const Vector2D &d, Float t, Vector2D *result)
		{
			result->mX = Math::CatmullRom(a.mX, b.mX, c.mX, d.mX, t);
			result->mY = Math::CatmullRom(a.mY, b.mY, c.mY, d.mY, t);
		}
	
		Vector2D Cerp(const Vector2D &a, const Vector2D &b, Float t) {
			return Vector2D(Math::Cerp(a.mX, b.mX, t),
				Math::Cerp(a.mY, b.mY, t));
		}
	
		void Cerp(const Vector2D &a,
			const Vector2D &b, Float t, Vector2D *result)
		{
			result->mX = Math::Cerp(a.mX, b.mX, t);
			result->mY = Math::Cerp(a.mY, b.mY, t);
		}
	
		Vector2D Decelerate(const Vector2D &a, const Vector2D &b, Float t) {
			return Vector2D(Math::Decelerate(a.mX, b.mX, t),
				Math::Decelerate(a.mY, b.mY, t));
		}
	
		void Decelerate(const Vector2D &a,
			const Vector2D &b, Float t, Vector2D *result)
		{
			result->mX = Math::Decelerate(a.mX, b.mX, t);
			result->mY = Math::Decelerate(a.mY, b.mY, t);
		}
	
		Vector2D Hermite(const Vector2D &a, const Vector2D &aTangent,
			const Vector2D &b, const Vector2D &bTangent, Float t)
		{
			return Vector2D(
				Math::Hermite(a.mX, aTangent.mX, b.mX, bTangent.mX, t),
				Math::Hermite(a.mY, aTangent.mY, b.mY, bTangent.mY, t));
		}
	
		void Hermite(const Vector2D &a, const Vector2D &aTangent,
			const Vector2D &b, const Vector2D &bTangent,
			Float t, Vector2D *result)
		{
			result->mX = Math::Hermite(a.mX, aTangent.mX, b.mX, bTangent.mX, t);
			result->mY = Math::Hermite(a.mY, aTangent.mY, b.mY, bTangent.mY, t);
		}
	
		Vector2D Lerp(const Vector2D &a, const Vector2D &b, Float t) {
			return Vector2D(Math::Lerp(a.mX, b.mX, t),
				Math::Lerp(a.mY, b.mY, t));
		}
	
		void Lerp(const Vector2D &a,
			const Vector2D &b, Float t, Vector2D *result) {
			result->mX = Math::Lerp(a.mX, b.mX, t);
			result->mY = Math::Lerp(a.mY, b.mY, t);
		}

		Vector2D Nlerp(const Vector2D &a, const Vector2D &b, Float t) {
			Vector2D v;
			Lerp(a, b, t, &v);
			v.Normalize();
			return v;
		}

		void Nlerp(const Vector2D &a,
			const Vector2D &b, Float t, Vector2D *result)
		{
			Lerp(a, b, t, result);
			result->Normalize();
		}

		Vector2D Slerp(const Vector2D &a, const Vector2D &b, Float t) {
			 Float dot = Math::WrapFloat(Dot(a, b), -1.0f, 1.0f);
			 Float theta = acos(dot) * t;
			 Vector2D relativeVec = b - (a * dot);
			 relativeVec.Normalize();
			 return ((a*cos(theta)) + (relativeVec*sin(theta)));
		}

		void Slerp(const Vector2D &a,
			const Vector2D &b, Float t, Vector2D *result)
		{
			 Float dot = Math::WrapFloat(Dot(a, b), -1.0f, 1.0f);
			 Float theta = acos(dot) * t;
			 *result = b - (a * dot);
			 result->Normalize();
			 *result = ((a*cos(theta)) + (*result*sin(theta)));
		}
	
		Vector2D SmoothStep(const Vector2D &a, const Vector2D &b, Float t) {
			return Vector2D(Math::SmoothStep(a.mX, b.mX, t),
				Math::SmoothStep(a.mY, b.mY, t));
		}
	
		void SmoothStep(const Vector2D &a,
			const Vector2D &b, Float t, Vector2D *result)
		{
			result->mX = Math::SmoothStep(a.mX, b.mX, t);
			result->mY = Math::SmoothStep(a.mY, b.mY, t);
		}

		Vector2D Wrap(const Vector2D &value,
			const Vector2D &min, const Vector2D &max)
		{
			return Vector2D(Math::WrapFloat(value.mX, min.mX, max.mX),
				Math::WrapFloat(value.mY, min.mY, max.mY));
		}

		void Wrap(const Vector2D &value, const Vector2D &min,
			const Vector2D &max, Vector2D *result)
		{
			result->mX = Math::WrapFloat(value.mX, min.mX, max.mX);
			result->mY = Math::WrapFloat(value.mY, min.mY, max.mY);
		}
	}
}
