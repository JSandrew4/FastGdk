/******************************************************************************/
/*                                                                            */
/*  Clipboard.hpp                                                             */
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

#ifndef FastClipboardHppIncluded
#define FastClipboardHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/String.hpp>

namespace Fast
{
	class Window;
	class Display;
	
	class FastApi Clipboard
	{
	private:
		Window	&mWindow;
		// Hide these functions. No reason to copy Clipboard objects.
		Clipboard(const Clipboard &that) : mWindow(that.mWindow) { }
		Clipboard& operator=(const Clipboard &that) { return *this; }
	public:
		Clipboard(Window *window);
		~Clipboard();
		ErrorType	StoreText(const String &text);
		String		GetStoredText();
		void		Clear();
	};
}

#endif // FastClipboardHppIncluded
