/******************************************************************************/
/*                                                                            */
/*  GamepadStickAxisEvent.cpp                                                 */
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

#include <Fast/GamepadStickAxisEvent.hpp>
#include <Fast/System.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GamepadStickAxisEvent::GamepadStickAxisEvent() {
		mTimestamp = System::GetTimeAndDate();
		mGamepadID = 0;
		mStick = 0;
		mStickAxis = kGamepadStickAxisNone;
		mStickAxisValue = 0;
	}

	GamepadStickAxisEvent::GamepadStickAxisEvent(Int gamepadID, Int stick,
		GamepadStickAxis stickAxis, Int stickAxisValue)
	{
		mTimestamp = System::GetTimeAndDate();
		mGamepadID = gamepadID;
		mStick = stick;
		mStickAxis = stickAxis;
		mStickAxisValue = stickAxisValue;
	}

	Bool GamepadStickAxisEvent::operator==(const GamepadStickAxisEvent &that)
		const
	{
		if (this->mGamepadID != that.mGamepadID)
			return false;
		if (this->mStick != that.mStick)
			return false;
		if (this->mStickAxis != that.mStickAxis)
			return false;
		if (this->mStickAxisValue != that.mStickAxisValue)
			return false;
		return true;
	}

	Bool GamepadStickAxisEvent::operator!=(const GamepadStickAxisEvent &that)
		const
	{
		if (this->mGamepadID != that.mGamepadID)
			return true;
		if (this->mStick != that.mStick)
			return true;
		if (this->mStickAxis != that.mStickAxis)
			return true;
		if (this->mStickAxisValue != that.mStickAxisValue)
			return true;
		return false;
	}
}