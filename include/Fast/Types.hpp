/******************************************************************************/
/*                                                                            */
/*  Types.hpp                                                                 */
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

#ifndef FastTypesHppIncluded
#define FastTypesHppIncluded

// Set up platform
#if defined(_WIN32) || defined(_WIN64)
#	define FastOSWindows
#	define StdCall __stdcall
#	ifdef _DEBUG
#		define _CONSOLE 1
#	else
#		define _CONSOLE 0
#	endif
#	ifndef UNICODE // Hush MSVC warnings if already defined
#		define UNICODE
#	endif
#	if defined(_WIN64)
#		define FastWindows64
#	else
#		define FastWindows32
#	endif
#	if defined(FastExporting)
#		define FastApi	__declspec(dllexport)
#	else
#		define FastApi	__declspec(dllimport)
#	endif
#	if defined(FastStatic)
#		define FastApi
#	endif
#	define FastFunctionName	__FUNCTION__
#	include <Windows.h>
#elif defined(__linux__)
#	define FastOSLinux
#	define FastOSUnixLike
#	define StdCall
#	define FastApi
#	define FastFunctionName	__FUNCTION__
#	include <inttypes.h>
#elif defined(__APPLE__) && defined(__MACH__)
#	define FastOSMacOSX
#	define FastOSUnixLike
#	define StdCall
#	define FastApi
#	define FastFunctionName	__FUNCTION__
#elif defined(__FreeBSD__)
#	define FastOSFreeBsd
#	define FastOSUnixLike
#	define StdCall
#	define FastApi
#	define FastFunctionName	__FUNCTION__
#	error "Platform not yet supported!"
#elif defined(__HAIKU__)
#	define FastOSHaiku
#	define FastOSUnixLike
#	define StdCall
#	define FastApi
#	define FastFunctionName	__FUNCTION__
#	error "Platform not yet supported!"
#else
#	error "Platform not supported!"
#endif

namespace Fast
{
	// Primitive types
	typedef void				Void;
	typedef bool				Bool;
	typedef char				Byte;
	typedef char				Char;
	typedef unsigned char		UByte;
	typedef short				Short;
	typedef unsigned short		UShort;
	typedef int					Int;
	typedef unsigned int		UInt;
	typedef unsigned int		Size;
	typedef float				Float;
	typedef double				Double;
	typedef wchar_t				WChar;
#if defined(FastOSWindows)
	typedef __int64				Long;
	typedef unsigned __int64	ULong;
	typedef int					socklen_t;
	typedef void*				JoystickDeviceHandle;
#elif defined(FastOSLinux)
	typedef int64_t				Long;
	typedef uint64_t			ULong;
	typedef int					JoystickDeviceHandle;
#elif defined(FastOSMacOSX)
	typedef long long			Long;
	typedef unsigned long long	ULong;
	typedef void*				JoystickDeviceHandle;
#endif
	// Other types
	typedef void*				CHGLRC;
	typedef void*				CHDC;
	typedef void*				CHWND;
	typedef void*				CLPDIRECTINPUT8;
	typedef void*				CLPDIRECTINPUTDEVICE8;
	typedef void				CXDisplay;
	typedef UInt				CXWindow;
	typedef void*				CGLXContext;
	typedef UInt				CGLXWindow;
	typedef Int					CGLXDrawable;
	typedef void				CALCdevice;
	typedef void				CALCcontext;
	typedef void				CXRRCrtcInfo;
	typedef void				CXRRScreenResources;
	typedef void*				CGLXFBConfig;
	typedef Int					CXAtom;
	typedef void				CFTTextureFont;
	typedef void				Czip;
	typedef void				Czip_file;
	typedef void				CFILE;
	typedef void				CXEvent;
	typedef	void				CNSWindow;
	typedef void				CNSAutoreleasePool;
	typedef void				CNSOpenGLContext;
	typedef void				CFTFont;
	typedef void				CFTGlyphContainer;
	typedef void				CFTSize;
	typedef void				CFTFontFont;
	typedef void				CFTFontTexture2DFont;
#if defined(FastWindows32)
	typedef Int		CLRESULT;
	typedef Int		CLPARAM;
	typedef UInt	CWPARAM;
#else
	typedef Long	CLRESULT;
	typedef Long	CLPARAM;
	typedef ULong	CWPARAM;
#endif
}

#endif // FastTypesHppIncluded
