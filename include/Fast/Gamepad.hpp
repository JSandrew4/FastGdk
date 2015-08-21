/******************************************************************************/
/*                                                                            */
/*  Gamepad.hpp                                                               */
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

#ifndef FastGamepadHppIncluded
#define FastGamepadHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>
#include <Fast/GamepadStick.hpp>
#include <Fast/GamepadCapabilities.hpp>
#include <Fast/GamepadDeviceInfo.hpp>

namespace Fast
{
	class FastApi Gamepad
	{
	private:
		GamepadDeviceInfo		mDeviceInfo;
		GamepadCapabilities		mCapabilities;
		Int						mID;
		Bool					mIsConnected;
		Array<Bool>				mButtonsPressed;
		Array<GamepadStick>		mSticks;
	public:
		// (Con/De)structors
		Gamepad();
		Gamepad(Int id, const GamepadDeviceInfo &deviceInfo,
			const GamepadCapabilities &capabilities);
		Gamepad(const Gamepad &that);
		~Gamepad();
		// Gets
		const GamepadDeviceInfo&	GetDeviceInfo() const;
		const GamepadCapabilities&	GetCapabilities() const;
		Int							GetID() const;
		Bool						IsConnected() const;
		Int							GetNumButtons() const;
		Bool						IsButtonDown(Int button) const;
		Bool						IsButtonUp(Int button) const;
		Int							GetNumSticks() const;
		Int							GetStickXAxis(Int stick) const;
		Int							GetStickYAxis(Int stick) const;
		Int							GetStickOtherAxis(Int stick) const;
		// Sets
		void	SetDeviceInfoAndCapabilities(
					const GamepadDeviceInfo &deviceInfo,
					const GamepadCapabilities &capabilities);
		void	SetID(Int id);
		void	SetConnected(Bool isConnected);
		void	PressButton(Int button);
		void	ReleaseButton(Int button);
		void	SetStickXAxis(Int stick, Int value);
		void	SetStickYAxis(Int stick, Int value);
		void	SetStickOtherAxis(Int stick, Int value);
		// Operators
		Gamepad&	operator= (const Gamepad &that);
		Bool		operator==(const Gamepad &that) const;
		Bool		operator!=(const Gamepad &that) const;
	};
}

#endif // FastGamepadHppIncluded
