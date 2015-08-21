/******************************************************************************/
/*                                                                            */
/*  CocoaWrapper.mm                                                           */
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
#include <Fast/CocoaWrapper.hpp>

#include "Undefs.hpp"

namespace Fast
{
	struct CocoaWindowWrapper
	{
		FastNSWindow	*mFastNSWindow;
	};

	struct CocoaAutoreleasePoolWrapper
	{
		NSAutoreleasePool	*mNSPool;
	};

	CocoaWindow::CocoaWindow(Byte depthBits,
		Byte stencilBits, Window *window)
	{
		mWin = new CocoaWindowWrapper;
		NSRect frame = NSMakeRect(0, 0, 640, 480);
		mWin->mFastNSWindow = [[FastNSWindow alloc]
			initWithFastWindow:window
			contentRect:frame
			styleMask:NSTitledWindowMask|NSClosableWindowMask|
				NSMiniaturizableWindowMask|NSResizableWindowMask
			backing:NSBackingStoreBuffered
			defer:NO];
	}

	CocoaWindow::~CocoaWindow() {
		[mWin->mFastNSWindow release];
		delete mWin;
	}

	void CocoaWindow::Show() {
		NSRect centerRect = NSMakeRect(
			([mWin->mFastNSWindow screen].frame.size.width -
			[mWin->mFastNSWindow frame].size.width) / 2,
			([mWin->mFastNSWindow screen].frame.size.height -
			[mWin->mFastNSWindow frame].size.height) / 2,
			[mWin->mFastNSWindow frame].size.width,
			[mWin->mFastNSWindow frame].size.height);
		[mWin->mFastNSWindow setFrame:centerRect display:YES animate:NO];
		[mWin->mFastNSWindow makeKeyAndOrderFront:NSApp];
	}

	void CocoaWindow::CheckEvents() {
		[mWin->mFastNSWindow CheckEvents];
	}

	void CocoaWindow::Display() {
		[mWin->mFastNSWindow display];
	}

	void CocoaWindow::SetCursorVisible(Bool isCursorVisible) {
		[mWin->mFastNSWindow SetCursorVisible:isCursorVisible];
	}

	void CocoaWindow::MakeCurrent(Bool makeCurrent) {
		[mWin->mFastNSWindow MakeCurrent:makeCurrent];
	}

	void CocoaWindow::SwapGraphicsBuffers() {
		[mWin->mFastNSWindow SwapGraphicsBuffers];
	}

	void CocoaWindow::SetSize(Int width, Int height) {
		
	}

	Int CocoaWindow::GetWidth() const {
		return 0;
	}

	Int CocoaWindow::GetHeight() const {
		return 0;
	}

	WindowStyle CocoaWindow::GetStyle() const {
		return kWindowStyleNormal;
	}

	void CocoaWindow::SetStyle(WindowStyle style) {
		
	}

	void CocoaWindow::SetTitle(const String &title) {
		[mWin->mFastNSWindow setTitle:
			[NSString stringWithUTF8String:title.GetData()]];
	}

	void CocoaWindow::SetSwapInterval(Int swapInterval) {
		[mWin->mFastNSWindow SetSwapInterval:swapInterval];
	}

	Bool CocoaWindow::IsInFocus() const {
		return ([NSApp keyWindow] == mWin->mFastNSWindow);
	}

	void CocoaWindow::TrapCursor(Bool trapCursor) {
		
	}

	Bool CocoaWindow::IsCursorTrapped() const {
		return false;
	}

	Point CocoaWindow::GetCursorPosition() const {
		return Point(0,0);
	}

	void CocoaWindow::MoveCursorTo(const Point &position) {
		[mWin->mFastNSWindow MoveCursorTo:position];
	}

	void CocoaWindow::SetTypingMode(Bool typingMode) {
		
	}

	Bool CocoaWindow::IsInTypingMode() const {
		return false;
	}

	String CocoaWindow::GetTypedChars() {
		return String();
	}

	CocoaAutoreleasePool::CocoaAutoreleasePool() {
		mPool = new CocoaAutoreleasePoolWrapper;
		mPool->mNSPool = [[NSAutoreleasePool alloc] init];
	}

	CocoaAutoreleasePool::~CocoaAutoreleasePool() {
		[mPool->mNSPool release];
		delete mPool;
	}

	namespace CocoaScreen
	{
		void KeyArrayCallback(const void *key,
			const void *value, void *context)
		{
			CFArrayAppendValue((CFMutableArrayRef)context, key);	
		}

