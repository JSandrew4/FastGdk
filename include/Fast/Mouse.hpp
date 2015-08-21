/******************************************************************************/
/*                                                                            */
/*  Mouse.hpp                                                                 */
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

#ifndef FastMouseHppIncluded
#define FastMouseHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Point.hpp>
#include <Fast/MouseButton.hpp>

#define kFastNumMouseButtons	3

namespace Fast
{
	class FastApi Mouse
	{
	private:
		Bool	mButtons[kFastNumMouseButtons];
		Point	mMoveDelta;
		Int		mVerticalScrollWheelDelta;
		Int		mHorizontalScrollWheelDelta;
	public:
		// (Con/De)structors
		Mouse();
		Mouse(const Mouse &that);
		~Mouse();
		// Get functions
		Bool			IsButtonDown(MouseButton mouseButton) const;
		Bool			IsButtonUp(MouseButton mouseButton) const;
		const Point&	GetMoveDelta() const;
		Int				GetVerticalScrollWheelDelta() const;
		Int				GetHorizontalScrollWheelDelta() const;
		// Set functions
		void	PressButton(MouseButton mouseButton);
		void	ReleaseButton(MouseButton mouseButton);
		void	Move(const Point &point);
		void	Move(Int x, Int y);
		void	ResetMoveDelta();
		void	ScrollVertically(Int delta);
		void	ScrollHorizontally(Int delta);
		void	ResetVerticalScrollWheelDelta();
		void	ResetHorizontalScrollWheelDelta();
		// Operators
		Mouse&	operator= (const Mouse &that);
		Bool	operator==(const Mouse &that);
		Bool	operator!=(const Mouse &that);
	};
}

#endif // FastMouseHppIncluded