/******************************************************************************/
/*                                                                            */
/*  Window.cpp                                                                */
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

#include <Fast/Window.hpp>
#include <Fast/Display.hpp>
#include <Fast/Exception.hpp>
#include <Fast/Error.hpp>
#include <Fast/VideoMode.hpp>
#include <Fast/Display.hpp>
#include <Fast/Monitor.hpp>
#include <Fast/Clipboard.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/CharacterInputEvent.hpp>
#include <Fast/KeyEvent.hpp>
#include <Fast/MouseButtonEvent.hpp>
#include <Fast/MouseWheelEvent.hpp>
#include <Fast/MouseMoveEvent.hpp>
#include <Fast/MouseRawMoveEvent.hpp>
#include <Fast/GamepadStickAxisEvent.hpp>
#include <Fast/GamepadConnectionEvent.hpp>
#include <Fast/GamepadButtonAction.hpp>
#include <Fast/GamepadButtonEvent.hpp>
#include <Fast/FileSystem.hpp>

#include "OpenGL.hpp"
#include "W32Interface.hpp"
#include "X11Interface.hpp"
#include "NSInterface.hpp"
#include "QZInterface.hpp"

#include "Undefs.hpp"

namespace Fast
{
	Window::Window(Display *display, Int multisampleCount) :
		mDisplay(*display),
		mParentMonitor(display->GetMainMonitor()),
		mTargetContentRectangle(mParentMonitor->GetBounds().mX,
			mParentMonitor->GetBounds().mY, 640, 480),
		mIsVisible(false),
		mTargetStyle(kWindowStyleNormal),
		mStyle(kWindowStyleNormal),
		mTitle("ChangeMe"),
		mIsCursorVisible(true),
		mIsCursorTrapped(false),
		mIsInTypingMode(false),
	#if defined(FastOSWindows)
		mHwnd(W32CreateWindow(this, mTargetContentRectangle, mStyle)),
		mDirectInput(W32DirectInputCreate()),
	#elif defined(FastOSLinux)
		mXDisplay(mDisplay.GetXDisplay()),
		mGLXFBConfigCount(0),
		mGLXFBConfigs(X11ChooseFBConfigs(mXDisplay, &mGLXFBConfigCount)),
		mGLXFBConfig(X11BestFBConfig(
			mXDisplay, mGLXFBConfigCount, mGLXFBConfigs)),
		mXWindow(X11CreateWindow(mXDisplay,
			mGLXFBConfig, mTargetContentRectangle)),
		mXIOpCode(X11InitializeInput(mXDisplay)),
	#elif defined(FastOSMacOSX)
		mNSWindow(NSCreateWindow(this)),
	#endif
		mClipboard(this),
		mGraphicsContext(this, mTargetContentRectangle, multisampleCount),
		mGuiRootContainer(this)
	{
		mParentMonitor->AddWindow(this);
	#if defined(FastOSWindows)
		// TODO: Move the following into their respective functions?
		//	Or wrap into W32Window class?...
		if (!mHwnd)
			Exception::Throw(kExceptionWindowCreationFailure,
				String("[%s()]", FastFunctionName));
		if (!mDirectInput)
			Exception::Throw(kExceptionGeneric, // TODO
				String("[%s()]", FastFunctionName));
	#elif defined(FastOSLinux)
		if (!mXDisplay)
			Exception::Throw(kExceptionX11OpenDisplayFailure,
				String("(%s)", FastFunctionName));
		if (!mGLXFBConfigs)
			Exception::Throw(kExceptionOpenGLNoValidFBConfigs,
				String("(%s)", FastFunctionName));
		if (!mXWindow)
			Exception::Throw(kExceptionWindowCreationFailure,
				String("(%s)", FastFunctionName));
		if (!mXIOpCode)
			Exception::Throw(kExceptionX11InitializeInputFailure,
				String("(%s)", FastFunctionName));
	#elif defined(FastOSMacOSX)
		if (!mNSWindow)
			Exception::Throw(kExceptionWindowCreationFailure,
				String("(%s)", FastFunctionName));
	#endif
		RefreshAttachedGamepads();
		SetTitle(mTitle);
	}

