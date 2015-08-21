/******************************************************************************/
/*                                                                            */
/*  Keyboard.cpp                                                              */
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

#include <Fast/Keyboard.hpp>
#include <Fast/Window.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	Keyboard::Keyboard() { }

	Keyboard::Keyboard(const Keyboard &that) {
		*this = that;
	}
	
	Keyboard::~Keyboard() { }

	Bool Keyboard::IsKeyDown(const String &key) const {
		String k = key;
		k.MakeLowercase();
		for (Int i = 0; i < mKeysPressed.GetElementCount(); i++)
			if (k == mKeysPressed[i])
				return true;
		return false;
	}

	Bool Keyboard::IsKeyUp(const String &key) const {
		String k = key;
		k.MakeLowercase();
		for (Int i = 0; i < mKeysPressed.GetElementCount(); i++)
			if (k == mKeysPressed[i])
				return false;
		return true;
	}

	void Keyboard::PressKey(const String &key) {
		String k = key;
		k.MakeLowercase();
		if (IsKeyUp(k))
			mKeysPressed.Append(k);
	}

	void Keyboard::ReleaseKey(const String &key) {
		String k = key;
		k.MakeLowercase();
		for (Int i = 0; i < mKeysPressed.GetElementCount(); i++) {
			if (k == mKeysPressed[i]) {
				mKeysPressed.Erase(i);
				return;
			}
		}
	}

	Keyboard & Keyboard::operator=(const Keyboard &that) {
		this->mKeysPressed.Clear();
		this->mKeysPressed.SetElementCount(that.mKeysPressed.GetElementCount());
		for (Int i = 0; i < this->mKeysPressed.GetElementCount(); i++)
			this->mKeysPressed[i] = that.mKeysPressed[i];
		return *this;
	}

	Bool Keyboard::operator==(const Keyboard &that) {
		if (this->mKeysPressed.GetElementCount() !=
			that.mKeysPressed.GetElementCount())
		{
			return false;
		}
		for (Int i = 0; i < this->mKeysPressed.GetElementCount(); i++)
			if (this->mKeysPressed[i] != that.mKeysPressed[i])
				return false;
		return true;
	}

	Bool Keyboard::operator!=(const Keyboard &that) {
		if (this->mKeysPressed.GetElementCount() !=
			that.mKeysPressed.GetElementCount())
		{
			return true;
		}
		for (Int i = 0; i < this->mKeysPressed.GetElementCount(); i++)
			if (this->mKeysPressed[i] != that.mKeysPressed[i])
				return true;
		return false;
	}
}
