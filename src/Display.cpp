/******************************************************************************/
/*                                                                            */
/*  Display.cpp                                                               */
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

#include <Fast/Display.hpp>
#include <Fast/Monitor.hpp>
#include <Fast/Point.hpp>
#include <Fast/Exception.hpp>

#if defined(FastOSWindows)
	// TODO
#elif defined(FastOSLinux)
#	include <X11/Xlib.h>
#	include <X11/extensions/Xrandr.h>
#elif defined(FastOSMacOSX)
#	include <ApplicationServices/ApplicationServices.h>
#endif

#include "QZInterface.hpp"
#include "NSInterface.hpp"

#include "Undefs.hpp"

namespace Fast
{

#if defined(FastOSWindows)

	struct DisplayEnumData
	{
		Int	mMainMonitorID;
		Int	mNumDisplays;
	};

	BOOL CALLBACK DisplayEnumNextMonitor
		(HMONITOR monitor, HDC hdc, LPRECT rect, LPARAM data)
	{
		DisplayEnumData *ded = (DisplayEnumData*)data;
		MONITORINFO mInfo;
		memset(&mInfo, 0, sizeof(MONITORINFO));
		mInfo.cbSize = sizeof(MONITORINFO);
		GetMonitorInfo(monitor, &mInfo);
		if (mInfo.dwFlags & MONITORINFOF_PRIMARY)
			ded->mMainMonitorID = ded->mNumDisplays;
		ded->mNumDisplays++;
		return TRUE;
	}

#endif

	Display::Display() {
		mMainMonitorID = -1;
		mXRRScreenResources = 0;
		mXRREventBase = 0;
		Int numDisplays = 0;
		// Get main display ID and number of monitors
	#if defined(FastOSWindows)
		DisplayEnumData ded;
		ded.mMainMonitorID = -1;
		ded.mNumDisplays = 0;
		EnumDisplayMonitors(0, 0, DisplayEnumNextMonitor, (LPARAM)&ded);
		mMainMonitorID = ded.mMainMonitorID;
		numDisplays = ded.mNumDisplays;
	#elif defined(FastOSLinux)
		mXDisplay = (CXDisplay*)XOpenDisplay(0);
		// Make sure we have the Xrandr extension and initialize
		Int xrrErrorBase;
		Int xrrExists = XRRQueryExtension((::Display*)mXDisplay,
			&mXRREventBase, &xrrErrorBase);
		if (!xrrExists)
			Exception::Throw(kExceptionX11InitializeRAndRFailure,
				String("(%s)", FastFunctionName));
		// Initialize
		mXRRScreenResources = (CXRRScreenResources*)XRRGetScreenResources(
			(::Display*)mXDisplay, XDefaultRootWindow((::Display*)mXDisplay));
		if (!mXRRScreenResources)
			Exception::Throw(kExceptionX11InitializeRAndRFailure,
				String("(%s)", FastFunctionName));
		numDisplays = ((XRRScreenResources*)mXRRScreenResources)->ncrtc;
		mMainMonitorID = 0;
	#elif defined(FastOSMacOSX)
		CGDirectDisplayID mainDisplay;
		CGDirectDisplayID displays[kFastMaxDisplays];
		CGGetActiveDisplayList(kFastMaxDisplays, displays, (UInt*)&numDisplays);
		mainDisplay = CGMainDisplayID();
		for (Int i = 0; i < numDisplays; i++)
			if (mainDisplay == displays[i])
				mMainMonitorID = i;
		QZRegisterDisplayChangeCallback(this);
	#endif
		if (mMainMonitorID == -1 || numDisplays == 0 ||
			mMainMonitorID >= numDisplays)
		{
			Exception::Throw(kExceptionMonitorEnumerationFailure,
				String("(%s)", FastFunctionName));
		}
		// Allocate Monitors
		for (Int i = 0; i < numDisplays; i++)
			mMonitorArray.Append(Monitor(this, i));
	}

	Display::~Display() {
		mMonitorArray.Clear();
	#if defined(FastOSLinux)
		XRRFreeScreenResources((XRRScreenResources*)mXRRScreenResources);
		XCloseDisplay((::Display*)mXDisplay);
	#elif defined(FastOSMacOSX)
		QZUnregisterDisplayChangeCallback(this);
	#endif
	}

	Int Display::GetMonitorCount() const {
		return mMonitorArray.GetElementCount();
	}

	Monitor* Display::GetMonitor(Int index) {
		return &mMonitorArray[index];
	}

	const Monitor& Display::GetMonitor(Int index) const {
		return mMonitorArray[index];
	}

	CXDisplay* Display::GetXDisplay() {
		return mXDisplay;
	}

	CXRRScreenResources* Display::GetXRRScreenResources() {
		return mXRRScreenResources;
	}

	Int Display::GetXRREventBase() const {
		return mXRREventBase;
	}

	Monitor* Display::GetMainMonitor() {
		return &mMonitorArray[mMainMonitorID];
	}

	const Monitor& Display::GetMainMonitor() const {
		return mMonitorArray[mMainMonitorID];
	}

	Monitor* Display::GetActiveMonitor() {
		Point ptMonitor;
	#if defined(FastOSWindows)
		POINT pt;
		GetCursorPos(&pt);
		ptMonitor = Point(pt.x, pt.y);
	#elif defined(FastOSLinux)
		::Window rootWindow, childWindow;
		Point ptWindow;
		UInt mask;
		XQueryPointer((::Display*)mXDisplay,
			XDefaultRootWindow((::Display*)mXDisplay), &rootWindow,
			&childWindow, &ptMonitor.mX, &ptMonitor.mY, &ptWindow.mX,
			&ptWindow.mY, &mask);
	#elif defined(FastOSMacOSX)
		CGEventRef evt = CGEventCreate(NULL);
		CGPoint pt = CGEventGetLocation(evt);
		ptMonitor = Point(pt.x, pt.y);
	#endif
		for (Int i = 0; i < mMonitorArray.GetElementCount(); i++)
			if (ptMonitor.IsInside(mMonitorArray[i].GetBounds()))
				return &mMonitorArray[i];
		return GetMainMonitor();
	}

	void Display::RefreshMonitors() {
		// TODO: Need to figure out how to gracefully delete and recreate
		//	current screens without screwing up all the external pointers
		//	to these screens. Some kind of shared pointer type deal?
	}
}
