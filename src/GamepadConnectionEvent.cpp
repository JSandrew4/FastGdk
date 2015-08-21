/******************************************************************************/
/*                                                                            */
/*  GamepadConnectionEvent.cpp                                                */
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

#include <Fast/GamepadConnectionEvent.hpp>
#include <Fast/System.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GamepadConnectionEvent::GamepadConnectionEvent() {
		mTimestamp = System::GetTimeAndDate();
		mGamepadID = 0;
		mIsConnected = false;
	}

	GamepadConnectionEvent::GamepadConnectionEvent(
		Int gamepadID, Bool isConnected)
	{
		mTimestamp = System::GetTimeAndDate();
		mGamepadID = gamepadID;
		mIsConnected = isConnected;
	}

	Bool GamepadConnectionEvent::operator==(const GamepadConnectionEvent &that)
		const
	{
		if (this->mGamepadID!= that.mGamepadID)
			return false;
		if (this->mIsConnected != that.mIsConnected)
			return false;
		return true;
	}

	Bool GamepadConnectionEvent::operator!=(const GamepadConnectionEvent &that)
		const
	{
		if (this->mGamepadID!= that.mGamepadID)
			return true;
		if (this->mIsConnected != that.mIsConnected)
			return true;
		return false;
	}
}