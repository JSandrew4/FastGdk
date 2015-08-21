/******************************************************************************/
/*                                                                            */
/*  System.hpp                                                                */
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

#ifndef FastSystemHppIncluded
#define FastSystemHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Platform.hpp>
#include <Fast/Clock.hpp>

#define kFastMaxPCNameLength	100
#define kFastMaxUserNameLength	100

namespace Fast
{
	namespace System
	{
		FastApi Platform	GetPlatform();
		FastApi Clock		GetTimeAndDate();
		FastApi String		GetCurrentUserName();
		FastApi String		GetPCName();
		FastApi Bool		IsBigEndian();
		FastApi Bool		IsLittleEndian();
		FastApi Short		SwapBytes(Short var);
		FastApi UShort		SwapBytes(UShort var);
		FastApi Int		SwapBytes(Int var);
		FastApi UInt		SwapBytes(UInt var);
		FastApi Long		SwapBytes(Long var);
		FastApi ULong		SwapBytes(ULong var);
		FastApi Float		SwapBytes(Float var);
		FastApi Double		SwapBytes(Double var);
	};
}

#endif // FastSystemHppIncluded
