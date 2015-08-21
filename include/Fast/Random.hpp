/******************************************************************************/
/*                                                                            */
/*  Random.hpp                                                                */
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

#ifndef FastRandomHppIncluded
#define FastRandomHppIncluded

#include <Fast/Types.hpp>

#define kFastRandomSeedA	521288629
#define kFastRandomSeedB	362436069
#define kFastRandomMax		0xffffffff

namespace Fast
{
	class FastApi Random
	{
	private:
		// Members
		UInt		mSeed, mSeed2;
	public:
		// (Con/De)structors
		Random();
		Random(const Random &that);
		Random(UInt seed);
		// Seed functions
		UInt	GetSeed() const;
		void	SetSeed(UInt seed);
		// Random functions
		UInt	NextRandom();
		Byte	NextByte(Byte min, Byte max);
		UByte	NextUByte(UByte min, UByte max);
		UShort	NextUShort(UShort min, UShort max);
		Short	NextShort(Short min, Short max);
		UInt	NextUInt(UInt min, UInt max);
		Int		NextInt(Int min, Int max);
		ULong	NextULong(ULong min, ULong max);
		Long	NextLong(Long min, Long max);
		Float	NextFloat(Float min, Float max);
		Double	NextDouble(Double min, Double max);
		// Assignment operator
		Random&	operator= (const Random &that);
		Bool	operator==(const Random &that) const;
		Bool	operator!=(const Random &that) const;
	};
}

#endif // FastRandomHppIncluded
