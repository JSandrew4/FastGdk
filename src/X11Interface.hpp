/******************************************************************************/
/*                                                                            */
/*  X11Interface.hpp                                                          */
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

#ifndef FastX11InterfaceHppIncluded
#define FastX11InterfaceHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class String;
	class Rectangle;
	class Window;

#if defined(FastOSLinux)
	
	extern CXWindow		X11CreateWindow(CXDisplay *display,
							CGLXFBConfig glXFBConfig,
							const Rectangle &contentRect);
	extern void			X11DestroyWindow(CXDisplay *display, CXWindow window);
	extern void			X11HandleEvents(CXDisplay *display, CXWindow window,
							Window *chaosWindow, Int xiOpCode);
	extern Int			X11InitializeInput(CXDisplay *display);
	extern Int			X11DefaultScreen(CXDisplay *display);
	extern CGLXFBConfig*X11ChooseFBConfigs(CXDisplay *display,
							int numFBConfigs,
							char depthBits, char stencilBits);
	extern CGLXFBConfig	X11BestFBConfig(CXDisplay *display, Int numFBConfigs,
							CGLXFBConfig *glXFBConfigs);
	extern CXAtom		X11InternAtom(CXDisplay *display, const char *atom);
	extern void			X11Sync(CXDisplay *display);
	extern void			X11SyncDismissEvents(CXDisplay *display);
	extern void			X11Flush(CXDisplay *display);
	extern void			X11SetWindowType(CXDisplay *display, CXWindow window,
							const char *netWmWindowType);
	extern CXWindow		X11GetRootWindow(CXDisplay *display);
	extern void			X11StoreName(CXDisplay *display, CXWindow window,
							const String &title);
	extern void			X11TrapCursor(CXDisplay *display, CXWindow window);
	extern void			X11UntrapCursor(CXDisplay *display);
	extern void			X11ShowCursor(CXDisplay *display,
							CXWindow window, bool showCursor);
	extern void			X11SetCursorPosition(CXDisplay *display, Int x, Int y);
	extern void			X11GetCursorPosition(CXDisplay *display,
							CXWindow window, Int *x, Int *y);
	extern CXWindow		X11GetFocus(CXDisplay *display);
	extern void			X11SetWindowState(CXDisplay *display, CXWindow window,
							const char *netWmState, bool setState);
	extern void			X11GetScreenCoords(CXDisplay *display, CXWindow window,
							Int screen, Int *x, Int *y);
	extern void			X11GetFrameExtents(CXDisplay *display, CXWindow window,
							Int *left, Int *right, Int *top, Int *bottom);
	extern void			X11GetFrameGeometry(CXDisplay *display,
							CXWindow window, Int *x, Int *y, Int *w, Int *h);
	extern void			X11GetClientGeometry(CXDisplay *display,
							CXWindow window, Int *x, Int *y, Int *w, Int *h);
	extern void			X11MoveResize(CXDisplay *display, CXWindow window,
							Int x, Int y, Int w, Int h);
	extern void			X11SetWindowResizable(CXDisplay *display,
							CXWindow window, bool resizable);
	extern void			X11ShowWindow(CXDisplay *display, CXWindow window);
	extern void			X11HideWindow(CXDisplay *display, CXWindow window);
	extern void			X11Free(void *ptr);

#endif

}

#endif // FastX11InterfaceHppIncluded