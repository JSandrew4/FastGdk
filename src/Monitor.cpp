/******************************************************************************/
/*                                                                            */
/*  Monitor.cpp                                                               */
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

#include <Fast/Monitor.hpp>
#include <Fast/Display.hpp>
#include <Fast/Window.hpp>
#include <Fast/Exception.hpp>
#include <Fast/Error.hpp>

#if defined(FastOSWindows)
#	include <wchar.h>
#elif defined(FastOSLinux)
#	include <X11/Xlib.h>
#	include <X11/extensions/Xrandr.h>
#endif

#include "QZInterface.hpp"

#include "Undefs.hpp"

namespace Fast
{

#if defined(FastOSWindows)

	struct MonitorEnumData
	{
		MONITORINFOEX	mMonitorInfo;
		Int				mMonitorID;
		Int				mIndex;
	};

	BOOL CALLBACK MonitorEnumNextMonitor
		(HMONITOR monitor, HDC hdc, LPRECT rect, LPARAM data)
	{
		MonitorEnumData *sed = (MonitorEnumData*)data;
		if (sed->mIndex == sed->mMonitorID) {
			memset(&sed->mMonitorInfo, 0, sizeof(MONITORINFOEX));
			sed->mMonitorInfo.cbSize = sizeof(MONITORINFOEX);
			GetMonitorInfo(monitor, &sed->mMonitorInfo);
		}
		sed->mIndex++;
		return TRUE;
	}

#endif	

	Monitor::Monitor(Display *display, Int id) :
		mDisplay(*display)
	{
		mID = id;
		mMacMonitorID = 0;
	#if defined(FastOSWindows)
		// Initialize
		DWORD mode = 0;
		DEVMODE dm;
		memset(&dm, 0, sizeof(DEVMODE));
		dm.dmSize = sizeof(DEVMODE);
		// Get monitor info
		MonitorEnumData sed;
		sed.mMonitorID = mID;
		sed.mIndex = 0;
		EnumDisplayMonitors(0, 0, MonitorEnumNextMonitor, (LPARAM)&sed);
		if (mID >= sed.mIndex)
			Exception::Throw(kExceptionMonitorIDOutOfRange,
				String("[%s(%p, %d)]", FastFunctionName, display, mID));
		mWin32DeviceName = sed.mMonitorInfo.szDevice;
		// Get available video modes
		while (EnumDisplaySettings(sed.mMonitorInfo.szDevice, mode++, &dm))
			mVideoModeArray.Append(VideoMode(dm.dmPelsWidth, dm.dmPelsHeight,
				dm.dmBitsPerPel, dm.dmDisplayFrequency));
		mBounds = Rectangle(sed.mMonitorInfo.rcMonitor.left,
			sed.mMonitorInfo.rcMonitor.top,
			sed.mMonitorInfo.rcMonitor.right - sed.mMonitorInfo.rcMonitor.left,
			sed.mMonitorInfo.rcMonitor.bottom - sed.mMonitorInfo.rcMonitor.top);
	#elif defined(FastOSLinux)
		XRRScreenResources *xrrScreenResources =
			(XRRScreenResources*)mDisplay->GetXRRScreenResources();
		::Display *xdisplay = (::Display*)mDisplay->GetXDisplay();
		// Get monitor info
		mXRRCrtcInfo = (XRRCrtcInfo*)XRRGetCrtcInfo(xdisplay,
			xrrScreenResources, xrrScreenResources->crtcs[mID]);
		XRRCrtcInfo *xrrCrtcInfo = (XRRCrtcInfo*)mXRRCrtcInfo;
		if (!xrrCrtcInfo)
			Exception::Throw(kExceptionMonitorEnumerationFailure,
				String("[%s(%p, %d)]", FastFunctionName, display, mID));
		// Enumerate outputs
		for (Int i = 0; i < xrrCrtcInfo->noutput; i++) {
			XRROutputInfo *xrrOutputInfo = XRRGetOutputInfo(xdisplay,
				xrrScreenResources, xrrCrtcInfo->outputs[i]);
			if (!xrrOutputInfo)
				Exception::Throw(kExceptionMonitorEnumerationFailure,
					String("[%s(%p, %d)]", FastFunctionName, display, mID));
			// Enumerate video modes on output
			Int numModes = xrrOutputInfo->nmode;
			for (Int j = 0; j < numModes; j++) {
				RRMode mode = xrrOutputInfo->modes[j];
				// Enumerate monitor's supported video modes for an ID match
				for (Int k = 0; k < xrrScreenResources->nmode; k++) {
					XRRModeInfo &xrrModeInfo = xrrScreenResources->modes[k];
					if (mode == xrrModeInfo.id) {
						// Match found! Add to list of available video modes
						mVideoModeArray.Append(VideoMode(xrrModeInfo.width,
							xrrModeInfo.height, XDefaultDepth(xdisplay, mID),
							(Int)(xrrModeInfo.dotClock /
							(xrrModeInfo.hTotal * xrrModeInfo.vTotal))));
					}
				}
			}
			XRRFreeOutputInfo(xrrOutputInfo);
		}
		mBounds = Rectangle(xrrCrtcInfo->x, xrrCrtcInfo->y,
			xrrCrtcInfo->width, xrrCrtcInfo->height);
	#elif defined(FastOSMacOSX)
		mMacMonitorID = QZGetDisplayID(mID);
		QZGetVideoModes(mMacMonitorID, &mVideoModeArray);
		QZGetMonitorRect(mMacMonitorID, &mBounds);
	#endif
		mOriginalVideoMode = GetCurrentVideoMode();
	}

