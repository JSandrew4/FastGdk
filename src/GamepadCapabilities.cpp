/******************************************************************************/
/*                                                                            */
/*  GamepadCapabilities.cpp                                                   */
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

#include <Fast/GamepadCapabilities.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GamepadCapabilities::GamepadCapabilities() {
		mNumAxes = 0;
		mNumDirectionalPads = 0;
		mNumRegularButtons = 0;
	}

	GamepadCapabilities::GamepadCapabilities(Int numRegularButtons,
		Int numDirectionalPads, Int numAxes)
	{
		mNumAxes = numAxes;
		mNumDirectionalPads = numDirectionalPads;
		mNumRegularButtons = numRegularButtons;
	}

	Bool GamepadCapabilities::operator==(const GamepadCapabilities &that) const {
		if (this->mNumAxes != that.mNumAxes)
			return false;
		if (this->mNumDirectionalPads != that.mNumDirectionalPads)
			return false;
		if (this->mNumRegularButtons != that.mNumRegularButtons)
			return false;
		return true;
	}

	Bool GamepadCapabilities::operator!=(const GamepadCapabilities &that) const {
		if (this->mNumAxes != that.mNumAxes)
			return true;
		if (this->mNumDirectionalPads != that.mNumDirectionalPads)
			return true;
		if (this->mNumRegularButtons != that.mNumRegularButtons)
			return true;
		return false;
	}
}