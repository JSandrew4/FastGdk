/******************************************************************************/
/*                                                                            */
/*  NSWindow.mm                                                               */
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

#include "NSWindow.hpp"
#include <Fast/Window.hpp>
#include <Fast/Point.hpp>
#include <Fast/CharacterInputEvent.hpp>
#include <Fast/KeyEvent.hpp>
#include <Fast/MouseButtonEvent.hpp>
#include <Fast/MouseWheelEvent.hpp>
#include <Fast/MouseMoveEvent.hpp>
#include <Fast/MouseRawMoveEvent.hpp>

#include "Undefs.hpp"

using namespace Fast;

namespace Fast
{
	void OnGamepadConnect(void *window, IOReturn result, void *sender,
		IOHIDDeviceRef device)
	{
		// TODO
		NSLog(@"Gamepad connected.");
	}

	void OnGamepadDisconnect(void *window, IOReturn result, void *sender,
		IOHIDDeviceRef device)
	{
		// TODO
		NSLog(@"Gamepad disconnected.");
	}

	void OnGamepadEvent(void *window, IOReturn result, void *sender,
		IOHIDValueRef value)
	{
		IOHIDElementRef element = IOHIDValueGetElement(value);
		long elementValue = IOHIDValueGetIntegerValue(value);
		// TODO
		NSLog(@"Gamepad event element=%@ value=%li", element, elementValue);
	}
}

@interface FastNSWindow (hidden)
- (void) ReleaseHidData;
@end

@implementation FastNSWindow

- (id) initWithFastWindow:(Fast::Window*)chaosWindow
	contentRect:(NSRect)frame
	styleMask:(NSUInteger)styleMask
	backing:(NSUInteger)backing
	defer:(BOOL)defer
{
	if (self = [super initWithContentRect:frame
		styleMask:styleMask
		backing:backing
		defer:defer])
	{
		mFastWindow = chaosWindow;
		[self setAcceptsMouseMovedEvents:YES];
		//[self setAutodisplay: NO];
		mShouldDraw = true;
		mIsShiftKeyDown = false;
		mIsControlKeyDown = false;
		mIsSuperKeyDown = false;
		mIsAltKeyDown = false;
		mIsCursorControlled = false;
		mJustWarpedCursor = false;
		mHidManager = NULL;
		mHidPageInt = 0;
		mHidPageString = NULL;
		mHidPageNumber = NULL;
		mHidUsageInt = 0;
		mHidUsageString = NULL;
		mHidUsageNumber = NULL;
		mHidCriterionDict = NULL;
		[self RefreshAttachedJoysticks];
	}
	return self;
}

- (void) dealloc {
	[self ReleaseHidData];
	[super dealloc];
}

- (Fast::Window*) GetFastWindow {
	return mFastWindow;
}

