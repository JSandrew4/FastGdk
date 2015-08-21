/******************************************************************************/
/*                                                                            */
/*  Mouse.cpp                                                                 */
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

#include <Fast/Mouse.hpp>
#include <Fast/Window.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	Mouse::Mouse() {
		memset(mButtons, 0, kFastNumMouseButtons);
		mVerticalScrollWheelDelta = 0;
		mHorizontalScrollWheelDelta = 0;
	}

	Mouse::Mouse(const Mouse &that) {
		*this = that;
	}

	Mouse::~Mouse() { }

	Bool Mouse::IsButtonDown(MouseButton mouseButton) const {
		return mButtons[mouseButton];
	}

	Bool Mouse::IsButtonUp(MouseButton mouseButton) const {
		return !(mButtons[mouseButton]);
	}

	const Point& Mouse::GetMoveDelta() const {
		return mMoveDelta;
	}

	Int Mouse::GetVerticalScrollWheelDelta() const {
		return mVerticalScrollWheelDelta;
	}

	Int Mouse::GetHorizontalScrollWheelDelta() const {
		return mHorizontalScrollWheelDelta;
	}

	void Mouse::PressButton(MouseButton mouseButton) {
		mButtons[mouseButton] = true;
	}

	void Mouse::ReleaseButton(MouseButton mouseButton) {
		mButtons[mouseButton] = false;
	}

	void Mouse::Move(const Point &point) {
		mMoveDelta = point;
	}

	void Mouse::Move(Int x, Int y) {
		mMoveDelta.mX = x;
		mMoveDelta.mY = y;
	}

	void Mouse::ResetMoveDelta() {
		mMoveDelta = kFastPointZero;
	}

	void Mouse::ScrollVertically(Int delta) {
		mVerticalScrollWheelDelta += delta;
	}

	void Mouse::ScrollHorizontally(Int delta) {
		mHorizontalScrollWheelDelta += delta;
	}

	void Mouse::ResetVerticalScrollWheelDelta() {
		mVerticalScrollWheelDelta = 0;
	}

	void Mouse::ResetHorizontalScrollWheelDelta() {
		mHorizontalScrollWheelDelta = 0;
	}

	Mouse& Mouse::operator=(const Mouse &that) {
		memcpy(this->mButtons, that.mButtons,
			kFastNumMouseButtons);
		this->mMoveDelta = that.mMoveDelta;
		this->mVerticalScrollWheelDelta = that.mVerticalScrollWheelDelta;
		this->mHorizontalScrollWheelDelta = that.mHorizontalScrollWheelDelta;
		return *this;
	}

	Bool Mouse::operator==(const Mouse &that) {
		if (this->mMoveDelta != that.mMoveDelta)
			return false;
		if (this->mVerticalScrollWheelDelta != that.mVerticalScrollWheelDelta)
			return false;
		if (this->mHorizontalScrollWheelDelta !=
			that.mHorizontalScrollWheelDelta)
		{
			return false;
		}
		if (memcmp(this->mButtons, that.mButtons, kFastNumMouseButtons))
			return false;
		return true;
	}

	Bool Mouse::operator!=(const Mouse &that) {
		if (this->mMoveDelta != that.mMoveDelta)
			return true;
		if (this->mVerticalScrollWheelDelta != that.mVerticalScrollWheelDelta)
			return true;
		if (this->mHorizontalScrollWheelDelta !=
			that.mHorizontalScrollWheelDelta)
		{
			return true;
		}
		if (memcmp(this->mButtons, that.mButtons, kFastNumMouseButtons))
			return true;
		return false;
	}
}