	Window::~Window() {
	#if defined(FastOSWindows)
		for (Int i = 4; i < mGamepads.GetElementCount(); i++)
			W32DirectInputDeviceRelease(
				mGamepads[i].GetDeviceInfo().mDeviceHandle);
		W32DirectInputRelease(mDirectInput);
		mParentMonitor->RemoveWindow(this);
		W32DestroyWindow(mHwnd);
	#elif defined(FastOSLinux)
		X11SyncDismissEvents(mXDisplay);
		X11DestroyWindow(mXDisplay, mXWindow);
		X11Free(mGLXFBConfigs);
	#elif defined(FastOSMacOSX)
		NSDestroyWindow(mNSWindow);
	#endif
	}

	void Window::CheckEvents() {
	#if defined(FastOSWindows)
		W32HandleEvents();
	#elif defined(FastOSLinux)
		X11HandleEvents(mXDisplay, mXWindow, this,
			mXIOpCode, GetDisplay()->GetXRREventBase());
	#elif defined(FastOSMacOSX)
		NSHandleEvents(mNSWindow);
	#endif
	}
	
	void Window::RefreshGeometry() {
		if (!mIsVisible)
			return;
	#if defined(FastOSWindows)
		W32GetFrameRect(mHwnd, &mFrameRectangle);
		mGlobalFrameRectangle = mFrameRectangle;
		mFrameRectangle.mX -= mParentMonitor->GetBounds().mX;
		mFrameRectangle.mY -= mParentMonitor->GetBounds().mY;
		W32GetContentRect(mHwnd, &mContentRectangle);
		mGlobalContentRectangle = mContentRectangle;
		mContentRectangle.mX -= mParentMonitor->GetBounds().mX;
		mContentRectangle.mY -= mParentMonitor->GetBounds().mY;
	#elif defined(FastOSLinux)
		Int x, y;
		X11GetClientGeometry(mXDisplay, mXWindow,
			&mGlobalContentRectangle.mX, &mGlobalContentRectangle.mY,
			&mGlobalContentRectangle.mWidth, &mGlobalContentRectangle.mHeight);
		mContentRectangle = mGlobalContentRectangle;
		mContentRectangle.mX -= mParentMonitor->GetBounds().mX;
		mContentRectangle.mY -= mParentMonitor->GetBounds().mY;
		X11GetFrameGeometry(mXDisplay, mXWindow,
			&mGlobalFrameRectangle.mX, &mGlobalFrameRectangle.mY,
			&mGlobalFrameRectangle.mWidth, &mGlobalFrameRectangle.mHeight);
		mFrameRectangle = mGlobalFrameRectangle;
		mFrameRectangle.mX -= mParentMonitor->GetBounds().mX;
		mFrameRectangle.mY -= mParentMonitor->GetBounds().mY;
	#elif defined(FastOSMacOSX)
		NSGetFrameRect(mNSWindow, &mGlobalFrameRectangle);
		mGlobalFrameRectangle.mY =
			mDisplay.GetMainMonitor().GetBounds().mHeight -
			mMonitor.GetBounds().mHeight - mGlobalFrameRectangle.mY;
		mFrameRectangle = mGlobalFrameRectangle;
		mFrameRectangle.mX -= mParentMonitor->GetBounds().mX;
		mFrameRectangle.mY -= mParentMonitor->GetBounds().mY;
		NSGetContentRect(mNSWindow, &mGlobalContentRectangle);
		mGlobalContentRectangle.mY =
			mDisplay.GetMainMonitor().GetBounds().mHeight -
			mMonitor.GetBounds().mHeight - mGlobalContentRectangle.mY;
		mContentRectangle = mGlobalContentRectangle;
		mContentRectangle.mX -= mParentMonitor->GetBounds().mX;
		mContentRectangle.mY -= mParentMonitor->GetBounds().mY;
	#endif
		if (mOldFrameRectangle.mWidth != mFrameRectangle.mWidth ||
			mOldFrameRectangle.mHeight != mFrameRectangle.mHeight ||
			mOldContentRectangle.mWidth != mContentRectangle.mWidth ||
			mOldContentRectangle.mHeight != mContentRectangle.mHeight)
		{
			OnExpose();
		}
		mOldFrameRectangle = mFrameRectangle;
		mOldContentRectangle = mContentRectangle;
	}
	
