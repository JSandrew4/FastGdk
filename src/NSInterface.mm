/******************************************************************************/
/*                                                                            */
/*  NSInterface.mm                                                            */
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

#include <Fast/String.hpp>
#include <Fast/Rectangle.hpp>
#include <Fast/Window.hpp>
#include <Fast/CharacterInputEvent.hpp>
#include <Fast/KeyEvent.hpp>
#include <Fast/MouseButtonEvent.hpp>
#include <Fast/MouseWheelEvent.hpp>
#include <Fast/MouseMoveEvent.hpp>
#include <Fast/MouseRawMoveEvent.hpp>
#include <Fast/KeyTranslator.hpp>
#include <Fast/VideoMode.hpp>
#if defined(FastOSMacOSX)
#	include <ApplicationServices/ApplicationServices.h>
#	include <CoreFoundation/CoreFoundation.h>
#	include <IOKit/IOKitLib.h>
#	include <IOKit/graphics/IOGraphicsLib.h>
#	include <IOKit/graphics/IOGraphicsTypes.h>
#endif
#include "NSWindow.hpp"
#include "NSInterface.hpp"
#include "OpenGL.hpp"

#include "Undefs.hpp"

namespace Fast
{

#if defined(FastOSMacOSX)

	void NSStartApplication() {
		[NSApplication sharedApplication];
		NSObject<NSApplicationDelegate> *appDelegate =
			[[NSObject<NSApplicationDelegate> alloc] init];
		[NSApp setDelegate:appDelegate];
		[NSApp finishLaunching];
	}

	void NSStopApplication() {
		[NSApp stop:nil];
	}

	CNSAutoreleasePool* NSCreateAutoreleasePool() {
		return (CNSAutoreleasePool*)[[NSAutoreleasePool alloc] init];
	}

	void NSDestroyAutoreleasePool(CNSAutoreleasePool *arp) {
		[(NSAutoreleasePool*)arp release];
	}

	CNSWindow* NSCreateWindow(Window *chaosWindow) {
		FastNSWindow *window = [[FastNSWindow alloc]
			initWithFastWindow:chaosWindow
			contentRect:NSMakeRect(0, 0, 640, 480)
			styleMask:(NSUInteger)NSGetStyleMask(kWindowStyleNormal)
			backing:NSBackingStoreBuffered
			defer:NO];
		return (CNSWindow*)window;
	}

	CNSOpenGLContext* NSCreateOpenGLContext(CNSWindow *window,
		Int depthBits, Int stencilBits)
	{
		NSOpenGLContext *nsOpenGLContext;
		NSOpenGLPixelFormatAttribute attribs[] = {
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFADepthSize,		depthBits,
			NSOpenGLPFAColorSize,		32,
			NSOpenGLPFAStencilSize,		stencilBits,
			0, 0
		};
		NSOpenGLPixelFormat *glFormat = [[NSOpenGLPixelFormat alloc]
			initWithAttributes:attribs];
    	nsOpenGLContext = [[NSOpenGLContext alloc]
    		initWithFormat:glFormat shareContext:NULL];
    	[glFormat release];
    	[nsOpenGLContext setView:[(FastNSWindow*)window contentView]];
    	return (CNSOpenGLContext*)nsOpenGLContext;
	}

	CNSOpenGLContext* NSCreateSharedOpenGLContext(CNSOpenGLContext *glContext,
		Int depthBits, Int stencilBits)
	{
		NSOpenGLContext *nsOpenGLContext;
		NSOpenGLPixelFormatAttribute attribs[] = {
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFADepthSize,		depthBits,
			NSOpenGLPFAColorSize,		32,
			NSOpenGLPFAStencilSize,		stencilBits,
			0, 0
		};
		NSOpenGLPixelFormat *glFormat = [[NSOpenGLPixelFormat alloc]
			initWithAttributes:attribs];
    	nsOpenGLContext = [[NSOpenGLContext alloc]
    		initWithFormat:glFormat
    		shareContext:(NSOpenGLContext*)glContext];
    	[glFormat release];
    	return (CNSOpenGLContext*)nsOpenGLContext;
	}

	void NSDestroyWindow(CNSWindow *window) {
		[(FastNSWindow*)window release];
	}

