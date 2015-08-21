/******************************************************************************/
/*                                                                            */
/*  MouseButtonEvent.hpp                                                      */
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

#ifndef FastMouseButtonEventHppIncluded
#define FastMouseButtonEventHppIncluded

#include <Fast/Types.hpp>
#include <Fast/MouseButton.hpp>
#include <Fast/MouseButtonAction.hpp>
#include <Fast/EventBase.hpp>

namespace Fast
{
	class FastApi MouseButtonEvent : public EventBase
	{
	public:
		MouseButton			mButton;
		MouseButtonAction	mAction;
		// Constructors
		MouseButtonEvent();
		MouseButtonEvent(MouseButton button, MouseButtonAction action);
		// Operators
		Bool	operator==(const MouseButtonEvent &that) const;
		Bool	operator!=(const MouseButtonEvent &that) const;
	};
}

#endif // FastMouseButtonEventHppIncluded