/******************************************************************************/
/*                                                                            */
/*  Cocoa.mm                                                                  */
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

#include "Cocoa.hpp"
#include <Fast/Window.hpp>
#include <Fast/Point.hpp>

#include "Undefs.hpp"

using namespace Fast;

@implementation FastNSWindow

- (id)initWithFastWindow:(Fast::Window*)fastWindow
	contentRect:(NSRect)frame
	styleMask:(NSUInteger)styleMask
	backing:(NSUInteger)backing
	defer:(BOOL)defer
{
	self = [super initWithContentRect:frame
		styleMask:styleMask
		backing:backing
		defer:defer];
	if (self) {
		mFastWindow = fastWindow;
		[self setAcceptsMouseMovedEvents:YES];
		NSOpenGLPixelFormatAttribute attribs[] = {
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFADepthSize,		32,
			NSOpenGLPFAColorSize,		32,
			NSOpenGLPFAStencilSize,		0,
		};
		NSOpenGLPixelFormat *glFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
    	mGLContext = [[NSOpenGLContext alloc] initWithFormat:glFormat shareContext:NULL];
    	[glFormat release];
    	[mGLContext setView:[self contentView]];
		//[self setAutodisplay: NO];
		mShouldDraw = true;
	}
	return self;
}

- (Fast::Window*) GetFastWindow {
	return mFastWindow;
}

- (void) CheckEvents {
	NSEvent *event;
	while (true) {
		event = [self nextEventMatchingMask:NSAnyEventMask
			untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES];
		if (!event) { // FIXME ?
			[event release];
			break;
		}
		switch([event type])
		{
		case NSKeyDown:
			NSLog(@"NSKeyDown\n");
			break;
		case NSKeyUp:
			NSLog(@"NSKeyUp\n");
			break;
		case NSMouseMoved:
			NSLog(@"NSMouseMoved\n");
			break;
		case NSScrollWheel:
			NSLog(@"NSScrollWheel\n");
			break;
		default:
			NSLog(@"Unsupported event: %d\n", (int)[event type]);
			[NSApp sendEvent:event];
			break;
		}
		[event release];
	}
}

- (void) MakeCurrent:(BOOL)makeCurrent {
	if (makeCurrent)
		[mGLContext makeCurrentContext];
	else
		[NSOpenGLContext clearCurrentContext];
}

- (void) SetSwapInterval:(Int)swapInterval {
	[mGLContext setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
}

- (void) SwapGraphicsBuffers {
	glFlushRenderAPPLE();
	glFinishRenderAPPLE();
	glSwapAPPLE();
}

- (void) MoveCursorTo:(const Fast::Point &)point {
	/*NSPoint pnt = NSMakePoint(point.x, point.y);
	//NSPoint mouseLocation = [NSEvent mouseLocation];
	NSEnumerator * screenEnumerator = [[NSScreen screens] objectEnumerator];
	NSScreen * screen;
	do {
		screen = [screenEnumerator nextObject];
	} while (screen && !NSMouseInRect([self convertBaseToScreen:pnt], screen.frame, NO));
	if (!screen)
		return;
	pnt.y = ([screen frame].origin.y + [screen frame].size.height) - pnt.y;
	pnt.x = [self frame].origin.x - pnt.x;
	pnt.y -= [self frame].origin.y;
	std::cout << "Move mouse to (" << pnt.x << "," << pnt.y << ")" << std::endl;
	std::cout << "Window origin (" << [self frame].origin.x << "," << [self frame].origin.y << ")" << std::endl;

	CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
    CGEventRef evt = CGEventCreateMouseEvent(src, kCGEventMouseMoved, NSPointToCGPoint(pnt), kCGMouseButtonLeft);
    CGEventPost(kCGSessionEventTap, evt);
    CFRelease(evt);
    CFRelease(src);*/



	//CGEventSourceRef evtSource = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
	//Rect windowRect;
	//GetWindowBounds([self windowRef], kWindowStructureRgn, &windowRect);
	// TODO: Figure out Mac screen coords
	//CGWarpMouseCursorPosition(pnt);
	//CGEventSourceSetLocalEventsSuppressionInterval(evtSource, 0.0);
}

- (void) SetCursorVisible:(Bool)isCursorVisible {
	isCursorVisible ? [NSCursor unhide] : [NSCursor hide];
}

- (void) dealloc {
	[mGLContext release];
	[super dealloc];
}

- (BOOL) canBecomeKeyWindow {
	return YES;
}

@end
