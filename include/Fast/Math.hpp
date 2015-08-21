/******************************************************************************/
/*                                                                            */
/*  Math.hpp                                                                  */
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

#ifndef FastMathHppIncluded
#define FastMathHppIncluded

#include <Fast/Types.hpp>

#define kFastMathPi		3.141592f
#define kFastMathTwoPi		6.283185f
#define kFastMathPiOver2	1.570796f
#define kFastMathPiOver4	0.785398f
#define kFastMathE			2.718281f

namespace Fast
{
	namespace Math
	{
		FastApi Float	Accelerate(Float  a, Float  b, Float  t);
		FastApi Double	Accelerate(Double a, Double b, Double t);

		FastApi Float	Barycentric(Float  a, Float  b, Float  c,
							Float  t1, Float  t2);
		FastApi Double	Barycentric(Double a, Double b, Double c,
							Double t1, Double t2);

		FastApi Float	CatmullRom(Float  a, Float  b, Float  c,
							Float  aD, Float  t);
		FastApi Double	CatmullRom(Double a, Double b, Double c,
							Double aD, Double t);

		FastApi Float	Cerp(Float  a, Float  b, Float  t);
		FastApi Double	Cerp(Double a, Double b, Double t);
		
		FastApi Float	ClampFloat( Float  x, Float  min, Float  max);
		FastApi Double	ClampDouble(Double x, Double min, Double max);
		FastApi Int	ClampInt(   Int    x, Int    min, Int    max);
		FastApi Long	ClampLong(  Long   x, Long   min, Long   max);
		
		FastApi Float	Decelerate(Float  a, Float  b, Float  t);
		FastApi Double	Decelerate(Double a, Double b, Double t);

		FastApi Float	Hermite(Float  a, Float  aTangent, Float  b,
							Float  bTangent, Float  t);
		FastApi Double	Hermite(Double a, Double aTangent, Double b,
							Double bTangent, Double t);

		FastApi Bool	IsSimilar(Float  a, Float  b, Float  error);
		FastApi Bool	IsSimilar(Double a, Double b, Double error);

		FastApi Float	Lerp(Float  a, Float  b, Float  t);
		FastApi Double	Lerp(Double a, Double b, Double t);

		FastApi Float	Ln(Float  x);
		FastApi Double	Ln(Double x);

		FastApi Float	Log(Float  base, Float  x);
		FastApi Double	Log(Double base, Double x);

		FastApi Float	Remainder(Float  numerator, Float  denominator);
		FastApi Double	Remainder(Double numerator, Double denominator);

		FastApi Float	Round(Float  x);
		FastApi Double	Round(Double x);

		FastApi Float	SmoothStep(Float  a, Float  b, Float  t);
		FastApi Double	SmoothStep(Double a, Double b, Double t);

		FastApi Float	ToDegrees(Float  radians);
		FastApi Double	ToDegrees(Double radians);

		FastApi Float	ToRadians(Float  degrees);
		FastApi Double	ToRadians(Double degrees);

		FastApi Float	WrapFloat( Float  x, Float  min, Float  max);
		FastApi Double	WrapDouble(Double x, Double min, Double max);
		FastApi Int	WrapInt(   Int    x, Int    min, Int    max);
		FastApi Long	WrapLong(  Long   x, Long   min, Long   max);
	};
}

#endif // FastMathHppIncluded