	void Window::RefreshAttachedGamepads() {
		ErrorType e;
		Array<GamepadDeviceInfo> deviceInfoArray;
		Array<Bool>	mGamepadsStillPhysicallyConnected;
	#if defined(FastOSWindows)
		Int numXboxGamepads = 4;
	#else
		Int numXboxGamepads = 0;
	#endif
		if (0 == mGamepads.GetElementCount())
			mGamepadsStillPhysicallyConnected.SetElementCount(numXboxGamepads, false);
		else
			mGamepadsStillPhysicallyConnected.SetElementCount(mGamepads.GetElementCount());
		for (Int i = 0; i < mGamepadsStillPhysicallyConnected.GetElementCount();
			i++)
		{
			mGamepadsStillPhysicallyConnected[i] = false;
		}
	#if defined(FastOSWindows)
		// Add XInput slots as the first 4 gamepads
		if (4 > mGamepads.GetElementCount()) {
			mGamepads.Clear();
			for (Int i = 0; i < 4; i++)
				mGamepads.Append(Gamepad(i, GamepadDeviceInfo(NULL,
					String("XInput Gamepad %d", i + 1), "Unknown", ""),
					GamepadCapabilities(10, 1, 2)));
		}
		// Acquire physically attached devices
		deviceInfoArray = W32DirectInputGetAttachedDevices(mDirectInput);
		// Check if there are any newly attached devices to append to mGamepads
		Bool matchFound;
		for (Int i = 0; i < 4; i++)
			mGamepadsStillPhysicallyConnected[i] = true;
		for (Int i = 0; i < deviceInfoArray.GetElementCount(); i++) {
			CLPDIRECTINPUTDEVICE8 did = deviceInfoArray[i].mDeviceHandle;
			matchFound = false;
			for (Int j = 4; j < mGamepads.GetElementCount(); j++) {
				if (mGamepads[j].GetDeviceInfo() == deviceInfoArray[i]) {
					matchFound = true;
					mGamepads[j].SetConnected(true);
					mGamepadsStillPhysicallyConnected[j] = true;
					break;
				}
			}
			if (!matchFound) {
				e = W32DirectInputDeviceSetUp(did, mHwnd);
				if (e)
					Error::Throw(e,
						String("[%s(): deviceInfo.mProductName=\"%s\"]",
						FastFunctionName, deviceInfoArray[i].mProductName));
				else
					mGamepads.Append(Gamepad(mGamepads.GetElementCount(),
						deviceInfoArray[i],
						W32DirectInputDeviceGetCapabilities(did)));
			} else W32DirectInputDeviceRelease(did);
		}
	#elif defined(FastOSLinux)
		// Acquire physically attached devices
		deviceInfoArray = LinuxGetAttachedJoysticks();
		// Check if there are any newly attached devices to append to mGamepads
		Int jfd = 0;
		for (Int i = 0; i < deviceInfoArray.GetSize(); i++) {
			Int jfd = deviceInfoArray[i].mLinuxFileDescriptor;
			matchFound = false;
			for (Int j = 0; j < mGamepads.GetSize(); j++) {
				if (mGamepads[j].GetDeviceInfo() == deviceInfoArray[i]) {
					matchFound = true;
					mGamepads[j].SetConnected(true);
					mGamepadsStillPhysicallyConnected[j] = true;
					break;
				}
			}
			if (!matchFound) {
				mGamepads.Append(Gamepad(mGamepads.GetSize(),
					deviceInfoArray[i], LinuxJoystickGetCapabilities(jfd)));
			} else LinuxJoystickClose(jfd);
		}
	#elif defined(FastOSMacOSX)
		// TODO
	#endif
		// If any Gamepads are unaccounted for in our attached devices
		//	enumeration earlier, we set their connected state to false
		for (Int i = numXboxGamepads; i < mGamepadsStillPhysicallyConnected.GetElementCount();
			i++)
		{
			if (!mGamepadsStillPhysicallyConnected[i])
				mGamepads[i].SetConnected(false);
		}
	}

