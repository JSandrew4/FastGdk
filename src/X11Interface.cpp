/******************************************************************************/
/*                                                                            */
/*  X11Interface.cpp                                                          */
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

#if defined(FastOSLinux)
#	include <X11/Xlib.h>
#	include <X11/Xatom.h>
#	include <X11/Xutil.h>
#	include <X11/cursorfont.h>
#	include <X11/extensions/XInput2.h>
#	include <X11/extensions/Xrandr.h>
#	include <unistd.h>
#endif
#include <cstdlib>
#include <cstring>

#include "X11Interface.hpp"
#include "OpenGL.hpp"

#include "Undefs.hpp"

namespace Fast
{

#if defined(FastOSLinux)

	CXWindow X11CreateWindow(CXDisplay *display, CGLXFBConfig glXFBConfig,
		const Rectangle &contentRect)
	{
		XVisualInfo				*xVisualInfo;
		XSetWindowAttributes	xSetWindowAttributes;
		Atom					xaWMDeleteWindow;
		::Window				window;
		// Get visual
		xVisualInfo = glXGetVisualFromFBConfig(
			(::Display*)display, (GLXFBConfig)glXFBConfig);
		if (!xVisualInfo)
			return 0;
		// Set up window attributes
		xSetWindowAttributes.border_pixel = 0;
		xSetWindowAttributes.event_mask = StructureNotifyMask;
		xSetWindowAttributes.colormap = XCreateColormap((::Display*)display,
			(::Window)X11GetRootWindow(display),
			xVisualInfo->visual, AllocNone);
		// Create window
		window = (CXWindow)XCreateWindow((::Display*)display,
			(::Window)X11GetRootWindow(display), contentRect.mX,
			contentRect.mY, contentRect.mWidth, contentRect.mHeight,
			0, xVisualInfo->depth, InputOutput, xVisualInfo->visual,
			CWBorderPixel | CWColormap | CWEventMask, &xSetWindowAttributes);
		if (!window)
			return 0;
		// Set other window properties
		xaWMDeleteWindow = (Atom)X11InternAtom(display, "WM_DELETE_WINDOW");
		XSetWMProtocols((::Display*)display,
			(::Window)window, &xaWMDeleteWindow, 1);
		XSelectInput((::Display*)display, (::Window)window, PointerMotionMask |
			KeyPressMask | KeyReleaseMask | KeymapStateMask |
			ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);
		XRRSelectInput((::Display*)display, (::Window)window,
			RRScreenChangeNotifyMask);
		XFree(xVisualInfo);
		return window;
	}

	void X11DestroyWindow(CXDisplay *display, CXWindow window) {
		XDestroyWindow((::Display*)display, (::Window)window);
	}

