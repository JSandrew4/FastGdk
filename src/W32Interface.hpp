/******************************************************************************/
/*                                                                            */
/*  W32Interface.hpp                                                          */
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

#ifndef FastW32InterfaceHppIncluded
#define FastW32InterfaceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Window.hpp>
#include <Fast/WindowStyle.hpp>
#include <Fast/Rectangle.hpp>
#include <Fast/Array.hpp>
#include <Fast/GamepadDeviceInfo.hpp>

namespace Fast
{
#if defined(FastOSWindows)
	extern Int						W32FindBestPixelFormat(CHDC deviceContext);
	extern CHWND					W32CreateWindow(Window *fastWindow,
										const Rectangle &contentRect,
										WindowStyle style);
	extern void						W32DestroyWindow(CHWND hwnd);
	extern void						W32HandleEvents();
	extern CLRESULT __stdcall		W32WindowProcedure(CHWND hwnd, UInt msg,
										CWPARAM wPrm, CLPARAM lPrm);
	extern void						W32GetStyleMasks(WindowStyle style,
										Int *dwStyle, Int *dwExStyle);
	extern void						W32SetStyle(CHWND hwnd,
										Int dwStyle, Int dwExStyle);
	extern void						W32SetWindowText(CHWND hwnd,
										const String &title);
	extern void						W32SetWindowFrame(CHWND hwnd,
										const Rectangle &rect);
	extern void						W32ShowWindow(CHWND hwnd);
	extern void						W32HideWindow(CHWND hwnd);
	extern void						W32FrameToContentRect(Rectangle *frame,
										Int dwStyle, Int dwExStyle);
	extern void						W32ContentToFrameRect(
										Rectangle *content,
										Int dwStyle, Int dwExStyle);
	extern CHWND					W32GetFocus();
	extern void						W32GetFrameRect(CHWND hwnd,
										Rectangle *rect);
	extern void						W32GetContentRect(CHWND hwnd,
										Rectangle *rect);
	extern void						W32ShowCursor(Bool showCursor);
	extern void						W32TrapCursor(CHWND hwnd,
										Bool trapCursor);
	extern void						W32SetCursorPosition(Int x, Int y);
	extern void						W32GetCursorPosition(Int *x, Int *y);
	extern CLPDIRECTINPUT8			W32DirectInputCreate();
	extern void						W32DirectInputRelease(
										CLPDIRECTINPUT8 directInput);
	extern Array<GamepadDeviceInfo>	W32DirectInputGetAttachedDevices(
										CLPDIRECTINPUT8 directInput);
	extern ErrorType				W32DirectInputDeviceSetUp(
										JoystickDeviceHandle handle,
										CHWND hwnd);
	extern void						W32DirectInputDevicePoll(Int gamepadID,
										Window *window);
	extern GamepadCapabilities		W32DirectInputDeviceGetCapabilities(
										JoystickDeviceHandle handle);
	extern void						W32DirectInputDeviceRelease(
										JoystickDeviceHandle handle);
	extern void						W32XInputEnable(Bool enable);
	extern void						W32XInputGetState(Int gamepadID,
										Window *window);
#endif
}

#endif // FastW32InterfaceHppIncluded