	void Window::PollGamepads() {
		for (Int i = 0; i < mGamepads.GetElementCount(); i++) {
	#if defined(FastOSWindows)
			if (i < 4)
				W32XInputGetState(i, this); 
			else
				W32DirectInputDevicePoll(i, this);
	#elif defined(FastOSLinux)
			LinuxJoystickPoll(i, this);
	#elif defined(FastOSMacOSX)
		// TODO
	#endif
		}
	}

	void Window::Show() {
		if (mTargetStyle == kWindowStyleFullscreen)
			mTargetContentRectangle = mParentMonitor->GetBounds();
		else {
			mTargetContentRectangle.mX += mParentMonitor->GetBounds().mX;
			mTargetContentRectangle.mY += mParentMonitor->GetBounds().mY;
		}
	#if defined(FastOSWindows)
		Int dwStyle, dwExStyle;
		W32GetStyleMasks(mTargetStyle, &dwStyle, &dwExStyle);
		W32ContentToFrameRect(&mTargetContentRectangle, dwStyle, dwExStyle);
		W32SetStyle(mHwnd, dwStyle, dwExStyle);
		W32SetWindowFrame(mHwnd, mTargetContentRectangle);
		W32ShowWindow(mHwnd);
	#elif defined(FastOSLinux)
		// Must (re)map window before changing properties in X11
		X11ShowWindow(mXDisplay, mXWindow);
		X11SetWindowResizable(mXDisplay, mXWindow, true);
		X11SetWindowType(mXDisplay, mXWindow, 0);
		X11SetWindowState(mXDisplay, mXWindow,
			"_NET_WM_STATE_FULLSCREEN", False);
		X11SetWindowState(mXDisplay, mXWindow, "_NET_WM_STATE_ABOVE", False);
		X11Flush(mXDisplay);
		switch (mTargetStyle)
		{
		case kWindowStyleFullscreen:
			X11SetWindowType(mXDisplay, mXWindow, "_NET_WM_WINDOW_TYPE_NORMAL");
			X11SetWindowState(mXDisplay, mXWindow,
				"_NET_WM_STATE_FULLSCREEN", True);
			break;
		case kWindowStyleBorderless:
			X11SetWindowType(mXDisplay, mXWindow,
				"_NET_WM_WINDOW_TYPE_TOOLBAR");
			break;
		case kWindowStyleNormal:
		case kWindowStyleResizable:
			X11SetWindowType(mXDisplay, mXWindow, "_NET_WM_WINDOW_TYPE_NORMAL");
			break;
		};
		X11MoveResize(mXDisplay, mXWindow, mTargetContentRectangle.mX,
			mTargetContentRectangle.mY, mTargetContentRectangle.mWidth,
			mTargetContentRectangle.mHeight);
		if (mTargetStyle != kWindowStyleResizable)
			X11SetWindowResizable(mXDisplay, mXWindow, false);
		X11Flush(mXDisplay);
	#elif defined(FastOSMacOSX)
		mTargetContentRectangle.mY =
			mDisplay->GetMainMonitor()->GetBounds().mHeight -
			mTargetContentRectangle.mY - mTargetContentRectangle.mHeight;
		NSSetStyleMask(mNSWindow, NSGetStyleMask(mTargetStyle));
		NSSetContentRect(mNSWindow, mTargetContentRectangle);
		NSSetWindowAlwaysOnTop(mTargetStyle == kWindowStyleFullscreen);
		NSShowWindow(mNSWindow);
	#endif
		RefreshGeometry();
		TrapCursor(mIsCursorTrapped);
		ShowCursor(mIsCursorVisible);
		mStyle = mTargetStyle;
		mTargetContentRectangle = mContentRectangle;
		mIsVisible = true;
	}

	void Window::Hide() {
	#if defined(FastOSWindows)
		W32HideWindow(mHwnd);
	#elif defined(FastOSLinux)
		X11HideWindow(mXDisplay, mXWindow);
	#elif defined(FastOSMacOSX)
		NSHideWindow(mNSWindow);
	#endif
		mIsVisible = false;
	}

