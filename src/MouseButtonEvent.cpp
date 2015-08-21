/******************************************************************************/
/*                                                                            */
/*  MouseButtonEvent.cpp                                                      */
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

#include <Fast/MouseButtonEvent.hpp>
#include <Fast/System.hpp>

#include "Undefs.hpp"

namespace Fast
{
	MouseButtonEvent::MouseButtonEvent() {
		mButton = kMouseButtonNone;
		mAction = kMouseButtonActionNone;
		mTimestamp = System::GetTimeAndDate();
	}

	MouseButtonEvent::MouseButtonEvent(MouseButton button, MouseButtonAction action) {
		mButton = button;
		mAction = action;
		mTimestamp = System::GetTimeAndDate();
	}

	Bool MouseButtonEvent::operator==(const MouseButtonEvent &that) const {
		if (this->mAction != that.mAction)
			return false;
		if (this->mButton != that.mButton)
			return false;
		return true;
	}

	Bool MouseButtonEvent::operator!=(const MouseButtonEvent &that) const {
		if (this->mAction != that.mAction)
			return true;
		if (this->mButton != that.mButton)
			return true;
		return false;
	}
}