	Monitor::Monitor(const Monitor &that) :
		mDisplay(that.mDisplay)
	{
		Monitor(&that.mDisplay, that.mID);
	}

	Monitor::~Monitor() {
		if (GetCurrentVideoMode() != mOriginalVideoMode)
			SetVideoMode(mOriginalVideoMode);
	#if defined(FastOSLinux)
		XRRFreeCrtcInfo((XRRCrtcInfo*)mXRRCrtcInfo);
	#endif
	}

	Int Monitor::GetWindowCount() const {
		return mWindowArray.GetElementCount();
	}

	Window* Monitor::GetWindow(Int id) {
		return mWindowArray[id];
	}

	const Window& Monitor::GetWindow(Int id) const {
		return *mWindowArray[id];
	}

	Int Monitor::GetID() const {
		return mID;
	}

	VideoMode Monitor::GetCurrentVideoMode() {
	#if defined(FastOSWindows)
		DEVMODE dm;
		memset(&dm, 0, sizeof(DEVMODE));
		dm.dmSize = sizeof(DEVMODE);
		EnumDisplaySettingsEx(mWin32DeviceName.GetWString().mData,
			ENUM_CURRENT_SETTINGS, &dm, 0);
		return VideoMode(dm.dmPelsWidth, dm.dmPelsHeight,
			dm.dmBitsPerPel, dm.dmDisplayFrequency);
	#elif defined(FastOSLinux)
		XRRScreenResources *xrrScreenResources =
			(XRRScreenResources*)mDisplay->GetXRRScreenResources();
		::Display *xdisplay = (::Display*)mDisplay->GetXDisplay();
		RRMode mode = ((XRRCrtcInfo*)mXRRCrtcInfo)->mode;
		// Find matching mode ID
		for (Int i = 0; i < xrrScreenResources->nmode; i++) {
			if (mode == xrrScreenResources->modes[i].id) {
				XRRModeInfo &xrrModeInfo = xrrScreenResources->modes[i];
				return VideoMode(xrrModeInfo.width, xrrModeInfo.height,
					XDefaultDepth(xdisplay, mID), (Int)(xrrModeInfo.dotClock /
					(xrrModeInfo.hTotal * xrrModeInfo.vTotal)));
			}
		}
		return VideoMode();
	#elif defined(FastOSMacOSX)
		VideoMode vm;
		QZGetCurrentVideoMode(mMacMonitorID, &vm);
		return vm;
	#endif
	}

	Int Monitor::GetVideoModeCount() const {
		return mVideoModeArray.GetElementCount();
	}

	const VideoMode& Monitor::GetVideoMode(Int index) const {
		return mVideoModeArray[index];
	}

	const Array<VideoMode>& Monitor::GetVideoModes() const {
		return mVideoModeArray;
	}

	const Rectangle& Monitor::GetBounds() const {
		return mBounds;
	}

