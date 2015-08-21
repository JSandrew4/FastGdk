/******************************************************************************/
/*                                                                            */
/*  SystemConsole.hpp                                                         */
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

#ifndef FastSystemConsoleHppIncluded
#define FastSystemConsoleHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>

#define kFastSystemConsoleMaxInputCharacters	4192

namespace Fast
{
	class FastApi SystemConsole
	{
	private:
		Char	mInput[kFastSystemConsoleMaxInputCharacters];
	public:
		SystemConsole();
		void	Print(const String &text);
		void	PrintLine(const String &text);
		void	Pause();
		void	Clear();
		void	Flush();
		String	Read();
		void	Read(String *result);
		String	Read(Int numCharacters);
		void	Read(Int numCharacters, String *result);
		String	Read(const String &delimiter);
		void	Read(const String &delimiter, String *result);
	};
}

#endif // FastSystemConsoleHppIncluded