/******************************************************************************/
/*                                                                            */
/*  GamepadDeviceInfo.cpp                                                     */
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

#include <Fast/GamepadDeviceInfo.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GamepadDeviceInfo::GamepadDeviceInfo() {
		mDeviceHandle = NULL;
	}

	GamepadDeviceInfo::GamepadDeviceInfo(JoystickDeviceHandle deviceHandle,
		const String &productName, const String &manufacturer,
		const String &guid)
	{
		mDeviceHandle = deviceHandle;
		mProductName = productName;
		mManufacturer = manufacturer;
		mGuid = guid;
	}

	Bool GamepadDeviceInfo::operator==(const GamepadDeviceInfo &that) const {
		if (this->mDeviceHandle != that.mDeviceHandle)
			return false;
		if (this->mProductName != that.mProductName)
			return false;
		if (this->mManufacturer != that.mManufacturer)
			return false;
		if (this->mGuid != that.mGuid)
			return false;
		return true;
	}

	Bool GamepadDeviceInfo::operator!=(const GamepadDeviceInfo &that) const {
		if (this->mDeviceHandle != that.mDeviceHandle)
			return true;
		if (this->mProductName != that.mProductName)
			return true;
		if (this->mManufacturer != that.mManufacturer)
			return true;
		if (this->mGuid != that.mGuid)
			return true;
		return false;
	}
}