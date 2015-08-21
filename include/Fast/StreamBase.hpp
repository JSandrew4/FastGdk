/******************************************************************************/
/*                                                                            */
/*  StreamBase.hpp                                                            */
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

#ifndef FastStreamBaseHppIncluded
#define FastStreamBaseHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/String.hpp>

namespace Fast
{
	class FastApi StreamBase
	{
	protected:
		Bool	mIsEndianAware;
		String	mName;
	public:
		virtual void		Close()		= 0;
		virtual void		Flush()		= 0;
		virtual Bool		IsOpen()	= 0;
		virtual Long		GetSize()	= 0;
		virtual ErrorType	GetError()	= 0;
		virtual void		SeekTo(Long seekPosition) = 0;
		virtual Long		GetSeekPosition() = 0;
		const String&		GetName() const;
		void				SetEndianAware(Bool isEndianAware);
		Bool				IsEndianAware() const;
	};
}

#endif // FastStreamBaseHppIncluded
