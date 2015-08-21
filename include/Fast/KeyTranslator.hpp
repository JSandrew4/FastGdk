/******************************************************************************/
/*                                                                            */
/*  KeyTranslator.hpp                                                         */
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

#ifndef FastKeyTranslatorHppIncluded
#define FastKeyTranslatorHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class FastApi KeyTranslator
	{
	private:
		const Char	*mKeyMap[0xff];
		// Hide these functions. No reason to copy
		KeyTranslator(const KeyTranslator &that) { }
		KeyTranslator& operator=(const KeyTranslator &that)
			{ return *this; }
	public:
		KeyTranslator();
		const Char*	GetKey(Int keyCode);
	};
}

#endif // FastKeyTranslatorHppIncluded