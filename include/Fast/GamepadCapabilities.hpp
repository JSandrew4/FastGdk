/******************************************************************************/
/*                                                                            */
/*  GamepadCapabilities.hpp                                                   */
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

#ifndef FastGamepadCapabilitiesHppIncluded
#define FastGamepadCapabilitiesHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class FastApi GamepadCapabilities
	{
	public:
		Int	mNumRegularButtons;
		Int mNumDirectionalPads;
		Int	mNumAxes;
		// Constructors
		GamepadCapabilities();
		GamepadCapabilities(Int numRegularButtons,
			Int numDirectionalPads, Int numAxes);
		// Operators
		Bool	operator==(const GamepadCapabilities &that) const;
		Bool	operator!=(const GamepadCapabilities &that) const;
	};
}

#endif // FastGamepadCapabilitiesHppIncluded