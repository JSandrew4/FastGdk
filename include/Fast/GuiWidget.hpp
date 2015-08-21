/******************************************************************************/
/*                                                                            */
/*  GuiWidget.hpp                                                             */
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

#ifndef FastGuiWidgetHppIncluded
#define FastGuiWidgetHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>

namespace Fast
{
	class Window;
	class CharacterInputEvent;
	class KeyEvent;
	class MouseButtonEvent;
	class MouseMoveEvent;
	class MouseWheelEvent;
	class MouseRawMoveEvent;
	class GamepadButtonEvent;
	class GamepadStickAxisEvent;

	class FastApi GuiWidget
	{
	protected:
		Window				*mOSWindow;
		GuiWidget			*mContainer;
		Int					mSubWidgetIndex;
		Array<GuiWidget*>	mSubWidgetArray;
		String				mClass;
		Bool				mIsVisible;
		Bool				mIsEnabled;
		Bool				mIsHovered;
		Bool				mIsFocused;
	public:
		// (Con/De)structors
		GuiWidget();
		~GuiWidget();
		// Getters
		Window*				GetOSWindow();
		const Window&		GetOSWindow() const;
		GuiWidget*			GetContainer();
		const GuiWidget&	GetContainer() const;
		Int					GetSubWidgetIndex() const;
		GuiWidget*			GetSubWidget(Int subWidgetIndex);
		const GuiWidget&	GetSubWidget(Int subWidgetIndex) const;
		const String&		GetClass() const;
		Bool				IsVisible() const;
		Bool				IsEnabled() const;
		Bool				IsHovered() const;
		Bool				IsFocused() const;
		// Setters
		void	SetContainer(GuiWidget *container);
		void	SetVisible(Bool isVisible);
		void	SetEnabled(Bool isEnabled);
		// Events
		virtual void	OnCharacterInput(const CharacterInputEvent &event);
		virtual void	OnKeyPress(const KeyEvent &event);
		virtual void	OnKeyRelease(const KeyEvent &event);
		virtual void	OnMouseButtonPress(const MouseButtonEvent &event);
		virtual void	OnMouseButtonRelease(const MouseButtonEvent &event);
		virtual void	OnMouseMove(const MouseMoveEvent &event);
		virtual void	OnMouseScrollUp(const MouseWheelEvent &event);
		virtual void	OnMouseScrollDown(const MouseWheelEvent &event);
		virtual void	OnMouseScrollRight(const MouseWheelEvent &event);
		virtual void	OnMouseScrollLeft(const MouseWheelEvent &event);
		virtual void	OnMouseRawMove(const MouseRawMoveEvent &event);
		virtual void	OnGamepadButtonPress(const GamepadButtonEvent &event);
		virtual void	OnGamepadButtonRelease(const GamepadButtonEvent &event);
		virtual void	OnGamepadStickAxisChange(
							const GamepadStickAxisEvent &event);
		virtual void	OnHover();
		virtual void	OnUnhover();
		virtual void	OnFocus();
		virtual void	OnUnfocus();
		virtual void	OnExpose();
		// Misc
		Int				AddSubWidget(GuiWidget *subWidget);
		void			RemoveSubWidget(Int subWidgetIndex);
		virtual void	Draw()		= 0;
	};
}

#endif // FastGuiWidgetHppIncluded