	void X11HandleEvents(CXDisplay *display, CXWindow window,
		Window *fastWindow, Int xiOpCode, Int xrrEventBase)
	{
		static KeyTranslator keyTranslator;
		XEvent xEvent;
		// First handle events whose window matches our's
		//   and whose events have a mask
		while (XCheckWindowEvent((::Display*)display,
			(::Window)window, ButtonPressMask | ButtonReleaseMask |
			PointerMotionMask | KeyPressMask | KeyReleaseMask, &xEvent))
		{
			if (RRScreenChangeNotify == (xEvent.type - xrrEventBase)) {
				XRRUpdateConfiguration(&xEvent);
				fastWindow->GetDisplay()->RefreshMonitors();
				fastWindow->RefreshGeometry();
				continue;
			}
			switch (xEvent.type)
			{
			case MotionNotify:
				{
					MouseMoveEvent mm;
					mm.mPosition.mX = xEvent.xmotion.x;
					mm.mPosition.mY = xEvent.xmotion.y;
					fastWindow->TriggerMouseMoveEvent(mm);
				}
				break;
			case ButtonPress:
				{
					MouseButtonEvent mb;
					mb.mAction = kMouseButtonActionPressed;
					mb.mButton = kMouseButtonNone;
					switch (xEvent.xbutton.button)
					{
					case 1:
						mb.mButton = kMouseButtonLeft;
						break;
					case 2:
						mb.mButton = kMouseButtonMiddle;
						break;
					case 3:
						mb.mButton = kMouseButtonRight;
						break;
					case 4:
						{
							MouseWheelEvent mw;
							mw.mAction = kMouseWheelActionScrollUp;
							fastWindow->TriggerMouseWheelEvent(mw);
						}
						break;
					case 5:
						{
							MouseWheelEvent mw;
							mw.mAction = kMouseWheelActionScrollDown;
							fastWindow->TriggerMouseWheelEvent(mw);
						}
						break;
					case 6:
						{
							MouseWheelEvent mw;
							mw.mAction = kMouseWheelActionScrollLeft;
							fastWindow->TriggerMouseWheelEvent(mw);
						}
					case 7:
						{
							MouseWheelEvent mw;
							mw.mAction = kMouseWheelActionScrollRight;
							fastWindow->TriggerMouseWheelEvent(mw);
						}
					};
					if (mb.mButton)
						fastWindow->TriggerMouseButtonEvent(mb);
				}
				break;
			case ButtonRelease:
				{
					MouseButtonEvent mb;
					mb.mAction = kMouseButtonActionReleased;
					mb.mButton = kMouseButtonNone;
					switch (xEvent.xbutton.button)
					{
					case 1:
						mb.mButton = kMouseButtonLeft;
						break;
					case 2:
						mb.mButton = kMouseButtonMiddle;
						break;
					case 3:
						mb.mButton = kMouseButtonRight;
						break;
					};
					if (mb.mButton)
						fastWindow->TriggerMouseButtonEvent(mb);
				}
				break;
			case KeymapNotify:
				XRefreshKeyboardMapping(&xEvent.xmapping);
				break;
			case KeyPress:
				{
					KeyEvent	k;
					Char		characters[17];
					Int			length;
					Int			keysym;
					// First look for a keycode (insert, f1, pause, etc.)
					keysym = (Int)(XLookupKeysym(&xEvent.xkey, 0) & 0xff);
					k.mKey = keyTranslator.GetKey(keysym);
					// If no keycode exists, get the key character
					if (k.mKey.IsEmpty()) {
						// First check for character input
						if (fastWindow->IsInTypingMode()) {
							CharacterInputEvent ci;
							length = XLookupString(&xEvent.xkey, characters,
								17, (KeySym*)&keysym, 0);
							if (length > 0 && characters[0] != 0) {
								ci.mString = characters;
								fastWindow->TriggerCharacterInputEvent(ci);
							}
						}
						// Now game input, remove modifiers
						xEvent.xkey.state &= ~ShiftMask;
						xEvent.xkey.state &= ~ControlMask;
						length = XLookupString(&xEvent.xkey, characters,
							17, (KeySym*)&keysym, 0);
						if (length == 0 || characters[0] == 0)
							break;
						k.mKey = characters;
					}
					k.mAction = kKeyActionPressed;
					fastWindow->TriggerKeyEvent(k);
				}
				break;
			case KeyRelease:
				{
					// Ignore auto-repeat's key up events
					Bool isReleased = true;
					if (XEventsQueued((::Display*)display, QueuedAfterReading))
					{
						XEvent nEvent;
						XPeekEvent((::Display*)display, &nEvent);
						if (nEvent.type == KeyPress &&
							nEvent.xkey.time == xEvent.xkey.time &&
							nEvent.xkey.keycode == xEvent.xkey.keycode)
						{
							isReleased = false;
						}
					}
					if (isReleased) {
						KeyEvent	k;
						Char		characters[17];
						Int			length;
						Int			keysym;
						// First look for a keysym (insert, f1, pause, etc.)
						keysym = (Int)(XLookupKeysym(&xEvent.xkey, 0) & 0xff);
						k.mKey = keyTranslator.GetKey(keysym);
						// If no keysym exists, get the key character
						if (k.mKey.IsEmpty()) {
							// Remove modifiers
							xEvent.xkey.state &= ~ShiftMask;
							xEvent.xkey.state &= ~ControlMask;
							length = XLookupString(&xEvent.xkey, characters,
								17, (KeySym*)&keysym, 0);
							if (length == 0 || characters[0] == 0)
								break;
							k.mKey = characters;
						}
						k.mAction = kKeyActionReleased;
						fastWindow->TriggerKeyEvent(k);
					}
				}
				break;
			};
		}
		// ClientMessage has no mask, search by type and window
		while (XCheckTypedWindowEvent((::Display*)display,
			(::Window)window, ClientMessage, &xEvent))
		{
			if (xEvent.xclient.data.l[0] ==
				(Atom)X11InternAtom(display, "WM_DELETE_WINDOW"))
			{
				fastWindow->TriggerCloseEvent();
			}
		}
		// Lastly, handle raw input events (no mask and no window)
		while (XCheckTypedEvent((::Display*)display, GenericEvent, &xEvent)) {
			XGenericEventCookie *xgec =
				(XGenericEventCookie*)&xEvent.xcookie;
			if (xgec->type = GenericEvent && xgec->extension == xiOpCode) {
				if (XGetEventData((::Display*)display, xgec)) {
					XIRawEvent *xiRawEvent = (XIRawEvent*)xgec->data;
					if (xgec->evtype == XI_RawMotion) {
						MouseRawMoveEvent mrm;
						mrm.mMovement = Point((Int)*(xiRawEvent->raw_values),
							(Int)-(*(xiRawEvent->raw_values+1)));
						fastWindow->TriggerMouseRawMoveEvent(mrm);
					}
					XFreeEventData((::Display*)display, xgec);
				}
			}
		}
	}