	void NSDestroyOpenGLContext(CNSOpenGLContext *glContext) {
		[(NSOpenGLContext*)glContext release];
	}

	void NSShowWindow(CNSWindow *window) {
		[(FastNSWindow*)window makeKeyAndOrderFront:NSApp];
	}

	void NSHideWindow(CNSWindow *window) {
		[(FastNSWindow*)window orderOut:NSApp];
	}

	void NSHandleEvents(CNSWindow *window) {
		NSEvent *event;
		while (true) {
			event = [(FastNSWindow*)window nextEventMatchingMask:NSAnyEventMask
				untilDate:[NSDate distantPast]
				inMode:NSDefaultRunLoopMode dequeue:YES];
			if (event)
				[NSApp sendEvent:event];
			else break;
		}
	}

	Bool NSMakeContextCurrent(CNSOpenGLContext *glContext) {
		if (glContext)
			[(NSOpenGLContext*)glContext makeCurrentContext];
		else
			[NSOpenGLContext clearCurrentContext];
		return true; // This function can't fail apparently
	}

	Bool NSIsKeyWindow(CNSWindow * window) {
		return (Bool)[(FastNSWindow*)window isKeyWindow];
	}

	void NSSetWindowAlwaysOnTop(CNSWindow *window, Bool isAlwaysOnTop) {
		if (isAlwaysOnTop)
			[(FastNSWindow*)window setLevel:NSMainMenuWindowLevel+1];
		else
			[(FastNSWindow*)window setLevel:NSNormalWindowLevel];
	}

	UInt NSGetStyleMask(WindowStyle style) {
		switch (style)
		{
		case kWindowStyleNormal:
			return (UInt)(NSTitledWindowMask|NSClosableWindowMask|
				NSMiniaturizableWindowMask);
		case kWindowStyleResizable:
			return (UInt)(NSTitledWindowMask|NSClosableWindowMask|
				NSMiniaturizableWindowMask|NSResizableWindowMask);
		default: // Fullscreen and Borderless use a mask of 0
			return 0;
		};
	}

	void NSSetStyleMask(CNSWindow *window, UInt styleMask) {
		[(FastNSWindow*)window setStyleMask:(NSUInteger)styleMask];
	}

	void NSShowCursor(Bool showCursor) {
		showCursor ? [NSCursor unhide] : [NSCursor hide];
	}

	void NSSetContentRect(CNSWindow *window, const Rectangle &rect) {
		[(FastNSWindow*)window
			setFrame:NSMakeRect(rect.mX, rect.mY, rect.mWidth, rect.mHeight)
			display:YES
			animate:NO];
	}

	void NSGetContentRect(CNSWindow *window, Rectangle *rect) {
		NSRect nsRect = [[(FastNSWindow*)window contentView] frame];
		*rect = Rectangle(nsRect.origin.x, nsRect.origin.y,
			nsRect.size.width, nsRect.size.height);
	}

	void NSGetFrameRect(CNSWindow *window, Rectangle *rect) {
		NSRect nsRect = [(FastNSWindow*)window
			frameRectForContentRect:
				[[(FastNSWindow*)window contentView] frame]];
		*rect = Rectangle(nsRect.origin.x, nsRect.origin.y,
			nsRect.size.width, nsRect.size.height);
	}

	void NSSetWindowText(CNSWindow *window, const String &title) {
		[(FastNSWindow*)window setTitle:
			[NSString stringWithUTF8String:title.GetData()]];
	}

	void NSTrapCursor(CNSWindow *window, Bool trapCursor) {
		if (trapCursor) {
			if (![(FastNSWindow*)window IsCursorControlled]) {
				CGAssociateMouseAndMouseCursorPosition(false);
				[(FastNSWindow*)window ControlCursor];
			}
		} else {
			CGAssociateMouseAndMouseCursorPosition(true);
			[(FastNSWindow*)window FreeCursor];
		}
	}

	void NSSetCursorPosition(CNSWindow *window, Int x, Int y) {
		[(FastNSWindow*)window WarpCursor:Point(x, y)];
	}

	void NSGetCursorPosition(Int *x, Int *y) {
		NSPoint pt = [NSEvent mouseLocation];
		*x = pt.x;
		*y = pt.y;
	}

#endif

}
