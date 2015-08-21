/******************************************************************************/
/*                                                                            */
/*  Exception.cpp                                                             */
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

#include <Fast/Exception.hpp>
#include <Fast/Debug.hpp>
#include <Fast/Logger.hpp>
#include <Fast/Application.hpp>

#include <cstdio>

#include "Undefs.hpp"

namespace Fast
{
	namespace Exception
	{
		void (*gExceptionCallback)(ExceptionType, const String&, void*);

		String GetString(ExceptionType error) {
			switch (error)
			{
			case kExceptionNone:
				return "No exception";
			case kExceptionGeneric:
				return "An exception occurred";
			case kExceptionOutOfRange:
				return "Out of range";
			case kExceptionSocketInvalid:
				return "Socket invalid";
			case kExceptionWindowCreationFailure:
				return "Window creation failure";
			case kExceptionBailerCreationFailure:
				return "Bailer creation failure";
			case kExceptionThreadTooManyThreads:
				return "Too many threads";
			case kExceptionThreadOutOfResources:
				return "Thread out of resources";
			case kExceptionThreadPermissionDenied:
				return "Thread permission denied";
			case kExceptionThreadInvalidArgument:
				return "Invalid thread argument";
			case kExceptionX11OpenDisplayFailure:
				return "X11 display open failure";
			case kExceptionX11InitializeInputFailure:
				return "X11 Input initialization failure";
			case kExceptionX11InitializeRAndRFailure:
				return "X11 RandR initialization failure";
			case kExceptionOpenGLContextCreationFailure:
				return "OpenGL context creation failure";
			case kExceptionOpenGLPixelFormatInvalid:
				return "OpenGL pixel format invalid";
			case kExceptionOpenGLNoValidPixelFormats:
				return "No valid OpenGL pixel formats";
			case kExceptionOpenGLLoadExtensionFailure:
				return "OpenGL load extension failure";
			case kExceptionOpenALDeviceCreationFailure:
				return "OpenAL device creation failure";
			case kExceptionOpenALGenSourcesFailure:
				return "OpenAL source generation failure";
			case kExceptionOpenALContextCreationFailure:
				return "OpenAL context creation failure";
			case kExceptionOpenALFormatInvalid:
				return "OpenAL format invalid";
			case kExceptionMonitorIDOutOfRange:
				return "Monitor ID out of range";
			case kExceptionMonitorEnumerationFailure:
				return "Monitor enumeration failure";
			default:
				return "Invalid exception code";
			}
		}

		void DefaultCallback(ExceptionType exception,
			const String &moreInfo, void *args)
		{
			Application::GetCurrent()->GetLogger()->LogCritical(
				String("Exception %d: %s. %s\n", (Int)exception,
					GetString(exception).GetCString(), moreInfo.GetCString()));
		}

		void SetCallback(void (*callback)(ExceptionType,const String&,void*)) {
			gExceptionCallback = callback;
		}

		void Throw(ExceptionType exception, const String &moreInfo, void *args)
		{
			(*gExceptionCallback)(exception, moreInfo, args);
			throw exception;
		}
	}
}