	Int X11InitializeInput(CXDisplay *display) {
		XIEventMask	xiEventMask;
		int			xiEventBase;
		int			xiErrorBase;
		Bool		xiExists;
		int			xiOpCode;

		xiExists = XQueryExtension((::Display*)display, "XInputExtension",
			&xiOpCode, &xiEventBase, &xiErrorBase);
		if (xiExists) {
			xiEventMask.mask_len = XIMaskLen(XI_RawMotion);
			xiEventMask.mask =
				(unsigned char *)calloc(xiEventMask.mask_len, 1);
			xiEventMask.deviceid = XIAllMasterDevices;
			memset(xiEventMask.mask, 0, xiEventMask.mask_len);
			XISetMask(xiEventMask.mask, XI_RawMotion);
			XISelectEvents((::Display*)display,
				(::Window)X11GetRootWindow(display),
				&xiEventMask, 1);
			XFree(xiEventMask.mask);
			return xiOpCode;
		}
		return 0;
	}

	Int X11DefaultScreen(CXDisplay *display) {
		return DefaultScreen((::Display*)display);
	}

	CGLXFBConfig* X11ChooseFBConfigs(CXDisplay *display, int glXFBConfigCount) {
		GLXFBConfig *glXFBConfigs = NULL;
		for (Int i = 0; i <= 1 && !glXFBConfigs; i++) {
			for (Int j = 1; j <= 3 && !glXFBConfigs; j++) {
				const int attribs[] = {
					GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
					GLX_RENDER_TYPE,	GLX_RGBA_BIT,
					GLX_DOUBLEBUFFER,	True,
					GLX_RED_SIZE,		8,
					GLX_GREEN_SIZE,		8,
					GLX_BLUE_SIZE,		8,
					GLX_ALPHA_SIZE,		8 - (i * 8),
					GLX_DEPTH_SIZE,		32 / j,
					GLX_STENCIL_SIZE,	8,
					None
				};
				glXFBConfigs = glXChooseFBConfig((::Display*)display,
					X11DefaultScreen(display), attribs, &glXFBConfigCount);
			}
		}
		return (CGLXFBConfig*)glXFBConfigs;
	}