	void Window::Update() {
		CheckEvents();
		Bool isInFocus = IsInFocus();
		Point pos;
		RefreshGeometry();
	#if defined(FastOSWindows)
		W32GetCursorPosition(&pos.mX, &pos.mY);
		if (isInFocus) {
			W32TrapCursor(mHwnd, mIsCursorTrapped);
			W32ShowCursor(mIsCursorVisible);
		} else
			W32TrapCursor(mHwnd, false);
	#elif defined(FastOSLinux)
		X11GetCursorPosition(mXDisplay, mXWindow, &pos.mX, &pos.mY);
		if (isInFocus) {
			if (mIsCursorTrapped)
				X11TrapCursor(mXDisplay, mXWindow);
			else
				X11UntrapCursor(mXDisplay);
			X11ShowCursor(mXDisplay, mXWindow, mIsCursorVisible);
		} else
			X11UntrapCursor(mXDisplay);
	#elif defined(FastOSMacOSX)
		NSGetCursorPosition(&pos.mX, &pos.mY);
		pos.mY = mDisplay->GetMainMonitor()->GetBounds().mHeight - pos.mY;
		if (isInFocus) {
			NSTrapCursor(mNSWindow, mIsCursorTrapped);
			NSShowCursor(mIsCursorVisible);
		} else
			NSTrapCursor(mNSWindow, false);
	#endif
		pos.mX -= mGlobalContentRectangle.mX;
		pos.mY -= mGlobalContentRectangle.mY;
		if (!mContentRectangle.Encloses(pos) || !isInFocus)
			mCursorPosition = pos;
		PollGamepads();
	}

	void Window::Draw() {
		TriggerDrawEvent();
	}

	void Window::TrapCursor(Bool trapCursor) {
		mIsCursorTrapped = trapCursor;
		if (IsInFocus()) {
		#if defined(FastOSWindows)
			W32TrapCursor(mHwnd, trapCursor);
		#elif defined(FastOSLinux)
			trapCursor ?
				X11TrapCursor(mXDisplay, mXWindow) :
				X11UntrapCursor(mXDisplay);
		#elif defined(FastOSMacOSX)
			NSTrapCursor(mNSWindow, trapCursor);
		#endif
		}
	}

	void Window::MoveCursorTo(const Point &position) {
		if (IsInFocus()) {
			Point pos = position;
			pos.mX += mGlobalContentRectangle.mX;
			pos.mY += mGlobalContentRectangle.mY;
		#if defined(FastOSWindows)
			W32SetCursorPosition(pos.mX, pos.mY);
		#elif defined(FastOSLinux)
			X11SetCursorPosition(mXDisplay, pos.mX, pos.mY);
		#elif defined(FastOSMacOSX)
			NSSetCursorPosition(mNSWindow, pos.mX, pos.mY);
		#endif
		}
	}

	void Window::ShowCursor(Bool showCursor) {
		mIsCursorVisible = showCursor;
		if (IsInFocus() && IsCursorInsideWindow()) {
		#if defined(FastOSWindows)
			W32ShowCursor(mIsCursorVisible);
		#elif defined(FastOSLinux)
			X11ShowCursor(mXDisplay, mXWindow, showCursor);
		#elif defined(FastOSMacOSX)
			NSShowCursor(showCursor);
		#endif
		}
	}

	void Window::TriggerCharacterInputEvent(const CharacterInputEvent &event) {
		mTypedChars.Append(event.mString);
		OnCharacterInput(event);
		mGuiRootContainer.OnCharacterInput(event);
	}

	void Window::TriggerKeyEvent(const KeyEvent &event) {
		if (event.mAction == kKeyActionPressed) {
			if (mKeyboard.IsKeyUp(event.mKey)) {
				mKeyboard.PressKey(event.mKey);
				OnKeyPress(event);
				mGuiRootContainer.OnKeyPress(event);
			}
		} else if (event.mAction == kKeyActionReleased) {
			if (mKeyboard.IsKeyDown(event.mKey)) {
				mKeyboard.ReleaseKey(event.mKey);
				OnKeyRelease(event);
				mGuiRootContainer.OnKeyRelease(event);
			}
		}
	}

	void Window::TriggerMouseButtonEvent(const MouseButtonEvent &event) {
		if (event.mAction == kMouseButtonActionPressed) {
			if (mMouse.IsButtonUp(event.mButton)) {
				mMouse.PressButton(event.mButton);
				OnMouseButtonPress(event);
				mGuiRootContainer.OnMouseButtonPress(event);
			}
		} else if (event.mAction == kMouseButtonActionReleased) {
			if (mMouse.IsButtonDown(event.mButton)) {
				mMouse.ReleaseButton(event.mButton);
				OnMouseButtonRelease(event);
				mGuiRootContainer.OnMouseButtonRelease(event);
			}
		}
	}