		String GetDisplayName(CGDirectDisplayID id) {
			String retString;
			CFStringRef localName = 0;
			io_connect_t displayPort = CGDisplayIOServicePort(id);
			CFDictionaryRef dict = (CFDictionaryRef)
				IODisplayCreateInfoDictionary(displayPort, 0);
			CFDictionaryRef names = (CFDictionaryRef)
				CFDictionaryGetValue(dict, CFSTR(kDisplayProductName));
			if (names)
			{
				CFArrayRef langKeys = CFArrayCreateMutable(
					kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);
				CFDictionaryApplyFunction(names,
					CocoaScreen::KeyArrayCallback, (void*)langKeys);
				CFArrayRef orderLangKeys =
					CFBundleCopyPreferredLocalizationsFromArray(langKeys);
				if(orderLangKeys && CFArrayGetCount(orderLangKeys))
				{
					CFStringRef langKey =
						(CFStringRef)CFArrayGetValueAtIndex(orderLangKeys, 0);
					localName = (CFStringRef)CFDictionaryGetValue(names, langKey);
					Long maxLength =
						CFStringGetMaximumSizeOfFileSystemRepresentation(localName);
					retString.Reserve(maxLength);
					CFStringGetFileSystemRepresentation(
						localName, (Char*)retString.GetData(), maxLength);
					retString.Resize(strlen(retString.GetData()));
				}
				CFRelease(langKeys);
				CFRelease(orderLangKeys);
			}
			CFRelease(dict);
			return retString;
		}
	}
	
	namespace CocoaDisplay
	{
		UInt GetID(UInt screenID) {
			CGDirectDisplayID displays[kFastMaxDisplays];
			UInt numDisplays;
			CGGetActiveDisplayList(kFastMaxDisplays, displays, &numDisplays);
			return displays[screenID];
		}

		void GetName(UInt displayID, String *displayName) {
			displayName->Assign(CocoaScreen::GetDisplayName(displayID));
		}

		UInt GetBitsPerPixel(UInt displayID, CGDisplayModeRef mode) {
			size_t depth = 0;
			CFStringRef pixelEncoding = CGDisplayModeCopyPixelEncoding(mode);
			String pe;
			Long maxLength =
				CFStringGetMaximumSizeOfFileSystemRepresentation(pixelEncoding);
			pe.Reserve(maxLength);
			CFStringGetFileSystemRepresentation(
				pixelEncoding, (Char*)pe.GetData(), maxLength);
			pe.Resize(strlen(pe.GetData()));
			CFRelease(pixelEncoding);
			if (pe == IO32BitDirectPixels)
				depth = 32;
			else if (pe == IO16BitDirectPixels)
				depth = 16;
			else if (pe == IO8BitIndexedPixels)
				depth = 8;
			return (UInt)depth;
		}

		void GetVideoModes(UInt displayID, Array<VideoMode> *modes) {
			CFArrayRef displayModes;
			modes->Clear();
			displayModes = CGDisplayCopyAllDisplayModes(displayID, 0);
			for (UInt i = 0; i < CFArrayGetCount(displayModes); i++) {
				CGDisplayModeRef mode =
					(CGDisplayModeRef)CFArrayGetValueAtIndex(displayModes, i);
				modes->Append(VideoMode(CGDisplayModeGetWidth(mode),
					CGDisplayModeGetHeight(mode),
					CocoaDisplay::GetBitsPerPixel(displayID, mode),
					CGDisplayModeGetRefreshRate(mode)));
			}
			CFRelease(displayModes);
		}

		void GetCurrentVideoMode(UInt displayID, VideoMode *mode) {
			CGDisplayModeRef displayMode = CGDisplayCopyDisplayMode(displayID);
			mode->mWidth = CGDisplayModeGetWidth(displayMode);
			mode->mHeight = CGDisplayModeGetHeight(displayMode);
			mode->mBitsPerPixel =
				CocoaDisplay::GetBitsPerPixel(displayID, displayMode);
			mode->mRefreshRate = CGDisplayModeGetRefreshRate(displayMode);
		}

		ErrorType SetVideoMode(
			UInt displayID, const VideoMode &videoMode)
		{
			CGError sdmSuccess;
			Int match = -1;
			CFArrayRef displayModes;
			displayModes = CGDisplayCopyAllDisplayModes(displayID, 0);
			// Find the screen size & refresh rate matching our VideoMode size
			for (UInt i = 0; i < CFArrayGetCount(displayModes); i++) {
				CGDisplayModeRef mode =
					(CGDisplayModeRef)CFArrayGetValueAtIndex(displayModes, i);
				VideoMode vmode = VideoMode(
					CGDisplayModeGetWidth(mode), CGDisplayModeGetHeight(mode),
					CocoaDisplay::GetBitsPerPixel(displayID, mode),
					CGDisplayModeGetRefreshRate(mode));
				if (videoMode == vmode) {
					match = i;
					break;
				}
			}
			// Set the mode
			sdmSuccess = CGDisplaySetDisplayMode(displayID,
				(CGDisplayModeRef)CFArrayGetValueAtIndex(displayModes, match), 0);
			CFRelease(displayModes);
			if (kCGErrorSuccess != sdmSuccess)
				return kErrorGeneric; // FIXME
			return kErrorNone;
		}
	}

	namespace CocoaApplication
	{
		void Start() {
			[NSApplication sharedApplication];
			NSObject<NSApplicationDelegate> *appDelegate =
				[[NSObject<NSApplicationDelegate> alloc] init];
			[NSApp setDelegate:appDelegate];
			[NSApp finishLaunching];
		}

		void Stop() {
			[NSApp stop:nil];
		}
	}
}
