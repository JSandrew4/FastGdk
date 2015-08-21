/******************************************************************************/
/*                                                                            */
/*  Application.cpp                                                           */
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

#include <Fast/Application.hpp>
#include <Fast/Error.hpp>
#include <Fast/Exception.hpp>
#include <Fast/Debug.hpp>
#include <Fast/Logger.hpp>
#if defined(FastOSLinux)
#	include <X11/Xlib.h>
#endif

#include <cstdlib>
#include <clocale>

#include "OpenGL.hpp"
#include "W32Interface.hpp"
#include "NSInterface.hpp"
#include "Network.hpp"

#include "Undefs.hpp"

namespace Fast
{
	Application *gCurrentApplication = NULL;

	Application::Application(Int argc, Char **argv) {
		if (NULL != gCurrentApplication)
			throw kExceptionGeneric; // TODO: kExceptionMultipleApplicationInstances
		gCurrentApplication = this;
		mLogger.SetDisplayLevel(kLoggerDisplayAll);
		mLogger.SetOutputFileName("FastDebug.txt");
		mLogger.SetShouldWriteToConsole(true);
		Error::SetCallback(Error::DefaultCallback);
		Exception::SetCallback(Exception::DefaultCallback);
	#if defined(FastOSWindows)
		W32XInputEnable(true);
		WSADATA wsd;
		WSAStartup(0x0202, &wsd);
	#elif defined(FastOSLinux)
		XInitThreads();
	#elif defined(FastOSMacOSX)
		NSStartApplication();
	#endif
		mArgc = argc;
		mArgv = argv;
		setlocale(LC_ALL, "");
		mLogger.SetDisplayLevel(kLoggerDisplayErrorAndCritical);
	}

	Application::~Application() {
		Application::Exit(0);
	}

	Application* Application::GetCurrent() {
		return gCurrentApplication;
	}

	Logger* Application::GetLogger() {
		return &mLogger;
	}

	const Logger& Application::GetLogger() const {
		return mLogger;
	}

	void Application::Exit(Int exitCode) {
	#if defined(FastOSWindows)
		WSACleanup();
		W32XInputEnable(false);
		ExitProcess(exitCode);
	#elif defined(FastOSLinux)
		exit(exitCode);
	#elif defined(FastOSMacOSX)
		NSStopApplication();
		exit(exitCode);
	#endif
	}
}
