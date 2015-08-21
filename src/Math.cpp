/******************************************************************************/
/*                                                                            */
/*  Math.cpp                                                                  */
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

#include <Fast/Math.hpp>
#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	namespace Math
	{
		Float ClampFloat(Float value, Float min, Float max) {
			if (min >= max) return value;
			if (value < min) return min;
			if (value > max) return max;
			return value;
		}

		Double ClampDouble(Double value, Double min, Double max) {
			if (min >= max) return value;
			if (value < min) return min;
			if (value > max) return max;
			return value;
		}

		Int ClampInt(Int value, Int min, Int max) {
			if (min >= max) return value;
			if (value < min) return min;
			if (value > max) return max;
			return value;
		}

		Long ClampLong(Long value, Long min, Long max) {
			if (min >= max) return value;
			if (value < min) return min;
			if (value > max) return max;
			return value;
		}
		
		Float Accelerate(Float a, Float b, Float t) {
			return Lerp(a, b, t * t);
		}
		
		Double Accelerate(Double a, Double b, Double t) {
			return Lerp(a, b, t * t);
		}

		Float Barycentric(Float a, Float b, Float c, Float t1, Float t2) {
			return (a + (t1 * (b - a)) + (t2 * (c - a)));
		}

		Double Barycentric(Double a, Double b, Double c, Double t1, Double t2)
		{
			return (a + (t1 * (b - a)) + (t2 * (c - a)));
		}

		Float CatmullRom(Float a, Float b, Float c, Float d, Float t) {
			return (0.5f * ((((2.0f * b) + ((-a + c) * t)) +
				(((((2.0f * a) - (5.0f * b)) + (4.0f * c)) - d) * t * t)) +
				((((-a + (3.0f * b)) - (3.0f * c)) + d) * t * t * t)));
		}

		Double CatmullRom(Double a, Double b, Double c, Double d, Double t) {
			return (0.5 * ((((2.0 * b) + ((-a + c) * t)) +
				(((((2.0 * a) - (5.0 * b)) + (4.0 * c)) - d) * t * t)) +
				((((-a + (3.0 * b)) - (3.0 * c)) + d) * t * t * t)));
		}

		Float Cerp(Float a, Float b, Float t) {
			return Lerp(a, b, (1.0f - (Float)cos(kFastMathPi * t)) / 2.0f);
		}

		Double Cerp(Double a, Double b, Double t) {
			return Lerp(a, b, (1.0 -
				(Double)cos((Double)kFastMathPi * t)) / 2.0);
		}

		Float Decelerate(Float a, Float b, Float t) {
			return Lerp(a, b , 1.0f - (Float)pow((1.0f - t), 2.0f));
		}

		Double Decelerate(Double a, Double b, Double t) {
			return Lerp(a, b , 1.0 - (Double)pow((1.0 - t), 2.0));
		}

		Float Hermite(Float a, Float aTangent,
			Float b, Float bTangent, Float t)
		{
			return ((((a * (((2.0f * t*t*t) - (3.0f * t*t)) + 1.0f)) +
				(b * ((-2.0f * t*t*t) + (3.0f * t*t)))) +
				(aTangent * ((t*t*t - (2.0f * t*t)) + t))) +
				(bTangent * (t*t*t - t*t)));
		}

		Double Hermite(Double a, Double aTangent,
			Double b, Double bTangent, Double t)
		{
			return ((((a * (((2.0 * t*t*t) - (3.0 * t*t)) + 1.0)) +
				(b * ((-2.0 * t*t*t) + (3.0 * t*t)))) +
				(aTangent * ((t*t*t - (2.0 * t*t)) + t))) +
				(bTangent * (t*t*t - t*t)));
		}

		Float Lerp(Float a, Float b, Float t) {
			return ((a * (1.0f - t)) + (b * t));
		}

		Double Lerp(Double a, Double b, Double t) {
			return ((a * (1.0 - t)) + (b * t));
		}

		Float SmoothStep(Float a, Float b, Float t) {
			return Lerp(a, b, (t * t) * (3.0f - (2.0f * t)));
		}

		Double SmoothStep(Double a, Double b, Double t) {
			return Lerp(a, b, (t * t) * (3.0 - (2.0 * t)));
		}

		Bool IsSimilar(Float a, Float b, Float error) {
			return (fabs(a - b) < error);
		}

		Bool IsSimilar(Double a, Double b, Double error) {
			return (fabs(a - b) < error);
		}
		
		Float Ln(Float x) {
			return log(x);
		}
		
		Double Ln(Double x) {
			return log(x);
		}
		
		Float Log(Float base, Float x) {
			return (Ln(x) / Ln(base));
		}
		
		Double Log(Double base, Double x) {
			return (Ln(x) / Ln(base));
		}
		
		Float Remainder(Float numerator, Float denominator) {
			return ((numerator / denominator) - floor(numerator / denominator));
		}
		
		Double Remainder(Double numerator, Double denominator) {
			return ((numerator / denominator) - floor(numerator / denominator));
		}
		
		Float Round(Float x) {
			if ((x - floor(x)) < 0.5f) return floor(x);
			else return ceil(x);
		}
		
		Double Round(Double x) {
			if ((x - floor(x)) < 0.5) return floor(x);
			else return ceil(x);
		}

		Float ToDegrees(Float radians) {
			return (radians * (180.0f / kFastMathPi));
		}

		Double ToDegrees(Double radians) {
			return (radians * (180.0 / (Double)kFastMathPi));
		}
		
		Float ToRadians(Float degrees) {
			return (degrees * (kFastMathPi / 180.0f));
		}
		
		Double ToRadians(Double degrees) {
			return (degrees * ((Double)kFastMathPi / 180.0));
		}
		
		Float WrapFloat(Float value, Float min, Float max) {
			if (min >= max) return value;
			Float total = max - min;
			while (value > max)
				value -= total;
			while (value < min)
				value += total;
			return value;
		}
		
		Double WrapDouble(Double value, Double min, Double max) {
			if (min >= max) return value;
			Double total = max - min;
			while (value > max)
				value -= total;
			while (value < min)
				value += total;
			return value;
		}
	
		Int WrapInt(Int value, Int min, Int max) {
			if (min >= max) return value;
			Int total = max - min;
			while (value > max)
				value -= total;
			while (value < min)
				value += total;
			return value;
		}
		
		Long WrapLong(Long value, Long min, Long max) {
			if (min >= max) return value;
			Long total = max - min;
			while (value > max)
				value -= total;
			while (value < min)
				value += total;
			return value;
		}
	}
}
