/******************************************************************************/
/*                                                                            */
/*  GuiPressable.cpp                                                         */
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

#include <Fast/GuiPressable.hpp>
#include <Fast/KeyEvent.hpp>
#include <Fast/Window.hpp>
#include <Fast/Keyboard.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GuiPressable::GuiPressable() : GuiSelectable() {
		mClass = "pressable";
		mIsPressed = false;
	}

	Bool GuiPressable::IsPressed() const {
		return mIsPressed;
	}

	void GuiPressable::OnKeyPress(const KeyEvent &event) {
		GuiSelectable::OnKeyPress(event);
		if ("space" == event.mKey)
			if (!mIsPressed)
				OnPress();
	}

	void GuiPressable::OnKeyRelease(const KeyEvent &event) {
		GuiSelectable::OnKeyRelease(event);
		if ("space" == event.mKey)
			if (mIsPressed)
				OnUnpress();
	}

	void GuiPressable::OnMouseButtonPress(const MouseButtonEvent &event) {
		GuiSelectable::OnMouseButtonPress(event);
		if (!mIsPressed)
			OnPress();
	}

	void GuiPressable::OnMouseButtonRelease(const MouseButtonEvent &event) {
		GuiSelectable::OnMouseButtonRelease(event);
		if (mIsPressed)
			OnUnpress();
	}

	void GuiPressable::OnHover() {
		mIsHovered = true;
		if (mIsPressed)
			;// TODO: change theme state to pressed
		else if (mIsSelected)
			;// TODO: change theme state to selected-hovered
		else
			;// TODO: change theme state to hovered
	}

	void GuiPressable::OnUnhover() {
		mIsHovered = false;
		// TODO: change theme state to normal
	}

	void GuiPressable::OnPress() {
		mIsPressed = true;
		// TODO: if (mIsPressed) change theme state to pressed
	}

	void GuiPressable::OnUnpress() {
		mIsPressed = false;
		if (mIsSelected && mIsHovered)
			;// TODO: change theme state to selected-hovered
		else if (mIsSelected)
			;// TODO: change theme state to selected
		else if (mIsHovered)
			;// TODO: change theme state to hovered
		else
			;// TODO: change theme state to normal
	}
}
