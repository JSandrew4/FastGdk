/******************************************************************************/
/*                                                                            */
/*  GuiSelectable.cpp                                                         */
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

#include <Fast/GuiSelectable.hpp>
#include <Fast/KeyEvent.hpp>
#include <Fast/KeyBoard.hpp>
#include <Fast/MouseButtonEvent.hpp>
#include <Fast/Window.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GuiSelectable::GuiSelectable() : GuiWidget() {
		mClass = "selectable";
		mIsSelected = false;
	}

	GuiSelectable::~GuiSelectable() {
		// TODO: properly remove mNext and mPrevious
		//	should we connect mNext and mPrevious together?
	}

	Bool GuiSelectable::IsSelected() const {
		return mIsSelected;
	}

	GuiSelectable* GuiSelectable::GetNextSelectable() {
		return mNext;
	}

	const GuiSelectable& GuiSelectable::GetNextSelectable() const {
		return *mNext;
	}

	GuiSelectable* GuiSelectable::GetPreviousSelectable() {
		return mPrevious;
	}

	const GuiSelectable& GuiSelectable::GetPreviousSelectable() const {
		return *mPrevious;
	}

	void GuiSelectable::SetNextSelectable(GuiSelectable *next) {
		if (mNext)
			mNext->mPrevious = NULL;
		mNext = next;
		if (mNext)
			mNext->mPrevious = this;
	}

	void GuiSelectable::SetPreviousSelectable(GuiSelectable *previous) {
		if (mPrevious)
			mPrevious->mNext = NULL;
		mPrevious = previous;
		if (mPrevious)
			mPrevious->mNext = this;
	}

	void GuiSelectable::OnKeyPress(const KeyEvent &event) {
		if ("tab" == event.mKey) {
			OnUnselect();
			if (mOSWindow->GetKeyboard().IsKeyDown("shift"))
				mPrevious->OnSelect();
			else
				mNext->OnSelect();
		}
	}

	void GuiSelectable::OnMouseButtonPress(const MouseButtonEvent &event) {
		if (!mIsSelected) {
			// TODO: unselect the currently selected widget
			//	should we store a selected widget in GuiRootContainer
			OnSelect();
		}
	}

	void GuiSelectable::OnSelect() {
		mIsSelected = true;
	}

	void GuiSelectable::OnUnselect() {
		mIsSelected = false;
	}
}
