/******************************************************************************/
/*                                                                            */
/*  GamepadDeviceInfo.hpp                                                     */
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

#ifndef FastGamepadDeviceInfoHppIncluded
#define FastGamepadDeviceInfoHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>

namespace Fast
{
	class FastApi GamepadDeviceInfo
	{
	public:
		JoystickDeviceHandle	mDeviceHandle;
		String					mProductName;
		String					mManufacturer;
		String					mGuid;
		// Constructors
		GamepadDeviceInfo();
		GamepadDeviceInfo(JoystickDeviceHandle deviceHandle,
			const String &productName, const String &manufacturer,
			const String &guid);
		// Operators
		Bool	operator==(const GamepadDeviceInfo &that) const;
		Bool	operator!=(const GamepadDeviceInfo &that) const;
	};
}

#endif // FastGamepadDeviceInfoHppIncluded