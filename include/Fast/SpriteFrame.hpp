/******************************************************************************/
/*                                                                            */
/*  SpriteFrame.hpp                                                           */
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

#ifndef FastSpriteFrameHppIncluded
#define FastSpriteFrameHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>

namespace Fast
{
	class FastApi SpriteFrame
	{
	private:
		String	mName;
		Int		mFrameConfigIndex;
		Long	mDelayMicroseconds;
		Int		mInterpType;
	public:
		// Constructors
		SpriteFrame();
		SpriteFrame(const SpriteFrame &that);
		SpriteFrame(const String &name, Int frameConfigIndex,
			Int delayMicroseconds, Int interpType);
		// Getters
		const String&	GetName() const;
		Int				GetFrameConfigIndex() const;
		Long			GetDelayMicroseconds() const;
		Int				GetInterpType() const;
		// Setters
		void	SetName(const String &name);
		void	SetFrameConfigIndex(Int frameConfigIndex);
		void	SetDelayMicroseconds(Long delayMicroseconds);
		void	SetInterpType(Int interpType);
		// Operators
		SpriteFrame&	operator= (const SpriteFrame &that);
		Bool			operator==(const SpriteFrame &that) const;
		Bool			operator!=(const SpriteFrame &that) const;
	};
}

#endif // FastSpriteFrameHppIncluded
