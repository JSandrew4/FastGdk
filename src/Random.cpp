/******************************************************************************/
/*                                                                            */
/*  Random.cpp                                                                */
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

#include <Fast/Random.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Random::Random() {
		mSeed = kFastRandomSeedA;
		mSeed2 = kFastRandomSeedB;
	}

	Random::Random(const Random &that) {
		this->mSeed = that.mSeed;
		this->mSeed2 = that.mSeed2;
	}

	Random::Random(UInt seed) {
		mSeed = seed;
		mSeed2 = kFastRandomSeedB;
	}

	void Random::SetSeed(UInt seed) {
		mSeed = seed;
		mSeed2 = kFastRandomSeedB;
	}

	UInt Random::GetSeed() const {
		return mSeed;
	}

	UInt Random::NextRandom() {
		mSeed2 = 36969 * (mSeed2 & 65535) + (mSeed2 >> 16);
		mSeed = 18000 * (mSeed & 65535) + (mSeed >> 16);
		UInt ret = (mSeed2 << 16) + mSeed;
		return ret;
	}
	
	Byte Random::NextByte(Byte min, Byte max) {
		if (min >= max) return 0;
		Byte ret =
			(Byte)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}
	
	UByte Random::NextUByte(UByte min, UByte max) {
		if (min >= max) return 0;
		UByte ret =
			(UByte)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}
	
	UShort Random::NextUShort(UShort min, UShort max) {
		if (min >= max) return 0;
		UShort ret =
			(UShort)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}
	
	Short Random::NextShort(Short min, Short max) {
		if (min >= max) return 0;
		Short ret =
			(Short)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}
	
	UInt Random::NextUInt(UInt min, UInt max) {
		if (min >= max || max > kFastRandomMax) return 0;
		UInt ret =
			(UInt)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}

	Int Random::NextInt(Int min, Int max) {
		if (min >= max || max > kFastRandomMax) return 0;
		Int ret =
			(Int)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}

	ULong Random::NextULong(ULong min, ULong max) {
		if (min >= max || max > kFastRandomMax) return 0;
		ULong ret =
			(ULong)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}

	Long Random::NextLong(Long min, Long max) {
		if (min >= max || max > kFastRandomMax) return 0;
		Long ret =
			(Long)((NextRandom() / (kFastRandomMax / (max+1 - min))) + min);
		return ret;
	}
	
	Float Random::NextFloat(Float min, Float max) {
		if (min >= max || max > (Float)kFastRandomMax) return 0.0f;
		Float ret = ((max - min) * ((Float)NextRandom() /
			(Float)kFastRandomMax) + min);
		return ret;
	}
	
	Double Random::NextDouble(Double min, Double max) {
		if (min >= max || max > (Double)kFastRandomMax) return 0.0;
		Double ret = ((max - min) * ((Double)NextRandom() /
			(Double)kFastRandomMax) + min);
		return ret;
	}

	Random& Random::operator=(const Random &that) {
		this->mSeed = that.mSeed;
		this->mSeed2 = that.mSeed2;
		return * this;
	}

	Bool Random::operator==(const Random &that) const {
		return (this->mSeed == that.mSeed && this->mSeed2 == that.mSeed2);
	}

	Bool Random::operator!=(const Random &that) const {
		return (this->mSeed != that.mSeed || this->mSeed2 != that.mSeed2);
	}
}