	void Window::TriggerMouseMoveEvent(const MouseMoveEvent &event) {
		mCursorPosition = event.mPosition;
		OnMouseMove(event);
		mGuiRootContainer.OnMouseMove(event);
	}

	void Window::TriggerMouseWheelEvent(const MouseWheelEvent &event) {
		switch (event.mAction)
		{
		case kMouseWheelActionScrollUp:
			mMouse.ScrollVertically(1);
			OnMouseScrollUp(event);
			mGuiRootContainer.OnMouseScrollUp(event);
			break;
		case kMouseWheelActionScrollDown:
			mMouse.ScrollVertically(-1);
			OnMouseScrollDown(event);
			mGuiRootContainer.OnMouseScrollDown(event);
			break;
		case kMouseWheelActionScrollRight:
			mMouse.ScrollHorizontally(1);
			OnMouseScrollRight(event);
			mGuiRootContainer.OnMouseScrollRight(event);
			break;
		case kMouseWheelActionScrollLeft:
			mMouse.ScrollHorizontally(-1);
			OnMouseScrollLeft(event);
			mGuiRootContainer.OnMouseScrollLeft(event);
			break;
		default:
			return;
		};
	}

	void Window::TriggerMouseRawMoveEvent(const MouseRawMoveEvent &event) {
		mMouse.Move(event.mMovement);
		OnMouseRawMove(event);
		mGuiRootContainer.OnMouseRawMove(event);
	}

	void Window::TriggerGamepadConnectionEvent(
		const GamepadConnectionEvent &event)
	{
		mGamepads[event.mGamepadID].SetConnected(event.mIsConnected);
		event.mIsConnected ? OnGamepadConnected(event) :
			OnGamepadDisconnect(event);
	}

	void Window::TriggerGamepadButtonEvent(const GamepadButtonEvent &event) {
		if (event.mAction == kGamepadButtonActionPressed) {
			mGamepads[event.mGamepadID].PressButton(event.mButton);
			OnGamepadButtonPress(event);
			mGuiRootContainer.OnGamepadButtonPress(event);
		} else if (event.mAction == kGamepadButtonActionReleased) {
			mGamepads[event.mGamepadID].ReleaseButton(event.mButton);
			OnGamepadButtonRelease(event);
			mGuiRootContainer.OnGamepadButtonRelease(event);
		}
	}

	void Window::TriggerGamepadStickAxisEvent(
		const GamepadStickAxisEvent &event)
	{
		switch (event.mStickAxis)
		{
		case kGamepadStickAxisX:
			mGamepads[event.mGamepadID].SetStickXAxis(
				event.mStick, event.mStickAxisValue);
			break;
		case kGamepadStickAxisY:
			mGamepads[event.mGamepadID].SetStickYAxis(
				event.mStick, event.mStickAxisValue);
			break;
		case kGamepadStickAxisOther:
			mGamepads[event.mGamepadID].SetStickOtherAxis(
				event.mStick, event.mStickAxisValue);
			break;
		default:
			return;
		};
		OnGamepadStickAxisChange(event);
		mGuiRootContainer.OnGamepadStickAxisChange(event);
	}

	void Window::TriggerExposeEvent() {
		OnExpose();
		mGuiRootContainer.OnExpose();
	}

	void Window::TriggerDrawEvent() {
		OnDraw();
	}

	void Window::TriggerCloseEvent() {
		OnClose();
	}

	Display* Window::GetDisplay() {
		return &mDisplay;
	}

	const Display& Window::GetDisplay() const {
		return mDisplay;
	}

	Monitor* Window::GetParentMonitor() {
		return mParentMonitor;
	}

	const Monitor& Window::GetParentMonitor() const {
		return *mParentMonitor;
	}

	GraphicsContext* Window::GetGraphicsContext() {
		return &mGraphicsContext;
	}

	const GraphicsContext& Window::GetGraphicsContext() const {
		return mGraphicsContext;
	}

	const Rectangle& Window::GetContentRectangle() const {
		return mContentRectangle;
	}

