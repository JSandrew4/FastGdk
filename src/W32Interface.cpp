/******************************************************************************/
/*                                                                            */
/*  W32Interface.cpp                                                          */
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
#include <Fast/Display.hpp>
#include <Fast/CharacterInputEvent.hpp>
#include <Fast/GamepadConnectionEvent.hpp>
#include <Fast/GamepadButtonEvent.hpp>
#include <Fast/GamepadStickAxisEvent.hpp>
#include <Fast/KeyEvent.hpp>
#include <Fast/MouseButtonEvent.hpp>
#include <Fast/MouseWheelEvent.hpp>
#include <Fast/MouseMoveEvent.hpp>
#include <Fast/MouseRawMoveEvent.hpp>
#include <Fast/KeyTranslator.hpp>
#include <Fast/StopWatch.hpp>
#if defined(FastOSWindows)
#	include <WindowsX.h>
#	define kFastDIDEventBufferSize		32
#	define kFastHidUsagePageGeneric	0x01
#	define kFastHidUsageGenericMouse	0x02
#	define DIRECTINPUT_VERSION			0x0800
#	include <dinput.h>
#	include <Xinput.h>
#endif

#include "W32Interface.hpp"

#include "Undefs.hpp"

#define FastConvertJoystickAxisValue(x) \
	(Int)(((65535.0 / 2000.0) * (Double)x) - 1000.0)

#define FastHandlePOVEvent(pov) { \
		if (pov < gamepad.GetCapabilities().mNumDirectionalPads) { \
			Bool o[] = { false, false, false, false }; \
			Bool n[] = { false, false, false, false }; \
			switch (didoData[i].dwData) { \
			case 0: \
				n[0] = true; \
				break; \
			case 4500: \
				n[0] = n[1] = true; \
				break; \
			case 9000: \
				n[1] = true; \
				break; \
			case 13500: \
				n[1] = n[2] = true; \
				break; \
			case 18000: \
				n[2] = true; \
				break; \
			case 22500: \
				n[2] = n[3] = true; \
				break; \
			case 27000: \
				n[3] = true; \
				break; \
			case 31500: \
				n[3] = n[0] = true; \
				break; \
			} \
			Int offset = (pov * 4); \
			for (Int i = 0; i < 4; i++) \
				o[i] = gamepad.IsButtonDown(offset+i); \
			for (Int i = 0; i < 4; i++) { \
				if (n[i] != o[i]) { \
					window->TriggerGamepadButtonEvent( \
						GamepadButtonEvent(gamepadID, offset+i, \
						n[i] ? kGamepadButtonActionPressed : \
						kGamepadButtonActionReleased)); \
				} \
			} \
		} \
	}

#define FastConvertXInputStickAxisValue(x) \
	(Int)((1000.0 / 32767.0) * (Double)x)

#define FastConvertXInputTriggerAxisValue(x) \
	(Int)(((2000.0 / 255.0) * (Double)x) - 1000.0)

namespace Fast
{

#if defined(FastOSWindows)

