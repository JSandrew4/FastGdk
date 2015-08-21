/******************************************************************************/
/*                                                                            */
/*  Process.cpp                                                               */
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

#include <Fast/Process.hpp>
#include <Fast/String.hpp>
#include <Fast/Error.hpp>
#include <Fast/FileSystem.hpp>

#if defined(FastOSWindows)
#	include <WindowsX.h>
#elif defined(FastOSUnixLike)
#	include <unistd.h>
#endif

#include <cstdlib>

#include "Undefs.hpp"

namespace Fast
{
	namespace Process
	{
		ErrorType Run(const String &command) {
			ErrorType error = kErrorNone;
		#if defined(FastOSWindows)
			FileSystem fs;
			PROCESS_INFORMATION pi;
			STARTUPINFO si;
			BOOL success;
			memset(&pi, 0, sizeof(PROCESS_INFORMATION));
			memset(&si, 0, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);
			success = CreateProcess(
				0, command.GetWString().mData, 0, 0, FALSE,
				NORMAL_PRIORITY_CLASS, 0,
				fs.GetCurrentWorkingPath().GetWString().mData,
				&si, &pi);
			if (success) {
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			} else
				error = kErrorProcessCreationFailure;
		#elif defined(FastOSUnixLike)
			pid_t pid = fork();
			if (pid == 0) {
				std::system(command.GetData());
				exit(0);
			} else if (pid < 0)
				error = kErrorProcessCreationFailure;
		#endif
			return error ? Error::Throw(error, String("[%s(\"%s\")]",
				FastFunctionName, command.GetCString())) : kErrorNone;
		}

		Int GetCurrentProcessID() {
		#if defined(FastOSWindows)
			return (Int)GetCurrentProcessId();
		#elif defined(FastOSUnixLike)
			return (Int)getpid();
		#endif
		}
	}
}