/******************************************************************************/
/*                                                                            */
/*  GuiWidget.cpp                                                             */
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

#include <Fast/GuiWidget.hpp>
#include <Fast/CharacterInputEvent.hpp>
#include <Fast/KeyEvent.hpp>
#include <Fast/MouseButtonEvent.hpp>
#include <Fast/MouseMoveEvent.hpp>
#include <Fast/MouseRawMoveEvent.hpp>
#include <Fast/MouseWheelEvent.hpp>
#include <Fast/GamepadButtonEvent.hpp>
#include <Fast/GamepadConnectionEvent.hpp>
#include <Fast/GamepadStickAxisEvent.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GuiWidget::GuiWidget() {
		mOSWindow = NULL;
		mContainer = NULL;
		mSubWidgetIndex = -1;
		mClass = "widget";
		mIsVisible = true;
		mIsEnabled = true;
		mIsHovered = false;
		mIsFocused = false;
	}

	GuiWidget::~GuiWidget() {
		for (Int i = 0; i < mSubWidgetArray.GetElementCount(); i++)
			if (mSubWidgetArray[i])
				RemoveSubWidget(i);
	}

	Window* GuiWidget::GetOSWindow() {
		return mOSWindow;
	}

	const Window& GuiWidget::GetOSWindow() const {
		return *mOSWindow;
	}

	GuiWidget* GuiWidget::GetContainer() {
		return mContainer;
	}

	const GuiWidget& GuiWidget::GetContainer() const {
		return *mContainer;
	}

	Int GuiWidget::GetSubWidgetIndex() const {
		return mSubWidgetIndex;
	}

	GuiWidget* GuiWidget::GetSubWidget(Int subWidgetIndex) {
		return mSubWidgetArray[subWidgetIndex];
	}

	const GuiWidget& GuiWidget::GetSubWidget(Int subWidgetIndex) const {
		return *mSubWidgetArray[subWidgetIndex];
	}

	const String& GuiWidget::GetClass() const {
		return mClass;
	}

	Bool GuiWidget::IsVisible() const {
		return mIsVisible;
	}

	Bool GuiWidget::IsEnabled() const {
		return mIsEnabled;
	}

	Bool GuiWidget::IsHovered() const {
		return mIsHovered;
	}

	Bool GuiWidget::IsFocused() const {
		return mIsFocused;
	}

	void GuiWidget::SetContainer(GuiWidget *container) {
		if (container)
			container->AddSubWidget(this);
		else if (mContainer) {
			mOSWindow = NULL;
			mContainer = NULL;
			mSubWidgetIndex = -1;
		}
	}

	void GuiWidget::SetVisible(Bool isVisible) {
		mIsVisible = isVisible;
	}

	void GuiWidget::SetEnabled(Bool isEnabled) {
		mIsEnabled = isEnabled;
	}

	void GuiWidget::OnCharacterInput(const CharacterInputEvent &event) {
		// TODO
	}

	void GuiWidget::OnKeyPress(const KeyEvent &event) {
		// TODO
	}

	void GuiWidget::OnKeyRelease(const KeyEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseButtonPress(const MouseButtonEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseButtonRelease(const MouseButtonEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseMove(const MouseMoveEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseScrollUp(const MouseWheelEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseScrollDown(const MouseWheelEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseScrollRight(const MouseWheelEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseScrollLeft(const MouseWheelEvent &event) {
		// TODO
	}

	void GuiWidget::OnMouseRawMove(const MouseRawMoveEvent &event) {
		// TODO
	}

	void GuiWidget::OnGamepadButtonPress(const GamepadButtonEvent &event) {
		// TODO
	}

	void GuiWidget::OnGamepadButtonRelease(const GamepadButtonEvent &event) {
		// TODO
	}

	void GuiWidget::OnGamepadStickAxisChange(const GamepadStickAxisEvent &event)
	{
		// TODO
	}

	void GuiWidget::OnHover() {
		mIsHovered = true;
		// TODO: change widget theme to *-hover
	}

	void GuiWidget::OnUnhover() {
		mIsHovered = false;
		// TODO: change widget theme to *-normal
	}

	void GuiWidget::OnFocus() {
		mIsFocused = true;
	}

	void GuiWidget::OnUnfocus() {
		mIsFocused = false;
	}

	void GuiWidget::OnExpose() {
		// TODO
	}

	Int GuiWidget::AddSubWidget(GuiWidget *subWidget) {
		if (this == subWidget->mContainer)
			return subWidget->mSubWidgetIndex;
		subWidget->mOSWindow = NULL;
		subWidget->mContainer = NULL;
		subWidget->mSubWidgetIndex = -1;
		for (Int i = 0; i < mSubWidgetArray.GetElementCount(); i++) {
			if (NULL == mSubWidgetArray[i]) {
				mSubWidgetArray[i] = subWidget;
				return i;
			}
		}
		mSubWidgetArray.Append(subWidget);
		return mSubWidgetArray.GetElementCount() - 1;
	}

	void GuiWidget::RemoveSubWidget(Int subWidgetIndex) {
		mSubWidgetArray[subWidgetIndex]->mOSWindow = NULL;
		mSubWidgetArray[subWidgetIndex]->mContainer = NULL;
		mSubWidgetArray[subWidgetIndex]->mSubWidgetIndex = -1;
		mSubWidgetArray[subWidgetIndex] = NULL;
	}
}