	Bool Monitor::IsMainMonitor() const {
		return (mDisplay.GetMainMonitor()->mID == mID);
	}

	Bool Monitor::IsActiveMonitor() const {
		return (mDisplay.GetActiveMonitor()->mID == mID);
	}

	void Monitor::AddWindow(Window *window) {
		mWindowArray.Append(window);
		if (window->GetParentMonitor() != this)
			window->SetParentMonitor(this);
	}

	void Monitor::RemoveWindow(Window *window) {
		for (Int i = 0; i < mWindowArray.GetElementCount(); i++)
			if (mWindowArray[i] == window)
				mWindowArray.Erase(i);
	}

	ErrorType Monitor::SetVideoMode(const VideoMode &videoMode) {
		if (GetCurrentVideoMode() == videoMode)
			return kErrorNone;
	#if defined(FastOSWindows)
		LONG cdsStatus;
		DEVMODE dm;
		memset(&dm, 0, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmBitsPerPel = videoMode.mBitsPerPixel;
		dm.dmPelsWidth = videoMode.mWidth;
		dm.dmPelsHeight = videoMode.mHeight;
		dm.dmDisplayFrequency = videoMode.mRefreshRate;
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH |
			DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		cdsStatus = ChangeDisplaySettingsEx(
			mWin32DeviceName.GetWString().mData, &dm, 0, CDS_FULLSCREEN, 0);
		if (DISP_CHANGE_SUCCESSFUL != cdsStatus)
			return Error::Throw(kErrorVideoModeSetFailure,
				String("[%s(%p): videoMode=(%dx%d:%dbpp@%dHz)]",
				FastFunctionName, &videoMode, videoMode.mWidth,
				videoMode.mHeight, videoMode.mBitsPerPixel,
				videoMode.mRefreshRate));
	#elif defined(FastOSLinux)
		Status xrrStatus;
		XRRScreenResources *xrrScreenResources =
			(XRRScreenResources*)mDisplay->GetXRRScreenResources();
		::Display *xdisplay = (::Display*)mDisplay->GetXDisplay();
		XRRCrtcInfo *xrrCrtcInfo = (XRRCrtcInfo*)mXRRCrtcInfo;
		// Find a matching video mode
		for (Int i = 0; i < xrrScreenResources->nmode; i++) {
			XRRModeInfo &xrrModeInfo = xrrScreenResources->modes[i];
			if (xrrModeInfo.width == videoMode.mWidth &&
				xrrModeInfo.height == videoMode.mHeight &&
				(Int)(xrrModeInfo.dotClock / (xrrModeInfo.hTotal *
				xrrModeInfo.vTotal)) == videoMode.mRefreshRate)
			{
				// Match found! Now find the matching mode ID from our outputs
				for (Int j = 0; j < xrrCrtcInfo->noutput; j++) {
					XRROutputInfo *xrrOutputInfo = XRRGetOutputInfo(
						xdisplay, xrrScreenResources, xrrCrtcInfo->outputs[j]);
					for (Int k = 0; k < xrrOutputInfo->nmode; k++) {
						if (xrrOutputInfo->modes[k] == xrrModeInfo.id) {
							// ID match found! Set the mode
							xrrStatus = XRRSetCrtcConfig(xdisplay,
								xrrScreenResources,
								xrrScreenResources->crtcs[mID], CurrentTime,
								xrrCrtcInfo->x, xrrCrtcInfo->y,
								xrrModeInfo.id, xrrCrtcInfo->rotation,
								xrrCrtcInfo->outputs, xrrCrtcInfo->noutput);
							if (Success != xrrStatus) {
								XRRFreeOutputInfo(xrrOutputInfo);
								return Error::Throw(kErrorVideoModeSetFailure,
									String("[%s(%p): videoMode=(%dx%d:%dbpp@%dHz)]",
									FastFunctionName, &videoMode, videoMode.mWidth,
									videoMode.mHeight, videoMode.mBitsPerPixel,
									videoMode.mRefreshRate));
							}
						}
					}
					XRRFreeOutputInfo(xrrOutputInfo);
				}
			}
		}
		XFlush(xdisplay);
	#elif defined(FastOSMacOSX)
		return QZSetVideoMode(mMacMonitorID, videoMode);
	#endif
		return kErrorNone;
	}
}
