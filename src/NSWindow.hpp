/******************************************************************************/
/*                                                                            */
/*  NSWindow.hpp                                                              */
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

#ifndef FastNSWindowHppIncluded
#define FastNSWindowHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Point.hpp>
#include <Fast/KeyTranslator.hpp>
#include "NSJoystickWatcher.hpp"

#if defined(FastOSMacOSX)
#	include <Cocoa/Cocoa.h>
#	include <ApplicationServices/ApplicationServices.h>
#	include <CoreFoundation/CoreFoundation.h>
#	include <IOKit/IOKitLib.h>
#	include <IOKit/IOHidLib.h>
#	include <IOKit/graphics/IOGraphicsLib.h>
#	include <IOKit/graphics/IOGraphicsTypes.h>
#	include <OpenGL/gl.h>
#	include <OpenGL/glu.h>
#	include <DDHidLib/DDHidLib.h>
#endif

namespace Fast
{
	class Window;
	class Point;
}

#if defined(FastOSMacOSX)

@interface FastNSWindow : NSWindow
{
	Fast::Window			*mFastWindow;
	Fast::Bool				mShouldDraw;
	NSOpenGLContext			*mGLContext;
	Fast::Bool				mIsShiftKeyDown;
	Fast::Bool				mIsControlKeyDown;
	Fast::Bool				mIsSuperKeyDown;
	Fast::Bool				mIsAltKeyDown;
	Fast::Bool				mIsCursorControlled;
	Fast::Point			mLastMouseDelta;
	Fast::Point			mWarpCursorDelta;
	Fast::Bool				mJustWarpedCursor;
	Fast::KeyTranslator	mKeyTranslator;
	IOHIDManagerRef			mHidManager;
	Int						mHidPageInt;
	CFStringRef				mHidPageString;
	CFNumberRef				mHidPageNumber;
	Int						mHidUsageInt;
	CFStringRef				mHidUsageString;
	CFNumberRef				mHidUsageNumber;
	CFMutableDictionaryRef	mHidCriterionDict;
}
// (Con/De)structors
- (id) initWithFastWindow:(Fast::Window*)chaosWindow
	contentRect:(NSRect)frame
	styleMask:(NSUInteger)styleMask
	backing:(NSUInteger)backing
	defer:(BOOL)defer;
- (void) dealloc;
// Misc functions
- (Fast::Window*) GetFastWindow;
- (void) SetSwapInterval:(Fast::Int)swapInterval;
- (void) SwapGraphicsBuffers;
- (void) ControlCursor;
- (void) FreeCursor;
- (void) WarpCursor:(const Fast::Point&)point;
- (BOOL) IsCursorControlled;
- (void) RefreshAttachedJoysticks;
- (BOOL) canBecomeKeyWindow;
- (BOOL) acceptsFirstResponder;
// Event functions
- (void) generalMouseMoveHandler:(NSEvent*)event;
- (void) keyDown:(NSEvent*)event;
- (void) keyUp:(NSEvent*)event;
- (void) flagsChanged:(NSEvent*)event;
- (void) scrollWheel:(NSEvent*)event;
- (void) mouseMoved:(NSEvent*)event;
- (void) mouseDown:(NSEvent*)event;
- (void) mouseUp:(NSEvent*)event;
- (void) mouseDragged:(NSEvent*)event;
- (void) rightMouseDown:(NSEvent*)event;
- (void) rightMouseUp:(NSEvent*)event;
- (void) rightMouseDragged:(NSEvent*)event;
- (void) otherMouseDown:(NSEvent*)event;
- (void) otherMouseUp:(NSEvent*)event;
- (void) otherMouseDragged:(NSEvent*)event;
@end

#endif

#endif // FastNSWindowHppIncluded
