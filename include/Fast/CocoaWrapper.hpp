/******************************************************************************/
/*                                                                            */
/*  CocoaWrapper.hpp                                                          */
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

#ifndef FastCocoaWrapperHppIncluded
#define FastCocoaWrapperHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Window.hpp>
#include <Fast/WindowStyle.hpp>
#include <Fast/String.hpp>
#include <Fast/Point.hpp>
#include <Fast/Application.hpp>
#include <Fast/Array.hpp>
#include <Fast/VideoMode.hpp>

#define kFastMaxDisplays	10

namespace Fast
{
	class Window;
	struct CocoaWindowWrapper;
	struct CocoaAutoreleasePoolWrapper;
	
	class CocoaWindow
	{
	private:
		CocoaWindowWrapper	*mWin;
	public:
		CocoaWindow(Byte depthBits, Byte stencilBits, Window *window);
		~CocoaWindow();
		void		Show();
		void		CheckEvents();
		void		Display();
		void		SetCursorVisible(Bool isCursorVisible);
		void		MakeCurrent(Bool makeCurrent);
		void		SwapGraphicsBuffers();
		void		SetSize(Int width, Int height);
		Int			GetWidth() const;
		Int			GetHeight() const;
		WindowStyle	GetStyle() const;
		void		SetStyle(WindowStyle style);
		void		SetTitle(const String &title);
		void		SetSwapInterval(Int swapInterval);
		Bool		IsInFocus() const;
		void		TrapCursor(Bool trapCursor);
		Bool		IsCursorTrapped() const;
		Point		GetCursorPosition() const;
		void		MoveCursorTo(const Point &position);
		void		SetTypingMode(Bool typingMode);
		Bool		IsInTypingMode() const;
		String		GetTypedChars();
	};
	
	class CocoaAutoreleasePool
	{
	private:
		CocoaAutoreleasePoolWrapper	*mPool;
	public:
		CocoaAutoreleasePool();
		~CocoaAutoreleasePool();
	};
	
	namespace CocoaApplication
	{
		void Start();
		void Stop();
	}

	namespace CocoaDisplay
	{
		UInt		GetID(UInt screenID);
		void		GetName(UInt displayID, String *displayName);
		void		GetVideoModes(UInt displayID, Array<VideoMode> *modes);
		void		GetCurrentVideoMode(UInt displayID, VideoMode *mode);
		ErrorType	SetVideoMode(UInt displayID, const VideoMode &videoMode);
	}
}

#endif // FastCocoaWrapperHppIncluded
