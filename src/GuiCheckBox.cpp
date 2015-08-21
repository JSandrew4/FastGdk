/******************************************************************************/
/*                                                                            */
/*  GuiCheckBox.cpp                                                           */
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

#include <Fast/GuiCheckBox.hpp>
#include <Fast/KeyEvent.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GuiCheckBox::GuiCheckBox() : GuiPressable() {
		mClass = "check-box";
		mState = kGuiCheckBoxUnchecked;
	}

	GuiCheckBox::~GuiCheckBox() { }

	GuiCheckBoxState GuiCheckBox::GetState() const {
		return mState;
	}

	void GuiCheckBox::SetState(GuiCheckBoxState state) {
		if (state != mState) {
			mState = state;
			// TODO: Change theme state to the check box type
			OnStateChange();
		}
	}

	void GuiCheckBox::OnUnpress() {
		GuiPressable::OnUnpress();
		switch (mState)
		{
		case kGuiCheckBoxUnchecked:
			SetState(kGuiCheckBoxChecked);
			break;
		case kGuiCheckBoxChecked:
			SetState(kGuiCheckBoxUnchecked);
			break;
		case kGuiCheckBoxUndetermined:
			SetState(kGuiCheckBoxChecked);
			break;
		}
	}

	void GuiCheckBox::OnMouseButtonPress(const MouseButtonEvent &event) {
		GuiWidget::OnMouseButtonPress(event);
		OnPress();
	}

	void GuiCheckBox::OnMouseButtonRelease(const MouseButtonEvent &event) {
		if (mIsPressed && mIsHovered)
			OnUnpress();
		else if (mIsPressed)
			GuiPressable::OnUnpress();
	}

	void GuiCheckBox::Draw() {
		// TODO
	}
}
