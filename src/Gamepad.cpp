/******************************************************************************/
/*                                                                            */
/*  Gamepad.cpp                                                               */
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

#include <Fast/Gamepad.hpp>
#include <Fast/Math.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Gamepad::Gamepad() {
		mID = 0;
		mIsConnected = false;
	}

	Gamepad::Gamepad(const Gamepad &that) {
		*this = that;
	}

	Gamepad::Gamepad(Int id, const GamepadDeviceInfo &deviceInfo,
		const GamepadCapabilities &capabilities)
	{
		mIsConnected = true;
		mID = id;
		SetDeviceInfoAndCapabilities(deviceInfo, capabilities);
	}

	Gamepad::~Gamepad() { }

	const GamepadDeviceInfo& Gamepad::GetDeviceInfo() const {
		return mDeviceInfo;
	}

	const GamepadCapabilities& Gamepad::GetCapabilities() const {
		return mCapabilities;
	}

	Int Gamepad::GetID() const {
		return mID;
	}

	Bool Gamepad::IsConnected() const {
		return mIsConnected;
	}

	Int Gamepad::GetNumButtons() const {
		return mButtonsPressed.GetElementCount();
	}

	Bool Gamepad::IsButtonDown(Int button) const {
		return mButtonsPressed[button];
	}

	Bool Gamepad::IsButtonUp(Int button) const {
		return !mButtonsPressed[button];
	}

	Int Gamepad::GetNumSticks() const {
		return mSticks.GetElementCount();
	}

	Int Gamepad::GetStickXAxis(Int stick) const {
		return mSticks[stick].mXAxis;
	}

	Int Gamepad::GetStickYAxis(Int stick) const {
		return mSticks[stick].mYAxis;
	}

	Int Gamepad::GetStickOtherAxis(Int stick) const {
		return mSticks[stick].mOtherAxis;
	}

	void Gamepad::SetDeviceInfoAndCapabilities(
		const GamepadDeviceInfo &deviceInfo,
		const GamepadCapabilities &capabilities)
	{
		mDeviceInfo = deviceInfo;
		mCapabilities = capabilities;
		mSticks.Clear();
		mButtonsPressed.Clear();
		mSticks.SetElementCount((mCapabilities.mNumAxes / 3) +
			(mCapabilities.mNumAxes % 3 ? 1 : 0));
		mButtonsPressed.SetElementCount((mCapabilities.mNumDirectionalPads * 4) +
			mCapabilities.mNumRegularButtons);
	}

	void Gamepad::SetID(Int id) {
		mID = id;
	}

	void Gamepad::SetConnected(Bool isConnected) {
		mIsConnected = isConnected;
	}

	void Gamepad::PressButton(Int button) {
		mButtonsPressed[button] = true;
	}

	void Gamepad::ReleaseButton(Int button) {
		mButtonsPressed[button] = false;
	}

	void Gamepad::SetStickXAxis(Int stick, Int value) {
		if (value > 100)
			mSticks[stick].mXAxis = 100;
		else if (value < 0)
			mSticks[stick].mXAxis = 0;
		else mSticks[stick].mXAxis = value;
	}

	void Gamepad::SetStickYAxis(Int stick, Int value) {
		if (value > 100)
			mSticks[stick].mYAxis = 100;
		else if (value < 0)
			mSticks[stick].mYAxis = 0;
		else mSticks[stick].mYAxis = value;
	}

	void Gamepad::SetStickOtherAxis(Int stick, Int value) {
		if (value > 100)
			mSticks[stick].mOtherAxis = 100;
		else if (value < 0)
			mSticks[stick].mOtherAxis = 0;
		else mSticks[stick].mOtherAxis = value;
	}

	Gamepad& Gamepad::operator=(const Gamepad &that) {
		this->mDeviceInfo = that.mDeviceInfo;
		this->mCapabilities = that.mCapabilities;
		this->mID = that.mID;
		this->mIsConnected = that.mIsConnected;
		this->mButtonsPressed = that.mButtonsPressed;
		this->mSticks = that.mSticks;
		return *this;
	}

	Bool Gamepad::operator==(const Gamepad &that) const {
		if (this->mDeviceInfo != that.mDeviceInfo)
			return false;
		if (this->mCapabilities != that.mCapabilities)
			return false;
		if (this->mID != that.mID)
			return false;
		if (this->mIsConnected != that.mIsConnected)
			return false;
		if (this->mButtonsPressed.GetElementCount() !=
			that.mButtonsPressed.GetElementCount())
		{
			return false;
		}
		for (Int i = 0; i < mButtonsPressed.GetElementCount(); i++)
			if (this->mButtonsPressed[i] != that.mButtonsPressed[i])
				return false;
		if (this->mSticks.GetElementCount() != that.mSticks.GetElementCount())
			return false;
		for (Int i = 0; i < mSticks.GetElementCount(); i++)
			if (this->mSticks[i] != that.mSticks[i])
				return false;
		return true;
	}

	Bool Gamepad::operator!=(const Gamepad &that) const {
		if (this->mDeviceInfo != that.mDeviceInfo)
			return true;
		if (this->mCapabilities != that.mCapabilities)
			return true;
		if (this->mID != that.mID)
			return true;
		if (this->mIsConnected != that.mIsConnected)
			return true;
		if (this->mButtonsPressed.GetElementCount() !=
			that.mButtonsPressed.GetElementCount())
		{
			return true;
		}
		for (Int i = 0; i < mButtonsPressed.GetElementCount(); i++)
			if (this->mButtonsPressed[i] != that.mButtonsPressed[i])
				return true;
		if (this->mSticks.GetElementCount() != that.mSticks.GetElementCount())
			return true;
		for (Int i = 0; i < mSticks.GetElementCount(); i++)
			if (this->mSticks[i] != that.mSticks[i])
				return true;
		return false;
	}
}