- (void) SetSwapInterval:(Int)swapInterval {
	[mGLContext setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
}

- (void) SwapGraphicsBuffers {
	glFlushRenderAPPLE();
	glFinishRenderAPPLE();
	glSwapAPPLE();
}

- (void) ControlCursor {
	mIsCursorControlled = true;
	mLastMouseDelta = Fast::kFastPointZero;
}

- (void) FreeCursor {
	mLastMouseDelta = Fast::kFastPointZero;
	mIsCursorControlled = false;
}

- (void) WarpCursor:(const Fast::Point&)point {
	CGPoint ptOld, ptNew;
	CGEventRef ev;
	CGEventSourceRef evSource;
	ptNew.x = point.mX;
	ptNew.y = point.mY;
	evSource = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
	ev = CGEventCreate(evSource);
	ptOld = CGEventGetLocation(ev);
	CGWarpMouseCursorPosition(ptNew);
	CGAssociateMouseAndMouseCursorPosition(true);
	if (mIsCursorControlled)
		CGAssociateMouseAndMouseCursorPosition(false);
	mJustWarpedCursor = true;
	mWarpCursorDelta.mX = ptNew.x - ptOld.x;
	mWarpCursorDelta.mY = ptNew.y - ptOld.y;
	CFRelease(ev);
	CFRelease(evSource);
}

- (BOOL) IsCursorControlled {
	return mIsCursorControlled;
}

- (void) ReleaseHidData {
	if (mHidManager) {
		IOHIDManagerClose(mHidManager, kIOHIDOptionsTypeNone);
		CFRelease(mHidCriterionDict);
		CFRelease(mHidPageString);
		CFRelease(mHidPageNumber);
		CFRelease(mHidUsageString);
		CFRelease(mHidUsageNumber);
		CFRelease(mHidManager);
	}
}

- (void) RefreshAttachedJoysticks {
	[self ReleaseHidData];
	mHidManager = IOHIDManagerCreate(
		kCFAllocatorDefault, kIOHIDOptionsTypeNone);
	if (!mHidManager) {
		// TODO: Throw exception
	}
	IOReturn ioReturn = IOHIDManagerOpen(mHidManager, kIOHIDOptionsTypeNone);
	if (!ioReturn) {
		// TODO: Throw exception
	}
	mHidPageInt = kHIDPage_GenericDesktop;
	mHidPageString = CFStringCreateWithCString(
		kCFAllocatorDefault, kIOHIDDeviceUsagePageKey, kCFStringEncodingASCII);
	mHidPageNumber = CFNumberCreate(
		kCFAllocatorDefault, kCFNumberIntType, &mHidPageInt);
	mHidUsageInt = kHIDUsage_GD_GamePad;
	mHidUsageString = CFStringCreateWithCString(
		kCFAllocatorDefault, kIOHIDDeviceUsageKey, kCFStringEncodingASCII);
	mHidUsageNumber = CFNumberCreate(
		kCFAllocatorDefault, kCFNumberIntType, &mHidUsageInt);
	mHidCriterionDict = CFDictionaryCreateMutable(NULL, 0,
		&kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	CFDictionarySetValue(mHidCriterionDict, mHidPageString, mHidPageNumber);
	CFDictionarySetValue(mHidCriterionDict, mHidUsageString, mHidUsageNumber);
	IOHIDManagerSetDeviceMatching(mHidManager, mHidCriterionDict);
	IOHIDManagerRegisterDeviceMatchingCallback(
		mHidManager, Fast::NSOnGamepadConnect, (void*)mFastWindow);
	IOHIDManagerRegisterDeviceRemovalCallback(
		mHidManager, Fast::NSOnGamepadDisconnect, (void*)mFastWindow);
	IOHIDManagerRegisterInputValueCallback(
		mHidManager, Fast::NSOnGamepadEvent, (void*)mFastWindow);
	IOHIDManagerScheduleWithRunLoop(
		mHidManager, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
}

- (BOOL) canBecomeKeyWindow {
	return YES;
}

- (BOOL) acceptsFirstResponder {
	return YES;
}

- (void) generalMouseMoveHandler:(NSEvent*)event {
	NSPoint pt;
	Fast::MouseMoveEvent mm;
	Fast::MouseRawMoveEvent mrm; 
	BOOL isInWindow;
	Fast::Point mouseDelta;
	// Get "raw" mouse movement. True raw movement is not supported on Mac OS X
	CGGetLastMouseDelta(&mouseDelta.mX, &mouseDelta.mY);
	mouseDelta.mX -= mLastMouseDelta.mX;
	mouseDelta.mY -= mLastMouseDelta.mY;
	if (mJustWarpedCursor) {
		mouseDelta.mX -= mWarpCursorDelta.mX;
		mouseDelta.mY -= mWarpCursorDelta.mY;
		mJustWarpedCursor = false;
	}
	mLastMouseDelta = mouseDelta;
	mrm.mMovement = mouseDelta;
	mFastWindow->TriggerMouseRawMoveEvent(mrm);
	// Get cursor location from event
	pt = [[self contentView] convertPoint:[event locationInWindow]
		toView:[self contentView]];
	mm.mPosition = Fast::Point((Fast::Int)pt.x, (Fast::Int)pt.y);
	mm.mPosition.mY -= 1; // Y is offset by 1 in Cocoa for some reason
	mm.mPosition.mY = // Adjust point to top-left coord system
		(Fast::Int)[[self contentView] frame].size.height - mm.mPosition.mY;
	// Clip cursor if it should be locked inside window
	if (mIsCursorControlled) {
		CGPoint cgPoint;
		mm.mPosition.mX += mouseDelta.mX;
		mm.mPosition.mY += mouseDelta.mY;
		if (mm.mPosition.mX >= (Int)[[self contentView] frame].size.width)
			mm.mPosition.mX = (Int)[[self contentView] frame].size.width;
		if (mm.mPosition.mX < 0)
			mm.mPosition.mX = 0;
		if (mm.mPosition.mY >= (Int)[[self contentView] frame].size.height)
			mm.mPosition.mY = (Int)[[self contentView] frame].size.height;
		if (mm.mPosition.mY < 0)
			mm.mPosition.mY = 0;
		cgPoint.x = mm.mPosition.mX;
		cgPoint.y = mm.mPosition.mY;
		CGWarpMouseCursorPosition(cgPoint);
		CGAssociateMouseAndMouseCursorPosition(true);
		CGAssociateMouseAndMouseCursorPosition(false);
	} else {
		// Don't trigger event if cursor is outside of window, for consistency
		if (mm.mPosition.mX < 0 ||
			mm.mPosition.mX >= (Int)[[self contentView] frame].size.width ||
			mm.mPosition.mY < 0 ||
			mm.mPosition.mY >= (Int)[[self contentView] frame].size.height)
		{
			return;
		}
	}
	mFastWindow->TriggerMouseMoveEvent(mm);
}

- (void) keyDown:(NSEvent*)event {
	Fast::KeyEvent k;
	// Look for a keycode (insert, f1, pause, etc.)
	k.mKey = mKeyTranslator.GetKey((int)[event keyCode]);
	// If no keycode exists, get the key character
	if (k.mKey.IsEmpty()) {
		// First handle character input
		if (mFastWindow->IsInTypingMode()) {
			CharacterInputEvent ci;
			ci.mString = [[event characters]
				cStringUsingEncoding:NSUTF8StringEncoding];
			if (!ci.mString.IsEmpty())
				mFastWindow->TriggerCharacterInputEvent(ci);
		}
		// Now generic game input
		if ([event modifierFlags] & NSShiftKeyMask) {
			NSEvent *nsevent;
			CGEventRef cgevent;
			// Get key character unmodified by shift key
			cgevent = CGEventCreateKeyboardEvent(
				0, (CGKeyCode)[event keyCode], true);
			CGEventSetFlags(cgevent, 0);
			nsevent = [NSEvent eventWithCGEvent:cgevent];
			k.mKey = [[nsevent charactersIgnoringModifiers]
				cStringUsingEncoding:NSUTF8StringEncoding];
			CFRelease(cgevent);
			[nsevent release];
		} else {
			k.mKey = [[event charactersIgnoringModifiers]
				cStringUsingEncoding:NSUTF8StringEncoding];
		}
	}
	if (!k.mKey.IsEmpty()) {
		k.mAction = kKeyActionPressed;
		mFastWindow->TriggerKeyEvent(k);
	}
	[super keyDown:event];
}

- (void) keyUp:(NSEvent*)event {
	Fast::KeyEvent k;
	// Look for a keycode (insert, f1, pause, etc.)
	k.mKey = mKeyTranslator.GetKey((int)[event keyCode]);
	// If no keycode exists, get the key character
	if (k.mKey.IsEmpty()) {
		if ([event modifierFlags] & NSShiftKeyMask) {
			NSEvent *nsevent;
			CGEventRef cgevent;
			// Get key character unmodified by shift key
			cgevent = CGEventCreateKeyboardEvent(
				0, (CGKeyCode)[event keyCode], true);
			CGEventSetFlags(cgevent, 0);
			nsevent = [NSEvent eventWithCGEvent:cgevent];
			k.mKey = [[nsevent charactersIgnoringModifiers]
				cStringUsingEncoding:NSUTF8StringEncoding];
			CFRelease(cgevent);
			[nsevent release];
		} else {
			k.mKey = [[event charactersIgnoringModifiers]
				cStringUsingEncoding:NSUTF8StringEncoding];
		}
	}
	if (!k.mKey.IsEmpty()) {
		k.mAction = kKeyActionReleased;
		mFastWindow->TriggerKeyEvent(k);
	}
	[super keyUp:event];
}

- (void) flagsChanged:(NSEvent*)event {
	UInt flags = [event modifierFlags];
	Fast::KeyEvent k;
	if ((flags & NSShiftKeyMask) && !mIsShiftKeyDown) {
		mIsShiftKeyDown = true;
		k.mKey = "shift";
		k.mAction = kKeyActionPressed;
		mFastWindow->TriggerKeyEvent(k);
	} else if (!(flags & NSShiftKeyMask) && mIsShiftKeyDown) {
		mIsShiftKeyDown = false;
		k.mKey = "shift";
		k.mAction = kKeyActionReleased;
		mFastWindow->TriggerKeyEvent(k);
	}
	if ((flags & NSControlKeyMask) && !mIsControlKeyDown) {
		mIsControlKeyDown = true;
		k.mKey = "control";
		k.mAction = kKeyActionPressed;
		mFastWindow->TriggerKeyEvent(k);
	} else if (!(flags & NSControlKeyMask) && mIsControlKeyDown) {
		mIsControlKeyDown = false;
		k.mKey = "control";
		k.mAction = kKeyActionReleased;
		mFastWindow->TriggerKeyEvent(k);
	}
	if ((flags & NSCommandKeyMask) && !mIsSuperKeyDown) {
		mIsSuperKeyDown = true;
		k.mKey = "super";
		k.mAction = kKeyActionPressed;
		mFastWindow->TriggerKeyEvent(k);
	} else if (!(flags & NSCommandKeyMask) && mIsSuperKeyDown) {
		mIsSuperKeyDown = false;
		k.mKey = "super";
		k.mAction = kKeyActionReleased;
		mFastWindow->TriggerKeyEvent(k);
	}
	if ((flags & NSAlternateKeyMask) && !mIsAltKeyDown) {
		mIsAltKeyDown = true;
		k.mKey = "alt";
		k.mAction = kKeyActionPressed;
		mFastWindow->TriggerKeyEvent(k);
	} else if (!(flags & NSAlternateKeyMask) && mIsAltKeyDown) {
		mIsAltKeyDown = false;
		k.mKey = "alt";
		k.mAction = kKeyActionReleased;
		mFastWindow->TriggerKeyEvent(k);
	}
	[super flagsChanged:event];
}

- (void) scrollWheel:(NSEvent*)event {
	Fast::MouseWheelEvent mw;
	if ([event deltaY] >= 1.0f) {
		mw.mAction = kMouseWheelActionScrollUp;
		mFastWindow->TriggerMouseWheelEvent(mw);
	} else if ([event deltaY] <= -1.0f) {
		mw.mAction = kMouseWheelActionScrollDown;
		mFastWindow->TriggerMouseWheelEvent(mw);
	}
	[super scrollWheel:event];
}

- (void) mouseMoved:(NSEvent*)event {
	[self generalMouseMoveHandler:event];
	[super mouseMoved:event];
}

- (void) mouseDown:(NSEvent*)event {
	Fast::MouseButtonEvent mb;
	mb.mButton = kMouseButtonLeft;
	mb.mAction = kMouseButtonActionPressed;
	mFastWindow->TriggerMouseButtonEvent(mb);
	[super mouseDown:event];	
}

- (void) mouseUp:(NSEvent*)event {
	Fast::MouseButtonEvent mb;
	mb.mButton = kMouseButtonLeft;
	mb.mAction = kMouseButtonActionReleased;
	mFastWindow->TriggerMouseButtonEvent(mb);
	[super mouseUp:event];
}

- (void) mouseDragged:(NSEvent*)event {
	[self generalMouseMoveHandler:event];
	[super mouseDragged:event];
}

- (void) rightMouseDown:(NSEvent*)event {
	Fast::MouseButtonEvent mb;
	mb.mButton = kMouseButtonRight;
	mb.mAction = kMouseButtonActionPressed;
	mFastWindow->TriggerMouseButtonEvent(mb);
	[super rightMouseDown:event];	
}

- (void) rightMouseUp:(NSEvent*)event {
	Fast::MouseButtonEvent mb;
	mb.mButton = kMouseButtonRight;
	mb.mAction = kMouseButtonActionReleased;
	mFastWindow->TriggerMouseButtonEvent(mb);
	[super rightMouseUp:event];
}

- (void) rightMouseDragged:(NSEvent*)event {
	[self generalMouseMoveHandler:event];
	[super rightMouseDragged:event];
}

- (void) otherMouseDown:(NSEvent*)event {
	switch ([event buttonNumber])
	{
	case 1:
		{
			Fast::MouseButtonEvent mb;
			mb.mButton = kMouseButtonMiddle;
			mb.mAction = kMouseButtonActionPressed;
			mFastWindow->TriggerMouseButtonEvent(mb);
		}
		break;
	case 3:
		{
			Fast::MouseWheelEvent mw;
			mw.mAction = kMouseWheelActionScrollLeft;
			mFastWindow->TriggerMouseWheelEvent(mw);
		}
		break;
	case 4:
		{
			Fast::MouseWheelEvent mw;
			mw.mAction = kMouseWheelActionScrollRight;
			mFastWindow->TriggerMouseWheelEvent(mw);
		}
		break;
	};
	[super otherMouseDown:event];
}

- (void) otherMouseUp:(NSEvent*)event {
	switch ([event buttonNumber])
	{
	case 1:
		{
			Fast::MouseButtonEvent mb;
			mb.mButton = kMouseButtonMiddle;
			mb.mAction = kMouseButtonActionPressed;
			mFastWindow->TriggerMouseButtonEvent(mb);
		}
		break;
	};
	[super otherMouseUp:event];
}

- (void) otherMouseDragged:(NSEvent*)event {
	[self generalMouseMoveHandler:event];
	[super otherMouseDragged:event];
}

- (void) ddhidJoystick:(DDHidJoystick*)joystick
		    buttonDown:(unsigned)buttonNumber
{
	if ([super isKeyWindow]) {
		Int gamepadID = -1; // TODO: Identify matching gamepadID
		mFastWindow->TriggerGamepadButtonEvent(GamepadButtonEvent(
			gamepadID, (Int)buttonNumber, kGamepadButtonActionPressed));
	}
}

- (void) ddhidJoystick:(DDHidJoystick*)joystick
		      buttonUp:(unsigned)buttonNumber
{
	if ([super isKeyWindow]) {
		Int gamepadID = -1; // TODO: Identify matching gamepadID
		mFastWindow->TriggerGamepadButtonEvent(GamepadButtonEvent(
			gamepadID, (Int)buttonNumber, kGamepadButtonActionReleased));
	}
}

- (void) ddhidJoystick:(DDHidJoystick*)joystick
		         stick:(unsigned)stick
		     otherAxis:(unsigned)otherAxis
		  valueChanged:(int)valueChanged
{
	if ([super isKeyWindow]) {
		Int gamepadID = -1; // TODO: Identify matching gamepadID
	}
}

- (void) ddhidJoystick:(DDHidJoystick*)joystick
		         stick:(unsigned)stick
		     povNumber:(unsigned)povNumber
		  valueChanged:(int)value
{
	if ([super isKeyWindow]) {
		Int gamepadID = -1; // TODO: Identify matching gamepadID
	}
}

- (void) ddhidJoystick:(DDHidJoystick*)joystick
		         stick:(unsigned)stick
		      yChanged:(int)value
{
	if ([super isKeyWindow]) {
		Int gamepadID = -1; // TODO: Identify matching gamepadID
	}
}

- (void) ddhidJoystick:(DDHidJoystick*)joystick
		         stick:(unsigned)stick
		      xChanged:(int)value
{
	if ([super isKeyWindow]) {
		Int gamepadID = -1; // TODO: Identify matching gamepadID
	}
}

@end
