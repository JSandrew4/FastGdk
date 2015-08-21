/******************************************************************************/
/*                                                                            */
/*  SpriteAnimation.hpp                                                       */
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

#ifndef FastSpriteAnimationHppIncluded
#define FastSpriteAnimationHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>
#include <Fast/SpriteAnimationFrame.hpp>

namespace Choas
{
	class FastApi SpriteAnimation
	{
	private:
		String						mName;
		Array<SpriteAnimationFrame>	mFrames;
	public:
		// (Con/De)structors
		SpriteAnimation();
		~SpriteAnimation();
		// Getters
		const String&				GetName() const;
		Int							GetNumFrames() const;
		SpriteAnimationFrame*		GetFrame(Int frame);
		const SpriteAnimationFrame&	GetFrame(Int frame) const;
		// Setters
		void	SetName(const String &name);
		void	AppendFrame(const SpriteAnimationFrame &frame);
		void	PrependFrame(const SpriteAnimationFrame &frame);
		void	InsertFrame(Int index, const SpriteAnimationFrame &frame);
		void	ReplaceFrame(Int index, const SpriteAnimationFrame &frame);
		void	RemoveFrame(Int index);
		// Operators
		SpriteAnimation&	operator= (const SpriteAnimation &that);
		Bool				operator==(const SpriteAnimation &that);
		Bool				operator!=(const SpriteAnimation &that);
	};
}

#endif // FastSpriteAnimationHppIncluded