	Int W32FindBestPixelFormat(CHDC deviceContext) {
		HDC hdc;
		Int i;
		int maxPFD;
		PIXELFORMATDESCRIPTOR pfd;
		int bestColor;
		int bestDepth;
		int bestDepthID;
		Array<Int> matchingIDArray;
		Array<Int> bestColorIDArray;
		bestColor = bestDepth = bestDepthID = -1;
		hdc = (HDC)deviceContext;
		maxPFD = DescribePixelFormat(hdc, 0, 0, NULL);
		for (i = 0; i < maxPFD; i++) {
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			DescribePixelFormat(hdc, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
			if (pfd.dwFlags & PFD_DRAW_TO_WINDOW && pfd.dwFlags & PFD_SUPPORT_OPENGL &&
				pfd.dwFlags & PFD_DOUBLEBUFFER && 8 == pfd.cStencilBits &&
				PFD_TYPE_RGBA == pfd.iPixelType)
			{
				matchingIDArray.Append(i);
				if (pfd.cColorBits > bestColor)
					bestColor = pfd.cColorBits;
			}
		}
		for (int i = 0; i < matchingIDArray.GetElementCount(); i++) {
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			DescribePixelFormat(hdc, matchingIDArray[i], sizeof(PIXELFORMATDESCRIPTOR), &pfd);
			if (pfd.cColorBits == bestColor)
				bestColorIDArray.Append(matchingIDArray[i]);
		}
		for (int i = 0; i < bestColorIDArray.GetElementCount(); i++) {
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			DescribePixelFormat(hdc, bestColorIDArray[i], sizeof(PIXELFORMATDESCRIPTOR), &pfd);
			if (pfd.cDepthBits > bestDepth) {
				bestDepth = pfd.cDepthBits;
				bestDepthID = bestColorIDArray[i];
			}
		}
		if (-1 == bestDepth)
			return 0;
		return bestDepthID;
	}

	CHWND W32CreateWindow(Window *chaosWindow,
		const Rectangle &contentRect, WindowStyle style)
	{
		WNDCLASSEX wcex;
		RECT wndSize;
		DWORD dwStyle, dwExStyle;
		HWND hWnd;
		RAWINPUTDEVICE rid[1];
		// Set up window properties
		memset(&wcex, 0, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc = (WNDPROC)W32WindowProcedure;
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.hInstance = GetModuleHandle(0);
		wcex.hCursor = LoadCursor(0, IDC_ARROW);
		wcex.lpszClassName = L"Game";
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		// Get content rectangle
		W32GetStyleMasks(style, (Int*)&dwStyle, (Int*)&dwExStyle);
		wndSize.top = contentRect.mY;
		wndSize.left = contentRect.mX;
		wndSize.right = contentRect.mX + contentRect.mWidth;
		wndSize.bottom = contentRect.mY + contentRect.mHeight;
		AdjustWindowRectEx(&wndSize, dwStyle, false, dwExStyle);
		// Create generic window
		RegisterClassEx(&wcex);
		hWnd = CreateWindowEx(dwExStyle, L"Game", L"", dwStyle, wndSize.left,
			wndSize.top, (wndSize.right - wndSize.left),
			(wndSize.bottom - wndSize.top), 0, 0, GetModuleHandle(0), 0);
		if (!hWnd)
			return 0;
		UpdateWindow(hWnd);
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)chaosWindow);
		// Set up raw mMouse input
		rid[0].usUsagePage = kFastHidUsagePageGeneric;
		rid[0].usUsage = kFastHidUsageGenericMouse;
		rid[0].dwFlags = RIDEV_INPUTSINK;
		rid[0].hwndTarget = hWnd;
		RegisterRawInputDevices(rid, 1, sizeof(rid[0]));
		return (CHWND)hWnd;
	}

	void W32DestroyWindow(CHWND hwnd) {
		// Unregister raw input devices
		RAWINPUTDEVICE rid[1];
		rid[0].usUsagePage = kFastHidUsagePageGeneric;
		rid[0].usUsage = kFastHidUsageGenericMouse;
		rid[0].dwFlags = RIDEV_REMOVE;
		rid[0].hwndTarget = 0;
		RegisterRawInputDevices(rid, 1, sizeof(rid[0]));
		// Destroy the window
		DestroyWindow((HWND)hwnd);
	}