	CGLXFBConfig X11BestFBConfig(CXDisplay *display,
		Int glXFBConfigCount, CGLXFBConfig *glXFBConfigs)
	{
		Int bestGLXFBConfigID = -1, bestSampleCount = -1;
		for (Int i = 0; i < glXFBConfigCount; i++) {
			int sampleBuffers, samples;
			glXGetFBConfigAttrib((::Display*)display,
				glXFBConfigs[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
			glXGetFBConfigAttrib((::Display*)display,
				glXFBConfigs[i], GLX_SAMPLES, &samples);
			if (bestGLXFBConfigID < 0 || sampleBuffers &&
				samples > bestSampleCount)
			{
				bestGLXFBConfigID = i;
				bestSampleCount = samples;
			}
		}
		return glXFBConfigs[bestGLXFBConfig];
	}

	CXAtom X11InternAtom(CXDisplay *display, const char *atom) {
		return (CXAtom)XInternAtom((::Display*)display, atom, False);
	}

	void X11Sync(CXDisplay *display) {
		XSync((::Display*)display, False);
	}

	void X11SyncDismissEvents(CXDisplay *display) {
		XSync((::Display*)display, True);
	}

	void X11Flush(CXDisplay *display) {
		XFlush((::Display*)display);
	}

	void X11SetWindowType(CXDisplay *display, CXWindow window,
		const char *netWmWindowType)
	{
		Atom wmPropertyType =
			(Atom)X11InternAtom(display, "_NET_WM_WINDOW_TYPE");
		if (netWmWindowType) {
			Atom wmProperty = (Atom)X11InternAtom(display, netWmWindowType);
			XChangeProperty((::Display*)display, (::Window)window,
				wmPropertyType, XA_ATOM, 32, PropModeReplace,
				(unsigned char*)&wmProperty, 1);
		} else {
			XDeleteProperty((::Display*)display,
				(::Window)window, wmPropertyType);
		}
		X11Flush(display);
	}

	CXWindow X11GetRootWindow(CXDisplay *display) {
		return (CXWindow)RootWindow((::Display*)display,
			X11DefaultScreen(display));
	}

	void X11TrapCursor(CXDisplay *display, CXWindow window) {
		XGrabPointer((::Display*)display,
			(::Window)X11GetRootWindow(display),
			True, 0, GrabModeAsync, GrabModeAsync, window,
			None, CurrentTime);
	}

	void X11StoreName(CXDisplay *display, CXWindow window, const String &title)
	{
		XStoreName((::Display*)display, (::Window)window, title.GetData());
	}

	void X11UntrapCursor(CXDisplay *display) {
		XUngrabPointer((::Display*)display, CurrentTime);
	}

	void X11ShowCursor(CXDisplay *display, CXWindow window, bool showCursor) {
		if (showCursor) {
			XUndefineCursor((::Display*)display, (::Window)window);
		} else {
			XColor clr;
			Pixmap pxm = XCreatePixmap((::Display*)display,
				(::Window)window, 1, 1, 1);
			Pixmap msk = XCreatePixmap((::Display*)display,
				(::Window)window, 1, 1, 1);
			XDefineCursor((::Display*)display, (::Window)window,
				XCreatePixmapCursor((::Display*)display,
					pxm, msk, &clr, &clr, 1, 1));
		}
	}

	void X11SetCursorPosition(CXDisplay *display, Int x, Int y) {
		XWarpPointer(
			(::Display*)display, None, (::Window)X11GetRootWindow(display),
			0, 0, 0, 0, x, y);
	}

	void X11GetCursorPosition(CXDisplay *display,
		CXWindow window, Int *x, Int *y)
	{
		::Window winRoot, winChild;
		Int xWin, yWin;
		UInt mask;
		XQueryPointer((::Display*)display, (::Window)window, &winRoot,
			&winChild, x, y, &xWin, &yWin, &mask);
	}

	CXWindow X11GetFocus(CXDisplay *display) {
		::Window focus;
		int revert;
		XGetInputFocus((::Display*)display, &focus, &revert);
		return (CXWindow)focus;
	}

	void X11SetWindowState(CXDisplay *display, CXWindow window,
		const char *netWmState, bool setState)
	{
		Atom wmPropertyType = (Atom)X11InternAtom(display, "_NET_WM_STATE");
		Atom wmProperty = (Atom)X11InternAtom(display, netWmState);
		XEvent xEvent;
		memset(&xEvent, 0, sizeof(XEvent));
		xEvent.xclient.type = ClientMessage;
		xEvent.xclient.send_event = True;
		xEvent.xclient.window = (::Window)window;
		xEvent.xclient.message_type = wmPropertyType;
		xEvent.xclient.format = 32;
		xEvent.xclient.data.l[0] = (wmProperty && setState);
		xEvent.xclient.data.l[1] = wmProperty;
		xEvent.xclient.data.l[2] = 0;
		xEvent.xclient.data.l[3] = 1;
		xEvent.xclient.data.l[4] = 0;
		XSendEvent((::Display*)display,
			(::Window)X11GetRootWindow(display),
			False, SubstructureRedirectMask | SubstructureNotifyMask, &xEvent);
		X11Flush(display);
	}

	void X11GetScreenCoords(CXDisplay *display, CXWindow window,
		Int screen, Int *x, Int *y)
	{
		Int srcX = *x;
		Int srcY = *y;
		::Window ret;
		XTranslateCoordinates((::Display*)display, (::Window)window,
			X11GetRootWindow(display), srcX, srcY, x, y, &ret);
	}

	void X11GetFrameExtents(CXDisplay *display, CXWindow window,
		Int *left, Int *right, Int *top, Int *bottom)
	{
		Atom xaNetFrameExtents;
		Atom xaActualType;
		Int actualFormat;
		unsigned long numItems;
		unsigned long bytesAfter;
		Int *data;
		Int result;
		data = 0;
		xaNetFrameExtents = (Atom)X11InternAtom(display, "_NET_FRAME_EXTENTS");
		result = XGetWindowProperty((::Display*)display, (::Window)window,
			xaNetFrameExtents, 0, 4, False, XA_CARDINAL, &xaActualType,
			&actualFormat, &numItems, &bytesAfter, (unsigned char**)&data);
		if (result != Success || !data) {
			*top = 0;
			*bottom = 0;
			*left = 0;
			*right = 0;
		} else {
			*left = data[0];
			*right = data[1];
			*top = data[2];
			*bottom = data[3];
			XFree(data);
		}
	}

	void X11GetFrameGeometry(CXDisplay *display, CXWindow window,
		Int *x, Int *y, Int *w, Int *h)
	{
		::Window root_return;
		unsigned int border_width_return, depth_return;
		XGetGeometry((::Display*)display, (::Window)window, &root_return,
			x, y, (unsigned int*)w, (unsigned int*)h,
			&border_width_return, &depth_return);
		Int left, right, top, bottom;
		X11GetFrameExtents(display, window, &left, &right, &top, &bottom);
		*x -= left;
		*y -= top;
		*w += left + right;
		*h += top + bottom;
	}

	void X11GetClientGeometry(CXDisplay *display, CXWindow window,
		Int *x, Int *y, Int *w, Int *h)
	{
		::Window root_return;
		unsigned int border_width_return, depth_return;
		XGetGeometry((::Display*)display, (::Window)window, &root_return,
			x, y, (unsigned int*)w, (unsigned int*)h,
			&border_width_return, &depth_return);
	}

	void X11MoveResize(CXDisplay *display, CXWindow window,
		Int x, Int y, Int w, Int h)
	{
		// The (x,y) of the window is the top left of the frame
		// The width and height is the size of the client area
		// So we need to modify the x and y based on the frame size
		Int left, right, top, bottom;
		X11GetFrameExtents(display, window, &left, &right, &top, &bottom);
		XMoveResizeWindow((::Display*)display, (::Window)window,
			x - left, y - top, w, h);
		// Wait for the move and resize event to register before we return
		for (Int i = 0; i < 250; i++) {
			Int wx, wy, ww, wh;
			X11Flush(display);
			X11GetClientGeometry(display, window, &wx, &wy, &ww, &wh);
			if (x == wx && y == wy && w == ww && h == wh)
				break;
			usleep(10000); // Poll at 10 ms intervals
		}
		X11Flush(display);
	}

	void X11SetWindowResizable(CXDisplay *display,
		CXWindow window, bool resizable)
	{
		XSizeHints *xSizeHints = XAllocSizeHints();
		Int x = 0, y = 0, w = 0, h = 0;
		if (resizable) {
			xSizeHints->flags = 0;
			xSizeHints->min_width = xSizeHints->max_width = 0;
			xSizeHints->min_height = xSizeHints->max_height = 0;
		} else {
			X11GetClientGeometry(display, window, &x, &y, &w, &h);
			xSizeHints->flags = (PMinSize | PMaxSize);
			xSizeHints->min_width = xSizeHints->max_width = w;
			xSizeHints->min_height = xSizeHints->max_height = h;
		}
		XSetWMNormalHints((::Display*)display, (::Window)window, xSizeHints);
		XFree(xSizeHints);
		X11Flush(display);
	}

	void X11ShowWindow(CXDisplay *display, CXWindow window) {
		XUnmapWindow((::Display*)display, (::Window)window);
		XMapRaised((::Display*)display, (::Window)window);
		// Wait for the window to actually map
		XEvent xEvent;
		while (true) {
			XNextEvent((::Display*)display, &xEvent);
			if (xEvent.type == MapNotify && xEvent.xmap.window == window)
				break;
		}
		X11Flush(display);
	}

	void X11HideWindow(CXDisplay *display, CXWindow window) {
		X11Flush(display);
		XUnmapWindow((::Display*)display, (::Window)window);
	}

	void X11Free(void *ptr) {
		XFree(ptr);
	}

#endif

}