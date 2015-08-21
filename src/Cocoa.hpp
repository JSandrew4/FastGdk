/******************************************************************************/
/*                                                                            */
/*  Cocoa.cpp                                                                 */
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

#ifndef FastCocoaHppIncluded
#define FastCocoaHppIncluded

#include <Fast/Types.hpp>
#include <Cocoa/Cocoa.h>
#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/graphics/IOGraphicsLib.h>
#include <IOKit/graphics/IOGraphicsTypes.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

namespace Fast
{
	class Window;
	class Point;
}

@interface FastNSWindow : NSWindow
{
	Fast::Window	*mFastWindow;
	Fast::Bool		mShouldDraw;
	NSOpenGLContext	*mGLContext;
}
- (id) initWithFastWindow:(Fast::Window*)fastWindow
	contentRect:(NSRect)frame
	styleMask:(NSUInteger)styleMask
	backing:(NSUInteger)backing
	defer:(BOOL)defer;
- (Fast::Window*) GetFastWindow;
- (void) CheckEvents;
- (void) MakeCurrent:(BOOL)makeCurrent;
- (void) SetSwapInterval:(Fast::Int)swapInterval;
- (void) SwapGraphicsBuffers;
- (void) MoveCursorTo:(const Fast::Point &)point;
- (void) SetCursorVisible:(Fast::Bool)isCursorVisible;
- (BOOL) canBecomeKeyWindow;
@end

#endif // FastCocoaHppIncluded
