/******************************************************************************/
/*                                                                            */
/*  KeyEvent.hpp                                                              */
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

#ifndef FastKeyEventHppIncluded
#define FastKeyEventHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Clock.hpp>
#include <Fast/String.hpp>
#include <Fast/KeyAction.hpp>

namespace Fast
{
	class FastApi KeyEvent
	{
	public:
		Clock		mTimestamp;
		String		mKey;
		KeyAction	mAction;
		// Constructors
		KeyEvent();
		KeyEvent(const String &key, KeyAction action);
		// Operators
		Bool	operator==(const KeyEvent &that) const;
		Bool	operator!=(const KeyEvent &that) const;
	};
}

#endif // FastKeyEventHppIncluded