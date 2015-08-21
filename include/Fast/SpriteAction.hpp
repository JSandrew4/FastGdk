/******************************************************************************/
/*                                                                            */
/*  SpriteAction.hpp                                                          */
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

#ifndef FastSpriteActionHppIncluded
#define FastSpriteActionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>
#include <Fast/SpriteFrame.hpp>

namespace Fast
{
	class FastApi SpriteAction
	{
	private:
		String				mName;
		Array<SpriteFrame>	mFrames;
	public:
		// Constructors
		SpriteAction();
		SpriteAction(const SpriteAction &that);
		// Getters
		const String&		GetName() const;
		Int					GetNumFrames() const;
		SpriteFrame*		GetFrame(Int index);
		const SpriteFrame&	GetFrame(Int index) const;
		Int					GetFrameIndex(const String &name) const;
		// Setters
		void	SetName(const String &name);
		// Modifiers
		void	AddFrame(const SpriteFrame &frame);
		void	InsertFrame(const SpriteFrame &frame, Int index);
		void	ReplaceFrame(const SpriteFrame &frame, Int index);
		void	EraseFrame(Int index);
		void	ClearFrames();
		// Operators
		SpriteAction&	operator= (const SpriteAction &that);
		Bool			operator==(const SpriteAction &that) const;
		Bool			operator!=(const SpriteAction &that) const;
	};

	template class FastApi Array<SpriteAction>;
}

#endif // FastSpriteActionHppIncluded