/******************************************************************************/
/*                                                                            */
/*  Checksum.hpp                                                              */
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

#ifndef FastChecksumHppIncluded
#define FastChecksumHppIncluded

#include <Fast/Types.hpp>

#define kFastChecksumSize 32

namespace Fast
{
	class FastApi Checksum
	{
	private:
		Bool	mIsEmpty;
	public:
		// Members
		Byte mSum[kFastChecksumSize];
		// (Con/De)structors
		Checksum();
		Checksum(const Checksum &that);
		Checksum(const Byte *data, Int size);
		// Functions
		void	Calculate(const Byte *data, Int size);
		void	Clear();
		Bool	IsEmpty() const;
		// Operators
		Checksum&	operator= (const Checksum &that);
		Bool		operator==(const Checksum &that) const;
		Bool		operator!=(const Checksum &that) const;
	};
}

#endif // FastChecksumHppIncluded
