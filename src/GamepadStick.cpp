/******************************************************************************/
/*                                                                            */
/*  GamepadStick.cpp                                                          */
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

#include <Fast/GamepadStick.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GamepadStick::GamepadStick() { }

	GamepadStick::GamepadStick(const GamepadStick &that) {
		*this = that;
	}

	GamepadStick& GamepadStick::operator= (const GamepadStick &that) {
		this->mXAxis = that.mXAxis;
		this->mYAxis = that.mYAxis;
		this->mOtherAxis = that.mOtherAxis;
		return *this;
	}

	Bool GamepadStick::operator==(const GamepadStick &that) const {
		if (this->mXAxis != that.mXAxis)
			return false;
		if (this->mYAxis != that.mYAxis)
			return false;
		if (this->mOtherAxis != that.mOtherAxis)
			return false;
		return true;
	}

	Bool GamepadStick::operator!=(const GamepadStick &that) const {
		if (this->mXAxis != that.mXAxis)
			return true;
		if (this->mYAxis != that.mYAxis)
			return true;
		if (this->mOtherAxis != that.mOtherAxis)
			return true;
		return false;
	}
}