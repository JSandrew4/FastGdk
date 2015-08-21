/******************************************************************************/
/*                                                                            */
/*  Window.hpp                                                                */
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

#ifndef FastWindowHppIncluded
#define FastWindowHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/Point.hpp>
#include <Fast/WindowStyle.hpp>
#include <Fast/Mouse.hpp>
#include <Fast/Keyboard.hpp>
#include <Fast/Gamepad.hpp>
#include <Fast/String.hpp>
#include <Fast/Rectangle.hpp>
#include <Fast/Clipboard.hpp>
#include <Fast/GuiRootContainer.hpp>
#include <Fast/GuiTheme.hpp>

namespace Fast
{
	class Game;
	class Monitor;
	class Display;
	class Window;
	class CharacterInputEvent;
	class KeyEvent;
	class MouseButtonEvent;
	class MouseWheelEvent;
	class MouseMoveEvent;
	class MouseRawMoveEvent;
	class GamepadConnectionEvent;
	class GamepadButtonEvent;
	class GamepadStickAxisEvent;
	class Clipboard;

	class FastApi Window
	{
	private:
		Display				&mDisplay;
		Monitor				*mParentMonitor;
		Rectangle			mTargetContentRectangle;
		Rectangle			mContentRectangle;
		Rectangle			mGlobalContentRectangle;
		Rectangle			mOldContentRectangle;
		Rectangle			mFrameRectangle;
		Rectangle			mGlobalFrameRectangle;
		Rectangle			mOldFrameRectangle;
		Bool				mIsVisible;
		WindowStyle			mTargetStyle;
		WindowStyle			mStyle;
		String				mTitle;
		Bool				mIsCursorVisible;
		Bool				mIsCursorTrapped;
		Bool				mIsInTypingMode;
		Point				mCursorPosition;
		Keyboard			mKeyboard;
		Mouse				mMouse;
		Mouse				mOldMouse;
		Array<Gamepad>		mGamepads;
		String				mTypedChars;
		CHWND				mHwnd;
		CLPDIRECTINPUT8		mDirectInput;
		CXDisplay			*mXDisplay;
		Int					mGLXFBConfigCount;
		CGLXFBConfig		*mGLXFBConfigs;
		CGLXFBConfig		mGLXFBConfig;
		CXWindow			mXWindow;
		Int					mXIOpCode;
		CNSWindow			*mNSWindow;
		Clipboard			mClipboard;
		GuiRootContainer	mGuiRootContainer;
		GraphicsContext		mGraphicsContext;
		GuiTheme			mGuiTheme;
	public:
		// (Con/De)structors
		Window(Display *display, Int multisampleCount = 0);
		~Window();
		// Misc functions
		void	CheckEvents();
		void	RefreshGeometry();
		void	RefreshAttachedGamepads();
		void	PollGamepads();
		void	Show();
		void	Hide();
		void	Update();
		void	Draw();
		void	TrapCursor(Bool trapCursor);
		void	MoveCursorTo(const Point &position);
		void	ShowCursor(Bool showCursor);
		// Event trigger functions
		void	TriggerCharacterInputEvent(const CharacterInputEvent &event);
		void	TriggerKeyEvent(const KeyEvent &event);
		void	TriggerMouseButtonEvent(const MouseButtonEvent &event);
		void	TriggerMouseMoveEvent(const MouseMoveEvent &event);
		void	TriggerMouseWheelEvent(const MouseWheelEvent &event);
		void	TriggerMouseRawMoveEvent(const MouseRawMoveEvent &event);
		void	TriggerGamepadConnectionEvent(
					const GamepadConnectionEvent &event);
		void	TriggerGamepadButtonEvent(const GamepadButtonEvent &event);
		void	TriggerGamepadStickAxisEvent(
					const GamepadStickAxisEvent &event);
		void	TriggerExposeEvent();
		void	TriggerDrawEvent();
		void	TriggerCloseEvent();
		// Events
		virtual void	OnCharacterInput(const CharacterInputEvent &event)	{ }
		virtual void	OnKeyPress(const KeyEvent &event)					{ }
		virtual void	OnKeyRelease(const KeyEvent &event)				{ }
		virtual void	OnMouseButtonPress(const MouseButtonEvent &event)	{ }
		virtual void	OnMouseButtonRelease(const MouseButtonEvent &event){ }
		virtual void	OnMouseMove(const MouseMoveEvent &event)			{ }
		virtual void	OnMouseScrollUp(const MouseWheelEvent &event)		{ }
		virtual void	OnMouseScrollDown(const MouseWheelEvent &event)		{ }
		virtual void	OnMouseScrollRight(const MouseWheelEvent &event)	{ }
		virtual void	OnMouseScrollLeft(const MouseWheelEvent &event)		{ }
		virtual void	OnMouseRawMove(const MouseRawMoveEvent &event)		{ }
		virtual void	OnGamepadConnected(const GamepadConnectionEvent &event)
							{ }
		virtual void	OnGamepadDisconnect(const GamepadConnectionEvent &event)
							{ }
		virtual void	OnGamepadButtonPress(const GamepadButtonEvent &event)
							{ }
		virtual void	OnGamepadButtonRelease(const GamepadButtonEvent &event)
							{ }
		virtual void	OnGamepadStickAxisChange(
							const GamepadStickAxisEvent &event) { }
		virtual void	OnExpose()											= 0;
		virtual void	OnDraw()											= 0;
		virtual void	OnClose()											= 0;
		// Get functions
		Display*				GetDisplay();
		const Display&			GetDisplay() const;
		Monitor*				GetParentMonitor();
		const Monitor&			GetParentMonitor() const;
		GraphicsContext*		GetGraphicsContext();
		const GraphicsContext&	GetGraphicsContext() const;
		const Rectangle&		GetContentRectangle() const;
		const Rectangle&		GetFrameRectangle() const;
		Bool					IsVisible() const;
		WindowStyle				GetStyle() const;
		const String&			GetTitle() const;
		Bool					IsInFocus() const;
		Bool					IsCursorTrapped() const;
		const Point&			GetCursorPosition() const;
		Bool					IsCursorInsideWindow() const;
		Bool					IsInTypingMode() const;
		String					GetTypedChars();
		const Keyboard&			GetKeyboard() const;
		const Mouse&			GetMouse();
		Int						GetGamepadCount() const;
		const Gamepad&			GetGamepad(Int id) const;
		Clipboard*				GetClipboard();
		const Clipboard&		GetClipboard() const;
		GuiRootContainer*		GetGuiRootContainer();
		const GuiRootContainer&	GetGuiRootContainer() const;
		GuiTheme*				GetGuiTheme();
		const GuiTheme&			GetGuiTheme() const;
		// Set functions
		void	SetParentMonitor(Monitor *monitor);
		void	SetContentRectangle(const Rectangle &rect);
		void	SetContentPosition(const Point &point);
		void	SetContentPosition(Int x, Int y);
		void	SetContentSize(Int w, Int h);
		void	SetStyle(WindowStyle style);
		void	SetTitle(const String &title);
		void	SetTypingMode(Bool typingMode);
		// Get deeper property functions
		CHWND			GetHWND();
		CXWindow		GetXWindow();
		CGLXFBConfig	GetGLXFBConfig();
		CNSWindow*		GetNSWindow();
	};
}

#endif // FastWindowHppIncluded