	const Rectangle& Window::GetFrameRectangle() const {
		return mFrameRectangle;
	}

	Bool Window::IsVisible() const {
		return mIsVisible;
	}

	WindowStyle Window::GetStyle() const {
		return mStyle;
	}

	const String & Window::GetTitle() const {
		return mTitle;
	}

	Bool Window::IsInFocus() const {
	#if defined(FastOSWindows)
		return W32GetFocus() == mHwnd;
	#elif defined(FastOSLinux)
		return X11GetFocus(mXDisplay) == mXWindow;
	#elif defined(FastOSMacOSX)
		return NSIsKeyWindow(mNSWindow);
	#endif
	}

	Bool Window::IsCursorTrapped() const {
		return mIsCursorTrapped;
	}

	const Point& Window::GetCursorPosition() const {
		return mCursorPosition;
	}

	Bool Window::IsCursorInsideWindow() const {
		return mContentRectangle.Encloses(mCursorPosition);
	}

	Bool Window::IsInTypingMode() const {
		return mIsInTypingMode;
	}

	String Window::GetTypedChars() {
		if (!mIsInTypingMode)
			return String();
		String temp;
		temp = mTypedChars;
		mTypedChars.Clear();
		return temp;
	}

	const Keyboard& Window::GetKeyboard() const {
		return mKeyboard;
	}

	const Mouse& Window::GetMouse() {
		mOldMouse = mMouse;
		mMouse.ResetMoveDelta();
		mMouse.ResetVerticalScrollWheelDelta();
		mMouse.ResetHorizontalScrollWheelDelta();
		return mOldMouse;
	}

	Int Window::GetGamepadCount() const {
		return mGamepads.GetElementCount();
	}

	const Gamepad& Window::GetGamepad(Int id) const {
		return mGamepads[id];
	}

	Clipboard* Window::GetClipboard() {
		return &mClipboard;
	}

	const Clipboard& Window::GetClipboard() const {
		return mClipboard;
	}

	GuiRootContainer* Window::GetGuiRootContainer() {
		return &mGuiRootContainer;
	}

	const GuiRootContainer& Window::GetGuiRootContainer() const {
		return mGuiRootContainer;
	}

	GuiTheme* Window::GetGuiTheme() {
		return &mGuiTheme;
	}

	const GuiTheme& Window::GetGuiTheme() const {
		return mGuiTheme;
	}

	void Window::SetParentMonitor(Monitor *monitor) {
		mParentMonitor->RemoveWindow(this);
		mParentMonitor = monitor;
		mParentMonitor->AddWindow(this);
		RefreshGeometry();
	}

	void Window::SetContentRectangle(const Rectangle &rect) {
		mTargetContentRectangle = rect;
	}

	void Window::SetContentPosition(const Point &point) {
		mTargetContentRectangle.mX = point.mX;
		mTargetContentRectangle.mY = point.mY;
	}

	void Window::SetContentPosition(Int x, Int y) {
		mTargetContentRectangle.mX = x;
		mTargetContentRectangle.mY = y;
	}

	void Window::SetContentSize(Int w, Int h) {
		mTargetContentRectangle.mWidth = w;
		mTargetContentRectangle.mHeight = h;
	}

	void Window::SetStyle(WindowStyle style) {
		mTargetStyle = style;
	}

	void Window::SetTitle(const String &title) {
		mTitle = title;
	#if defined(FastOSWindows)
		W32SetWindowText(mHwnd, mTitle);
	#elif defined(FastOSLinux)
		X11StoreName(mXDisplay, mXWindow, mTitle);
	#elif defined(FastOSMacOSX)
		NSSetWindowText(mNSWindow, mTitle);
	#endif
	}

	void Window::SetTypingMode(Bool typingMode) {
		mIsInTypingMode = typingMode;
		if (mIsInTypingMode)
			mTypedChars.Clear();
	}

	CHWND Window::GetHWND() {
		return mHwnd;
	}

	CXWindow Window::GetXWindow() {
		return mXWindow;
	}

	CGLXFBConfig Window::GetGLXFBConfig() {
		return mGLXFBConfig;
	}

	CNSWindow* Window::GetNSWindow() {
		return mNSWindow;
	}
}