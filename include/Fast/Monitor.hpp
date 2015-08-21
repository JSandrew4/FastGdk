/******************************************************************************/
/*                                                                            */
/*  Monitor.hpp                                                               */
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

#ifndef FastMonitorHppIncluded
#define FastMonitorHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/VideoMode.hpp>
#include <Fast/Rectangle.hpp>

namespace Fast
{
	class Display;
	class Window;

	class FastApi Monitor
	{
	private:
		CXRRCrtcInfo		*mXRRCrtcInfo;
		Int					mMacMonitorID;
		String				mWin32DeviceName;
		Display				&mDisplay;
		Array<Window*>		mWindowArray;
		Int					mID;
		VideoMode			mOriginalVideoMode;
		Array<VideoMode>	mVideoModeArray;
		Rectangle			mBounds;
		Bool				mIsMainMonitor;
		// Hide this function. No assigning screens!
		Monitor&	operator=(const Monitor &that);
	public:
		// (Con/De)structors
		Monitor(Display *display, Int id);
		Monitor(const Monitor &that);
		~Monitor();
		// Getters
		Int						GetWindowCount() const;
		Window*					GetWindow(Int id);
		const Window&			GetWindow(Int id) const;
		Int						GetID() const;
		VideoMode				GetCurrentVideoMode();
		Int						GetVideoModeCount() const;
		const VideoMode&		GetVideoMode(Int index) const;
		const Array<VideoMode>&	GetVideoModes() const;
		const Rectangle&		GetBounds() const;
		Bool					IsMainMonitor() const;
		Bool					IsActiveMonitor() const;
		// Misc
		void		AddWindow(Window *window);
		void		RemoveWindow(Window *window);
		ErrorType	SetVideoMode(const VideoMode &videoMode);
	};
}

#endif // FastMonitorHppIncluded