	void W32HandleEvents() {
		MSG msg;
		memset(&msg, 0, sizeof(msg));
		while (PeekMessage(&msg, 0, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CLRESULT __stdcall W32WindowProcedure(
		CHWND hwnd, UInt msg, CWPARAM wPrm, CLPARAM lPrm)
	{
		static KeyTranslator keyTranslator;
		Window *window = (Window*)GetWindowLongPtr((HWND)hwnd, GWL_USERDATA);
		if (window) {
			switch (msg)
			{
			case WM_CHAR:
				// TODO: Send UNICODE char to window
				//   if (isprint(wPrm)) window->typedChars += wPrm;
				window->TriggerCharacterInputEvent(CharacterInputEvent());
				return 0;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				{
					KeyEvent k;
					k.mKey = keyTranslator.GetKey((Int)wPrm);
					// If no defined key code, retrieve characters
					if (k.mKey.IsEmpty()) {
						UInt scanCode = (lPrm >> 16) & 0xFF;
						WChar characters[17];
						int error = -1;
						Byte keyboardState[256];
						GetKeyState(0); // Make sure key state is sync'd
						GetKeyboardState((PBYTE)keyboardState);
						// Handle character input
						if (window->IsInTypingMode()) {
							CharacterInputEvent ci;
							error = ToUnicode((WPARAM)wPrm, scanCode,
								(const BYTE*)keyboardState, characters, 17, 0);
							if (error == 1 && characters[0] != 0) {
								ci.mString = characters;
								window->TriggerCharacterInputEvent(ci);
							}
						}
						// Now for game input, remove modifiers
						keyboardState[VK_SHIFT] &= ~128;
						keyboardState[VK_LSHIFT] &= ~128;
						keyboardState[VK_RSHIFT] &= ~128;
						keyboardState[VK_CONTROL] &= ~128;
						keyboardState[VK_LCONTROL] &= ~128;
						keyboardState[VK_RCONTROL] &= ~128;
						keyboardState[VK_MENU] &= ~128;
						keyboardState[VK_LMENU] &= ~128;
						keyboardState[VK_RMENU] &= ~128;
						keyboardState[VK_LWIN] &= ~128;
						keyboardState[VK_RWIN] &= ~128;
						keyboardState[VK_CAPITAL] &= ~1;
						error = ToUnicode((WPARAM)wPrm, scanCode,
							(const BYTE*)keyboardState, characters, 17, 0);
						if (error != 1 || characters == 0)
							return 0;
						k.mKey = characters;
					}
					k.mAction = kKeyActionPressed;
					window->TriggerKeyEvent(k);
					return 0;
				}
			case WM_KEYUP:
			case WM_SYSKEYUP:
				{
					KeyEvent k;
					k.mKey = keyTranslator.GetKey((Int)wPrm);
					// If no defined key code, retrieve characters
					if (k.mKey.IsEmpty()) {
						UInt scanCode = (lPrm >> 16) & 0xFF;
						WChar characters[17];
						int error = -1;
						Byte keyboardState[256];
						GetKeyState(0); // Make sure key state is sync'd
						GetKeyboardState((PBYTE)keyboardState);
						// Remove modifiers
						keyboardState[VK_SHIFT] &= ~128;
						keyboardState[VK_LSHIFT] &= ~128;
						keyboardState[VK_RSHIFT] &= ~128;
						keyboardState[VK_CONTROL] &= ~128;
						keyboardState[VK_LCONTROL] &= ~128;
						keyboardState[VK_RCONTROL] &= ~128;
						keyboardState[VK_MENU] &= ~128;
						keyboardState[VK_LMENU] &= ~128;
						keyboardState[VK_RMENU] &= ~128;
						keyboardState[VK_LWIN] &= ~128;
						keyboardState[VK_RWIN] &= ~128;
						keyboardState[VK_CAPITAL] &= ~1;
						error = ToUnicode((WPARAM)wPrm, scanCode,
							(const BYTE*)keyboardState, characters, 17, 0);
						if (error != 1 || characters == 0)
							return 0;
						k.mKey = characters;
					}
					k.mAction = kKeyActionReleased;
					window->TriggerKeyEvent(k);
					return 0;
				}
			case WM_LBUTTONDOWN:
				{
					MouseButtonEvent mb;
					mb.mButton = kMouseButtonLeft;
					mb.mAction = kMouseButtonActionPressed;
					window->TriggerMouseButtonEvent(MouseButtonEvent(
						kMouseButtonLeft, kMouseButtonActionPressed));
					return 0;
				}
			case WM_LBUTTONUP:
				{
					MouseButtonEvent mb;
					mb.mButton = kMouseButtonLeft;
					mb.mAction = kMouseButtonActionReleased;
					window->TriggerMouseButtonEvent(MouseButtonEvent(
						kMouseButtonLeft, kMouseButtonActionReleased));
					return 0;
				}
			case WM_RBUTTONDOWN:
				{
					MouseButtonEvent mb;
					mb.mButton = kMouseButtonRight;
					mb.mAction = kMouseButtonActionPressed;
					window->TriggerMouseButtonEvent(MouseButtonEvent(
						kMouseButtonRight, kMouseButtonActionPressed));
					return 0;
				}
			case WM_RBUTTONUP:
				window->TriggerMouseButtonEvent(MouseButtonEvent(
					kMouseButtonRight, kMouseButtonActionReleased));
				return 0;
			case WM_MBUTTONDOWN:
				window->TriggerMouseButtonEvent(MouseButtonEvent(
					kMouseButtonMiddle, kMouseButtonActionPressed));
				return 0;
			case WM_MBUTTONUP:
				window->TriggerMouseButtonEvent(MouseButtonEvent(
					kMouseButtonMiddle, kMouseButtonActionReleased));
				return 0;
			case WM_MOUSEWHEEL:
				{
					MouseWheelEvent mw;
					if (GET_WHEEL_DELTA_WPARAM((WPARAM)wPrm) > 0)
						mw.mAction = kMouseWheelActionScrollUp;
					else if (GET_WHEEL_DELTA_WPARAM((WPARAM)wPrm) < 0)
						mw.mAction = kMouseWheelActionScrollDown;
					else return 1;
					window->TriggerMouseWheelEvent(mw);
					return 0;
				}
			case WM_MOUSEHWHEEL:
				{
					MouseWheelEvent mw;
					if (GET_WHEEL_DELTA_WPARAM((WPARAM)wPrm) > 0)
						mw.mAction = kMouseWheelActionScrollRight;
					else if (GET_WHEEL_DELTA_WPARAM((WPARAM)wPrm) < 0)
						mw.mAction = kMouseWheelActionScrollLeft;
					else return 1;
					window->TriggerMouseWheelEvent(mw);
					return 0;
				}
			case WM_MOUSEMOVE:
				window->TriggerMouseMoveEvent(
					MouseMoveEvent(Point(GET_X_LPARAM((LPARAM)lPrm),
						GET_Y_LPARAM((LPARAM)lPrm))));
				return 0;
			case WM_INPUT:
				{
					Int size = 40;
					static Byte lpb[40];
					GetRawInputData((HRAWINPUT)lPrm, RID_INPUT, lpb,
						(PUINT)&size, sizeof(RAWINPUTHEADER));
					RAWINPUT *raw = (RAWINPUT*)lpb;
					if (raw->header.dwType == RIM_TYPEMOUSE) {
						window->TriggerMouseRawMoveEvent(
							MouseRawMoveEvent(Point(raw->data.mouse.lLastX,
								raw->data.mouse.lLastY)));
					}
					return 0;
				}
			case WM_DEVICECHANGE:
				window->RefreshAttachedGamepads();
				return 0;
			case WM_DEVMODECHANGE:
				window->GetDisplay()->RefreshMonitors();
				window->RefreshGeometry();
				return 0;
			case WM_CLOSE:
				window->TriggerCloseEvent();
				return 0;
			};
		}
		return DefWindowProc((HWND)hwnd, msg, (WPARAM)wPrm, (LPARAM)lPrm);
	}

	void W32GetStyleMasks(WindowStyle style, Int *dwStyle, Int *dwExStyle) {
		switch (style)
		{
		case kWindowStyleNormal:
			*dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
				WS_MINIMIZEBOX;
			*dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			break;
		case kWindowStyleResizable:
			*dwStyle = WS_OVERLAPPEDWINDOW;
			*dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			break;
		case kWindowStyleBorderless:
			*dwStyle = WS_POPUP;
			*dwExStyle = WS_EX_APPWINDOW;
			break;
		case kWindowStyleFullscreen:
			*dwStyle = WS_POPUP;
			*dwExStyle = WS_EX_TOPMOST | WS_EX_APPWINDOW;
			return;
		}
	}

	void W32SetStyle(CHWND hwnd, Int dwStyle, Int dwExStyle) {
		SetWindowLongPtr((HWND)hwnd, GWL_STYLE, (DWORD)dwStyle);
		SetWindowLongPtr((HWND)hwnd, GWL_EXSTYLE, (DWORD)dwExStyle);
	}

	void W32SetWindowText(CHWND hwnd, const String &title) {
		SetWindowText((HWND)hwnd, title.GetWString().mData);
	}

	void W32SetWindowFrame(CHWND hwnd, const Rectangle &rect) {
		SetWindowPos((HWND)hwnd, HWND_TOP, rect.mX, rect.mY,
			rect.mWidth, rect.mHeight, SWP_FRAMECHANGED);
	}

	void W32ShowWindow(CHWND hwnd) {
		ShowWindow((HWND)hwnd, SW_SHOW);
	}

	void W32HideWindow(CHWND hwnd) {
		ShowWindow((HWND)hwnd, SW_HIDE);
	}

	void W32FrameToContentRect(Rectangle *frame, Int dwStyle, Int dwExStyle) {
		// Get size of frame first
		RECT size;
		size.left = size.top = 0;
		size.right = size.bottom = 100;
		AdjustWindowRectEx(&size, (DWORD)dwStyle, FALSE, (DWORD)dwExStyle);
		size.left *= -1;
		size.top *= -1;
		size.right -= 100;
		size.bottom -= 100;
		// Now use the sizes to adjust to the content rect
		frame->mX += size.left;
		frame->mY += size.top;
		frame->mWidth -= (size.left + size.right);
		frame->mHeight-= (size.top + size.bottom);
	}

	void W32ContentToFrameRect(Rectangle *content, Int dwStyle, Int dwExStyle) {
		RECT r;
		r.left = content->mX;
		r.top = content->mY;
		r.right = content->mX + content->mWidth;
		r.bottom = content->mY + content->mHeight;
		AdjustWindowRectEx(&r, (DWORD)dwStyle, FALSE, (DWORD)dwExStyle);
		content->mX = r.left;
		content->mY = r.top;
		content->mWidth = r.right - r.left;
		content->mHeight = r.bottom - r.top;
	}

	CHWND W32GetFocus() {
		return (CHWND)GetFocus();
	}

	void W32GetFrameRect(CHWND hwnd, Rectangle *rect) {
		RECT wndSize;
		GetWindowRect((HWND)hwnd, &wndSize);
		*rect = Rectangle(wndSize.left, wndSize.top,
			wndSize.right - wndSize.left, wndSize.bottom - wndSize.top);
	}

	void W32GetContentRect(CHWND hwnd, Rectangle *rect) {
		RECT wndSize;
		GetClientRect((HWND)hwnd, &wndSize);
		*rect = Rectangle(wndSize.left, wndSize.top,
			wndSize.right - wndSize.left, wndSize.bottom - wndSize.top);
	}

	void W32ShowCursor(Bool showCursor) {
		Int counter = 0;
		if (showCursor) {
			do {
				counter = ShowCursor(showCursor);
			} while (counter <= 0);
		}
		else {
			do {
				counter = ShowCursor(showCursor);
			} while (counter >= 0);
		}
	}

	void W32TrapCursor(CHWND hwnd, Bool trapCursor) {
		if (trapCursor) {
			RECT clientrc;
			POINT clientp;
			GetClientRect((HWND)hwnd, &clientrc);
			clientp.x = clientp.y = 0;
			ClientToScreen((HWND)hwnd, &clientp);
			clientrc.left = clientp.x;
			clientrc.top = clientp.y;
			clientrc.right += clientp.x;
			clientrc.bottom += clientp.y;
			ClipCursor(&clientrc);
		} else ClipCursor(0);
	}

	void W32SetCursorPosition(Int x, Int y) {
		SetCursorPos(x, y);
	}

	void W32GetCursorPosition(Int *x, Int *y) {
		POINT pt;
		GetCursorPos(&pt);
		*x = pt.x;
		*y = pt.y;
	}

	CLPDIRECTINPUT8 W32DirectInputCreate() {
		CLPDIRECTINPUT8 directInput = NULL;
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
			IID_IDirectInput8, &directInput, NULL);
		return directInput;
	}

	void W32DirectInputRelease(CLPDIRECTINPUT8 directInput) {
		((LPDIRECTINPUT8)directInput)->Release();
	}

	class W32EnumJoysticksArgs
	{
	public:
		CLPDIRECTINPUT8				mDirectInput;
		Array<GamepadDeviceInfo>	mGamepadDeviceInfo;
	};

	BOOL CALLBACK W32EnumJoysticksCallback(
		const DIDEVICEINSTANCE *instance, LPVOID args)
	{
		W32EnumJoysticksArgs *eja = (W32EnumJoysticksArgs*)args;
		LPDIRECTINPUTDEVICE8 directInputDevice = NULL;
		if (((LPDIRECTINPUT8)eja->mDirectInput)->CreateDevice(
			instance->guidInstance, &directInputDevice, NULL))
		{
			if (directInputDevice) {
				GamepadDeviceInfo gdi;
				gdi.mDeviceHandle = directInputDevice;
				gdi.mProductName = instance->tszProductName;
				// TODO: Get other device infos
				eja->mGamepadDeviceInfo.Append(gdi);
			}
			return DIENUM_CONTINUE;
		}
		return DIENUM_STOP;
	}

	Array<GamepadDeviceInfo> W32DirectInputGetAttachedDevices(
		CLPDIRECTINPUT8 directInput8)
	{
		W32EnumJoysticksArgs eja;
		eja.mDirectInput = (LPDIRECTINPUT8)directInput8;
		((LPDIRECTINPUT8)eja.mDirectInput)->EnumDevices(DI8DEVCLASS_GAMECTRL,
			W32EnumJoysticksCallback, &eja, DIEDBSFL_ATTACHEDONLY);
		return eja.mGamepadDeviceInfo;
	}

	ErrorType W32DirectInputDeviceSetUp(CLPDIRECTINPUTDEVICE8 device, CHWND hwnd) {
		if (FAILED(((LPDIRECTINPUTDEVICE8)device)->SetDataFormat(&c_dfDIJoystick)))
			return kErrorGeneric; // TODO
		if (FAILED(((LPDIRECTINPUTDEVICE8)device)->SetCooperativeLevel(
			(HWND)hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		{
			return kErrorGeneric; // TODO
		}
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj = NULL;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = kFastDIDEventBufferSize;
		if (FAILED(((LPDIRECTINPUTDEVICE8)device)->SetProperty(
			DIPROP_BUFFERSIZE, &dipdw.diph)))
		{
			return kErrorGeneric; // TODO
		}
		return kErrorNone;
	}

	void W32DirectInputDevicePoll(Int gamepadID, Window *window) {
		DIDEVICEOBJECTDATA didoData[kFastDIDEventBufferSize];
		DWORD eventCount = kFastDIDEventBufferSize;
		HRESULT hr = NULL;
		const Gamepad &gamepad = window->GetGamepad(gamepadID);
		LPDIRECTINPUTDEVICE8 did = (LPDIRECTINPUTDEVICE8)
			gamepad.GetDeviceInfo().mDeviceHandle;
		StopWatch sw;
		sw.Start();
		do {
			if (gamepad.IsConnected() && sw.GetElapsedSeconds() > 1.0f) {
				window->TriggerGamepadConnectionEvent(
					GamepadConnectionEvent(gamepadID, false));
				return;
			}
			hr = did->Acquire();
			if (!gamepad.IsConnected() && DIERR_INPUTLOST != hr) {
				window->TriggerGamepadConnectionEvent(
					GamepadConnectionEvent(gamepadID, true));
			}
		} while (DIERR_INPUTLOST == hr);
		if (FAILED(did->Poll()))
			return;
		if (FAILED(did->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
			didoData, &eventCount, 0)))
		{
			return;
		}
		for (DWORD i = 0; i < eventCount; i++) {
			switch (didoData[i].dwOfs) {
			case DIJOFS_X:
				if (gamepad.GetNumSticks() >= 1)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 0, kGamepadStickAxisX,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_Y:
				if (gamepad.GetNumSticks() >= 1)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 0, kGamepadStickAxisY,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_Z:
				if (gamepad.GetNumSticks() >= 1)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 0, kGamepadStickAxisOther,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_RX:
				if (gamepad.GetNumSticks() >= 2)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 1, kGamepadStickAxisX,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_RY:
				if (gamepad.GetNumSticks() >= 2)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 1, kGamepadStickAxisY,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_RZ:
				if (gamepad.GetNumSticks() >= 2)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 1, kGamepadStickAxisOther,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_SLIDER(0):
				if (gamepad.GetNumSticks() >= 3)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 2, kGamepadStickAxisX,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_SLIDER(1):
				if (gamepad.GetNumSticks() >= 3)
					window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
						gamepadID, 2, kGamepadStickAxisY,
						FastConvertJoystickAxisValue(didoData[i].dwData)));
				break;
			case DIJOFS_POV(0):
				FastHandlePOVEvent(0);
				break;
			case DIJOFS_POV(1):
				FastHandlePOVEvent(1);
				break;
			case DIJOFS_POV(2):
				FastHandlePOVEvent(2);
				break;
			case DIJOFS_POV(3):
				FastHandlePOVEvent(3);
				break;
			default:
				if (DIJOFS_BUTTON(0) <= didoData[i].dwOfs &&
					DIJOFS_BUTTON(32) > didoData[i].dwOfs)
				{
					Int button = (didoData[i].dwData - DIJOFS_BUTTON(0)) +
						(gamepad.GetCapabilities().mNumDirectionalPads * 4);
					window->TriggerGamepadButtonEvent(GamepadButtonEvent(
						gamepadID, button, button & 0x80 ?
						kGamepadButtonActionPressed :
						kGamepadButtonActionReleased));
				}
				break;
			}
		}
	}

	GamepadCapabilities W32DirectInputDeviceGetCapabilities(
		CLPDIRECTINPUTDEVICE8 device)
	{
		GamepadCapabilities gc;
		DIDEVCAPS devCaps;
		((LPDIRECTINPUTDEVICE8)device)->GetCapabilities(&devCaps);
		gc.mNumAxes = devCaps.dwAxes;
		gc.mNumRegularButtons = devCaps.dwButtons;
		gc.mNumDirectionalPads = devCaps.dwPOVs;
		return gc;
	}

	void W32DirectInputDeviceRelease(CLPDIRECTINPUTDEVICE8 device) {
		((LPDIRECTINPUTDEVICE8)device)->Release();
	}

	void W32XInputEnable(Bool enable) {
		// TODO: Apparently we don't need this in Xinput9_1_0???
		//XInputEnable((BOOL)enable);
	}

	void W32XInputGetState(Int gamepadID, Window *window) {
		XINPUT_STATE xis;
		const Gamepad& gamepad = window->GetGamepad(gamepadID);
		DWORD result = XInputGetState(gamepad.GetID(), &xis);
		if (ERROR_SUCCESS == result) {
			if (!gamepad.IsConnected())
				window->TriggerGamepadConnectionEvent(
					GamepadConnectionEvent(gamepadID, true));
			Int o[20], n[20];
			memset(o, 0, sizeof(Int)*20);
			memset(n, 0, sizeof(Int)*20);
			// Load up the old state
			for (Int i = 0; i < 14; i++)
				o[i] = (Int)gamepad.IsButtonDown(i);
			o[14] = gamepad.GetStickXAxis(0);
			o[15] = gamepad.GetStickYAxis(0);
			o[16] = gamepad.GetStickOtherAxis(0);
			o[17] = gamepad.GetStickXAxis(1);
			o[18] = gamepad.GetStickYAxis(1);
			o[19] = gamepad.GetStickOtherAxis(1);
			// Load up the new state
			n[ 0] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
			n[ 1] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
			n[ 2] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
			n[ 3] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
			n[ 4] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_START;
			n[ 5] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
			n[ 6] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
			n[ 7] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
			n[ 8] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
			n[ 9] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
			n[10] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_A;
			n[11] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_B;
			n[12] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_X;
			n[13] = xis.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
			n[14] = FastConvertXInputStickAxisValue(xis.Gamepad.sThumbLX);
			n[15] = FastConvertXInputStickAxisValue(xis.Gamepad.sThumbLY);
			n[16] = FastConvertXInputTriggerAxisValue(xis.Gamepad.bLeftTrigger);
			n[17] = FastConvertXInputStickAxisValue(xis.Gamepad.sThumbRX);
			n[18] = FastConvertXInputStickAxisValue(xis.Gamepad.sThumbRY);
			n[19] = FastConvertXInputTriggerAxisValue(xis.Gamepad.bRightTrigger);
			// Compare the two and trigger events as needed
			for (Int i = 0; i < 14; i++)
				if (n[i] != o[i])
					window->TriggerGamepadButtonEvent(GamepadButtonEvent(
						gamepadID, i, n[i] ? kGamepadButtonActionPressed :
						kGamepadButtonActionReleased));
			if (n[14] != o[14])
				window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
					gamepadID, 0, kGamepadStickAxisX, n[14]));
			if (n[15] != o[15])
				window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
					gamepadID, 0, kGamepadStickAxisY, n[15]));
			if (n[16] != o[16])
				window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
					gamepadID, 0, kGamepadStickAxisOther, n[16]));
			if (n[17] != o[17])
				window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
					gamepadID, 1, kGamepadStickAxisX, n[17]));
			if (n[18] != o[18])
				window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
					gamepadID, 0, kGamepadStickAxisY, n[18]));
			if (n[19] != o[19])
				window->TriggerGamepadStickAxisEvent(GamepadStickAxisEvent(
					gamepadID, 0, kGamepadStickAxisOther, n[19]));
		} else {
			if (gamepad.IsConnected())
				window->TriggerGamepadConnectionEvent(
					GamepadConnectionEvent(gamepadID, false));
		}
	}

#endif

}