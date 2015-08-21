/******************************************************************************/
/*                                                                            */
/*  MouseMoveEvent.cpp                                                        */
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

#include <Fast/MouseMoveEvent.hpp>
#include <Fast/System.hpp>

#include "Undefs.hpp"

namespace Fast
{
	MouseMoveEvent::MouseMoveEvent() {
		mTimestamp = System::GetTimeAndDate();
	}

	MouseMoveEvent::MouseMoveEvent(const Point &position) {
		mPosition = position;
		mTimestamp = System::GetTimeAndDate();
	}

	Bool MouseMoveEvent::operator==(const MouseMoveEvent &that) const {
		if (this->mPosition != that.mPosition)
			return false;
		return true;
	}

	Bool MouseMoveEvent::operator!=(const MouseMoveEvent &that) const {
		if (this->mPosition != that.mPosition)
			return true;
		return false;
	}
}