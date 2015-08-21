/******************************************************************************/
/*                                                                            */
/*  QZInterface.cpp                                                           */
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
#include <Fast/Error.hpp>

#if defined(FastOSMacOSX)
#	include <ApplicationServices/ApplicationServices.h>
#	include <CoreFoundation/CoreFoundation.h>
#	include <IOKit/IOKitLib.h>
#	include <IOKit/graphics/IOGraphicsLib.h>
#	include <IOKit/graphics/IOGraphicsTypes.h>
#endif

#include "QZInterface.hpp"
#include "OpenGL.hpp"

#include "Undefs.hpp"

namespace Fast
{

#if defined(FastOSMacOSX)

	void QZDisplayChangedCallback(CGDirectDisplayID directDisplayID,
		CGDisplayChangeSummaryFlags flags, void *userInfo)
	{
		Display *display = (Display*)userInfo;
		display->RefreshMonitors();
		for (Int i = 0; i < display->GetMonitorCount(); i++)
			for (Int j = 0; j < display->GetMonitor(i)->GetWindowCount(); j++)
				display->GetMonitor(i)->GetWindow(j)->RefreshGeometry();
	}

	void QZRegisterDisplayChangeCallback(Display *display) {
		CGDisplayRegisterReconfigurationCallback(
			QZDisplayChangedCallback, (void*)display);
	}

	void QZUnregisterDisplayChangeCallback(Display *display) {
		CGDisplayRemoveReconfigurationCallback(
			QZDisplayChangedCallback, (void*)display);
	}

	UInt QZGetDisplayBitsPerPixel(UInt displayID, CGDisplayModeRef mode) {
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

	UInt QZGetDisplayID(UInt chaosScreenID) {
		CGDirectDisplayID displays[kFastMaxDisplays];
		UInt numDisplays;
		CGGetActiveDisplayList(kFastMaxDisplays, displays, &numDisplays);
		return displays[chaosScreenID];
	}

	void QZGetVideoModes(UInt displayID, Array<VideoMode> *modes) {
		CFArrayRef displayModes;
		modes->Clear();
		displayModes = CGDisplayCopyAllDisplayModes(displayID, 0);
		for (UInt i = 0; i < CFArrayGetCount(displayModes); i++) {
			CGDisplayModeRef mode =
				(CGDisplayModeRef)CFArrayGetValueAtIndex(displayModes, i);
			modes->Append(VideoMode(CGDisplayModeGetWidth(mode),
				CGDisplayModeGetHeight(mode),
				QZGetDisplayBitsPerPixel(displayID, mode),
				CGDisplayModeGetRefreshRate(mode)));
		}
		CFRelease(displayModes);
	}

	void QZGetCurrentVideoMode(UInt displayID, VideoMode *mode) {
		CGDisplayModeRef displayMode = CGDisplayCopyDisplayMode(displayID);
		mode->mWidth = CGDisplayModeGetWidth(displayMode);
		mode->mHeight = CGDisplayModeGetHeight(displayMode);
		mode->mBitsPerPixel = QZGetDisplayBitsPerPixel(displayID, displayMode);
		mode->mRefreshRate = CGDisplayModeGetRefreshRate(displayMode);
	}

	ErrorType QZSetVideoMode(UInt displayID, const VideoMode &vm) {
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
				QZGetDisplayBitsPerPixel(displayID, mode),
				CGDisplayModeGetRefreshRate(mode));
			if (vm == vmode) {
				match = i;
				break;
			}
		}
		// Set the mode
		sdmSuccess = CGDisplaySetDisplayMode(displayID, (CGDisplayModeRef)
			CFArrayGetValueAtIndex(displayModes, match), 0);
		CFRelease(displayModes);
		if (kCGErrorSuccess != sdmSuccess)
			return Error::Throw(kErrorVideoModeSetFailure,
				String("[%s(%u, %p): videoMode=(%dx%d:%dbpp@%dHz)]",
					FastFunctionName, displayID, &vm, vm.mWidth, vm.mHeight,
					vm.mBitsPerPixel, vm.mRefreshRate));
		return kErrorNone;
	}

	void QZGetMonitorRect(UInt displayID, Rectangle *rect) {
		CGRect selfRect = CGDisplayBounds(displayID);
		*rect = Rectangle(selfRect.origin.x, selfRect.origin.y,
			selfRect.size.width, selfRect.size.height);
	}

#endif

}