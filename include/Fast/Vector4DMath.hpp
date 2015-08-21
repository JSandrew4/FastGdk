/******************************************************************************/
/*                                                                            */
/*  Vector4DMath.hpp                                                          */
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

#ifndef FastVector4DMathHppIncluded
#define FastVector4DMathHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector4D.hpp>

namespace Fast
{
	class Matrix;
	class Quaternion;
	class Vector2D;
	class Vector3D;

	namespace Vector4DMath
	{
		FastApi Float		Distance(const Vector4D &a, const Vector4D &b);
		FastApi Float		DistanceSquared(const Vector4D &a,
								const Vector4D &b);
		FastApi Float		Dot(const Vector4D &a, const Vector4D &b);
		FastApi Vector4D	Normalize(const Vector4D &v);
		FastApi void		Normalize(const Vector4D &v, Vector4D *result);
		FastApi Vector4D	Reflect(const Vector4D &v, const Vector4D &normal);
		FastApi void		Reflect(const Vector4D &v,
								const Vector4D &normal, Vector4D *result);
		FastApi Bool		IsSimilar(const Vector4D &a,
								const Vector4D &b, Float error);
		FastApi Vector4D	Clamp(const Vector4D &value,
								const Vector4D &min, const Vector4D &max);
		FastApi void		Clamp(const Vector4D &value, const Vector4D &min,
								const Vector4D &max, Vector4D *result);
		FastApi Vector4D	Accelerate(const Vector4D &a,
								const Vector4D &b, Float t);
		FastApi void		Accelerate(const Vector4D &a,
								const Vector4D &b, Float t, Vector4D *result);
		FastApi Vector4D	Barycentric(const Vector4D &a, const Vector4D &b,
								const Vector4D &c, Float t1, Float t2);
		FastApi void		Barycentric(const Vector4D &a, const Vector4D &b,
								const Vector4D &c, Float t1,
								Float t2, Vector4D *result);
		FastApi Vector4D	CatmullRom(const Vector4D &a, const Vector4D &b,
								const Vector4D &c, const Vector4D &d, Float t);
		FastApi void		CatmullRom(const Vector4D &a, const Vector4D &b,
								const Vector4D &c, const Vector4D &d,
								Float t, Vector4D *result);
		FastApi Vector4D	Cerp(const Vector4D &a, const Vector4D &b, Float t);
		FastApi void		Cerp(const Vector4D &a,
								const Vector4D &b, Float t, Vector4D *result);
		FastApi Vector4D	Decelerate(const Vector4D &a,
								const Vector4D &b, Float t);
		FastApi void		Decelerate(const Vector4D &a,
								const Vector4D &b, Float t, Vector4D *result);
		FastApi Vector4D	Hermite(const Vector4D &a, const Vector4D &aTangent,
								const Vector4D &b, const Vector4D &bTangent,
								Float t);
		FastApi void		Hermite(const Vector4D &a, const Vector4D &aTangent,
								const Vector4D &b, const Vector4D &bTangent,
								Float t, Vector4D *result);
		FastApi Vector4D	Lerp(const Vector4D &a, const Vector4D &b, Float t);
		FastApi void		Lerp(const Vector4D &a, const Vector4D &b,
								Float t, Vector4D *result);
		FastApi Vector4D	Nlerp(const Vector4D &a,
								const Vector4D &b, Float t);
		FastApi void		Nlerp(const Vector4D &a, const Vector4D &b,
								Float t, Vector4D *result);
		FastApi Vector4D	Slerp(const Vector4D &a,
								const Vector4D &b, Float t);
		FastApi void		Slerp(const Vector4D &a, const Vector4D &b,
								Float t, Vector4D *result);
		FastApi Vector4D	Transform(const Vector4D &position,
								const Matrix &m);
		FastApi void		Transform(const Vector4D &position,
								const Matrix &m, Vector4D *result);
		FastApi Vector4D	Transform(const Vector4D &value,
								const Quaternion &rotation);
		FastApi void		Transform(const Vector4D &value,
								const Quaternion &rotation, Vector4D *result);
		FastApi Vector4D	TransformNormal(const Vector4D &normal,
								const Matrix &m);
		FastApi void		TransformNormal(const Vector4D &normal,
								const Matrix &m, Vector4D *result);
		FastApi Vector4D	SmoothStep(const Vector4D &a,
								const Vector4D &b, Float t);
		FastApi void		SmoothStep(const Vector4D &a, const Vector4D &b,
								Float t, Vector4D *result);
		FastApi Vector4D	Wrap(const Vector4D &value,
								const Vector4D &min, const Vector4D &max);
		FastApi void		Wrap(const Vector4D &value, const Vector4D &min,
								const Vector4D &max, Vector4D *result);
	}
}

#endif // FastVector4DMathHppIncluded
