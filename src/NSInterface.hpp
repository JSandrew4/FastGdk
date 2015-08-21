/******************************************************************************/
/*                                                                            */
/*  NSInterface.hpp                                                           */
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

#ifndef FastNSInterfaceHppIncluded
#define FastNSInterfaceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/WindowStyle.hpp>

namespace Fast
{
	class Rectangle;
	class String;
	class Window;

#if defined(FastOSMacOSX)

	extern void					NSStartApplication();
	extern void					NSStopApplication();
	extern CNSAutoreleasePool*	NSCreateAutoreleasePool();
	extern void					NSDestroyAutoreleasePool(
									CNSAutoreleasePool *arp);
	extern CNSWindow*			NSCreateWindow(Window *chaosWindow);
	extern CNSOpenGLContext*	NSCreateOpenGLContext(CNSWindow *window,
									Int depthBits, Int stencilBits);
	extern CNSOpenGLContext*	NSCreateSharedOpenGLContext(
									CNSOpenGLContext *glContext,
									Int depthBits, Int stencilBits);
	extern void					NSDestroyWindow(CNSWindow *window);
	extern void					NSDestroyOpenGLContext(
									CNSOpenGLContext *glContext);
	extern void					NSShowWindow(CNSWindow *window);
	extern void					NSHideWindow(CNSWindow *window);
	extern void					NSHandleEvents(CNSWindow *window);
	extern Bool					NSMakeContextCurrent(
									CNSOpenGLContext *glContext);
	extern Bool					NSIsKeyWindow(CNSWindow *window);
	extern void					NSSetWindowAlwaysOnTop(CNSWindow *window,
									Bool isAlwaysOnTop);
	extern UInt					NSGetStyleMask(WindowStyle style);
	extern void					NSSetStyleMask(CNSWindow *window,
									UInt styleMask);
	extern void					NSShowCursor(Bool showCursor);
	extern void					NSSetContentRect(CNSWindow *window,
									const Rectangle &rect);
	extern void					NSGetContentRect(CNSWindow *window,
									Rectangle *rect);
	extern void					NSGetFrameRect(CNSWindow *window,
									Rectangle *rect);
	extern void					NSSetWindowText(CNSWindow *window,
									const String &title);
	extern void					NSTrapCursor(CNSWindow *window,
									Bool trapCursor);
	extern void					NSSetCursorPosition(CNSWindow *window,
									Int x, Int y);
	extern void					NSGetCursorPosition(Int *x, Int *y);

#endif
	
}

#endif // FastNSInterfaceHppIncluded
