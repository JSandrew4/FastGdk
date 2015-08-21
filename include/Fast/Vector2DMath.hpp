/******************************************************************************/
/*                                                                            */
/*  Vector2DMath.hpp                                                          */
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

#ifndef FastVector2DMathHppIncluded
#define FastVector2DMathHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector2D.hpp>

namespace Fast
{
	class Matrix;
	class Quaternion;

	namespace Vector2DMath
	{
		FastApi Float		Distance(const Vector2D &a, const Vector2D &b);
		FastApi Float		DistanceSquared(const Vector2D &a,
								const Vector2D &b);
		FastApi Float		Dot(const Vector2D &a, const Vector2D &b);
		FastApi Float		Reflect(Float direction, const Vector2D &normal);
		FastApi Vector2D	Normalize(const Vector2D &v);
		FastApi void		Normalize(const Vector2D &v, Vector2D *result);
		FastApi Vector2D	Reflect(const Vector2D &v, const Vector2D &normal);
		FastApi void		Reflect(const Vector2D &v,
								const Vector2D &normal, Vector2D *result);
		FastApi Bool		IsSimilar(const Vector2D &a,
								const Vector2D &b, Float error);
		FastApi Vector2D	Clamp(const Vector2D &value,
								const Vector2D &min, const Vector2D &max);
		FastApi void		Clamp(const Vector2D &value, const Vector2D &min,
								const Vector2D &max, Vector2D *result);
		FastApi Vector2D	Accelerate(const Vector2D &a,
								const Vector2D &b, Float t);
		FastApi void		Accelerate(const Vector2D &a, const Vector2D &b,
								Float t, Vector2D *result);
		FastApi Vector2D	Barycentric(const Vector2D &a, const Vector2D &b,
								const Vector2D &c, Float t1, Float t2);
		FastApi void		Barycentric(const Vector2D &a, const Vector2D &b,
								const Vector2D &c, Float t1, Float t2,
								Vector2D *result);
		FastApi Vector2D	CatmullRom(const Vector2D &a, const Vector2D &b,
								const Vector2D &c, const Vector2D &d, Float t);
		FastApi void		CatmullRom(const Vector2D &a, const Vector2D &b,
								const Vector2D &c, const Vector2D &d, Float t,
								Vector2D *result);
		FastApi Vector2D	Cerp(const Vector2D &a,
								const Vector2D &b, Float t);
		FastApi void		Cerp(const Vector2D &a, const Vector2D &b,
								Float t, Vector2D *result);
		FastApi Vector2D	Decelerate(const Vector2D &a,
								const Vector2D &b, Float t);
		FastApi void		Decelerate(const Vector2D &a, const Vector2D &b,
								Float t, Vector2D *result);
		FastApi Vector2D	Hermite(const Vector2D &a,
								const Vector2D &aTangent, const Vector2D &b,
								const Vector2D &bTangent, Float t);
		FastApi void		Hermite(const Vector2D &a,
								const Vector2D &aTangent,
								const Vector2D &b, const Vector2D &bTangent,
								Float t, Vector2D *result);
		FastApi Vector2D	Lerp(const Vector2D &a,
								const Vector2D &b, Float t);
		FastApi void		Lerp(const Vector2D &a, const Vector2D &b,
								Float t, Vector2D *result);
		FastApi Vector2D	Nlerp(const Vector2D &a,
								const Vector2D &b, Float t);
		FastApi void		Nlerp(const Vector2D &a, const Vector2D &b,
								Float t, Vector2D *result);
		FastApi Vector2D	Slerp(const Vector2D &a,
								const Vector2D &b, Float t);
		FastApi void		Slerp(const Vector2D &a, const Vector2D &b,
								Float t, Vector2D *result);
		FastApi Vector2D	SmoothStep(const Vector2D &a,
								const Vector2D &b, Float t);
		FastApi void		SmoothStep(const Vector2D &a, const Vector2D &b,
								Float t, Vector2D *result);
		FastApi Vector2D	Transform(const Vector2D &position,
								const Matrix &m);
		FastApi void		Transform(const Vector2D &position,
								const Matrix &m, Vector2D *result);
		FastApi Vector2D	Transform(const Vector2D &value,
								const Quaternion &rotation);
		FastApi void		Transform(const Vector2D &value,
								const Quaternion &rotation, Vector2D *result);
		FastApi Vector2D	TransformNormal(const Vector2D &normal,
								const Matrix &m);
		FastApi void		TransformNormal(const Vector2D &normal,
								const Matrix &m, Vector2D *result);
		FastApi Vector2D	Wrap(const Vector2D &value, const Vector2D &min,
								const Vector2D &max);
		FastApi void		Wrap(const Vector2D &value, const Vector2D &min,
								const Vector2D &max, Vector2D *result);
	};
}

#endif // FastVector2DMathHppIncluded
