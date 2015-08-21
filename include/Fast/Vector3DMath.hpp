/******************************************************************************/
/*                                                                            */
/*  Vector3DMath.hpp                                                          */
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

#ifndef FastVector3DMathHppIncluded
#define FastVector3DMathHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector3D.hpp>

namespace Fast
{
	class Matrix;
	class Quaternion;
	class Vector2D;

	namespace Vector3DMath
	{
		FastApi Float		Distance(const Vector3D &a, const Vector3D &b);
		FastApi Float		DistanceSquared(const Vector3D &a,
								const Vector3D &b);
		FastApi Float		Dot(const Vector3D &a, const Vector3D &b);
		FastApi Vector3D	Cross(const Vector3D &a, const Vector3D &b);
		FastApi void		Cross(const Vector3D &a, const Vector3D &b,
								Vector3D *result);
		FastApi Vector3D	Normalize(const Vector3D &v);
		FastApi void		Normalize(const Vector3D &v, Vector3D *result);
		FastApi Vector3D	Reflect(const Vector3D &v, const Vector3D &normal);
		FastApi void		Reflect(const Vector3D &v, const Vector3D &normal,
								Vector3D *result);
		FastApi Bool		IsSimilar(const Vector3D &a,
								const Vector3D &b, Float error);
		FastApi Vector3D	Clamp(const Vector3D &value,
								const Vector3D &min, const Vector3D &max);
		FastApi void		Clamp(const Vector3D &value, const Vector3D &min,
								const Vector3D &max, Vector3D *result);
		FastApi Vector3D	Accelerate(const Vector3D &a,
								const Vector3D &b, Float t);
		FastApi void		Accelerate(const Vector3D &a, const Vector3D &b,
								Float t, Vector3D *result);
		FastApi Vector3D	Barycentric(const Vector3D &a, const Vector3D &b,
								const Vector3D &c, Float t1, Float t2);
		FastApi void		Barycentric(const Vector3D &a, const Vector3D &b,
								const Vector3D &c, Float t1, Float t2,
								Vector3D *result);
		FastApi Vector3D	CatmullRom(const Vector3D &a, const Vector3D &b,
								const Vector3D &c, const Vector3D &d, Float t);
		FastApi void		CatmullRom(const Vector3D &a, const Vector3D &b,
								const Vector3D &c, const Vector3D &d,
								Float t, Vector3D *result);
		FastApi Vector3D	Cerp(const Vector3D &a, const Vector3D &b, Float t);
		FastApi void		Cerp(const Vector3D &a, const Vector3D &b,
								Float t, Vector3D *result);
		FastApi Vector3D	Decelerate(const Vector3D &a,
								const Vector3D &b, Float t);
		FastApi void		Decelerate(const Vector3D &a, const Vector3D &b,
								Float t, Vector3D *result);
		FastApi Vector3D	Hermite(const Vector3D &a, const Vector3D &aTangent,
								const Vector3D &b, const Vector3D &bTangent,
								Float t);
		FastApi void		Hermite(const Vector3D &a, const Vector3D &aTangent,
								const Vector3D &b, const Vector3D &bTangent,
								Float t, Vector3D *result);
		FastApi Vector3D	Lerp(const Vector3D &a,
								const Vector3D &b, Float t);
		FastApi void		Lerp(const Vector3D &a, const Vector3D &b,
								Float t, Vector3D *result);
		FastApi Vector3D	Nlerp(const Vector3D &a,
								const Vector3D &b, Float t);
		FastApi void		Nlerp(const Vector3D &a, const Vector3D &b,
								Float t, Vector3D *result);
		FastApi Vector3D	Slerp(const Vector3D &a,
								const Vector3D &b, Float t);
		FastApi void		Slerp(const Vector3D &a, const Vector3D &b,
								Float t, Vector3D *result);
		FastApi Vector3D	SmoothStep(const Vector3D &a,
								const Vector3D &b, Float t);
		FastApi void		SmoothStep(const Vector3D &a, const Vector3D &b,
								Float t, Vector3D *result);
		FastApi Vector3D	Transform(const Vector3D & aPosition,
								const Matrix &m);
		FastApi void		Transform(const Vector3D & aPosition,
								const Matrix &m, Vector3D *result);
		FastApi Vector3D	Transform(const Vector3D &value,
								const Quaternion & rotation);
		FastApi void		Transform(const Vector3D &value,
								const Quaternion & rotation, Vector3D *result);
		FastApi Vector3D	TransformNormal(const Vector3D &normal,
								const Matrix &m);
		FastApi void		TransformNormal(const Vector3D &normal,
								const Matrix &m, Vector3D *result);
		FastApi Vector3D	Wrap(const Vector3D &value,
								const Vector3D &min, const Vector3D &max);
		FastApi void		Wrap(const Vector3D &value, const Vector3D &min,
								const Vector3D &max, Vector3D *result);
	};
}

#endif // FastVector3DMathHppIncluded
