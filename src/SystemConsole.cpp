/******************************************************************************/
/*                                                                            */
/*  SystemConsole.cpp                                                         */
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

#include <Fast/SystemConsole.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

namespace Fast
{
	SystemConsole::SystemConsole() {
		memset(mInput, 0, kFastSystemConsoleMaxInputCharacters);
	}

	void SystemConsole::Print(const String &text) {
	#if defined(FastOSWindows)
		wprintf(text.GetWString().mData);
	#elif defined(FastOSUnixLike)
		printf(text.GetCString());
	#endif
	}

	void SystemConsole::PrintLine(const String &text) {
		Print(text);
		Print("\n");
	}

	void SystemConsole::Pause() {
		Print("Press Enter to continue...");
		Read();
	}

	void SystemConsole::Clear() {
	#if defined(FastOSWindows)
		system("cls");
	#elif defined(FastOSUnixLike)
		system("clear");
	#endif
	}

	void SystemConsole::Flush() {
		fflush(stdin);
	}

	String SystemConsole::Read() {
		String s;
		Read(s);
		return s;
	}

	void SystemConsole::Read(String *result) {
		result->Clear();
		Int strLength;
		fgets(mInput, 1024, stdin);
		strLength = strlen(mInput);
		mInput[strLength-1] = '\0';
		*result = mInput;
	}

	String SystemConsole::Read(Int numCharacters) {
		String s;
		Read(numCharacters, &s);
		return s;
	}

	void SystemConsole::Read(Int numCharacters, String *result) {
		result->Clear();
		Read(result);
		*result = result->GetSubString(0, numCharacters);
	}

	String SystemConsole::Read(const String &delimiter) {
		String s;
		Read(delimiter, &s);
		return s;
	}

	void SystemConsole::Read(const String &delimiter, String *result) {
		result->Clear();
		Read(result);
		*result = result->GetSubString(0, result->FindFirstOf(delimiter, 0));
	}
}