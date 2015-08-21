/******************************************************************************/
/*                                                                            */
/*  SpriteAction.cpp                                                          */
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

#include <Fast/SpriteAction.hpp>
#include <Fast/Exception.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteAction::SpriteAction() { }

	SpriteAction::SpriteAction(const SpriteAction &that) {
		*this = that;
	}

	const String& SpriteAction::GetName() const {
		return mName;
	}

	Int SpriteAction::GetNumFrames() const {
		return mFrames.GetElementCount();		
	}

	SpriteFrame* SpriteAction::GetFrame(Int index) {
		if (0 > index || GetNumFrames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return &mFrames[index];
	}

	const SpriteFrame& SpriteAction::GetFrame(Int index) const {
		if (0 > index || GetNumFrames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return mFrames[index];
	}

	Int SpriteAction::GetFrameIndex(const String &name) const {
		for (Int i = 0; i < mFrames.GetElementCount(); i++)
			if (mFrames[i].GetName() == name)
				return i;
		return -1;
	}

	void SpriteAction::SetName(const String &name) {
		mName = name;
	}

	void SpriteAction::AddFrame(const SpriteFrame &frame) {
		mFrames.Append(frame);
	}

	void SpriteAction::InsertFrame(const SpriteFrame &frame, Int index) {
		if (0 > index || GetNumFrames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mFrames.Insert(frame, index);
	}

	void SpriteAction::ReplaceFrame(const SpriteFrame &frame, Int index) {
		if (0 > index || GetNumFrames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mFrames.Replace(frame, index);
	}

	void SpriteAction::EraseFrame(Int index) {
		if (0 > index || GetNumFrames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mFrames.Erase(index);
	}

	void SpriteAction::ClearFrames() {
		for (Int i = GetNumFrames() - 1; i >= 0; i--)
			EraseFrame(i);
	}

	SpriteAction& SpriteAction::operator=(const SpriteAction &that) {
		this->mName = that.mName;
		this->mFrames = that.mFrames;
		return *this;
	}

	Bool SpriteAction::operator==(const SpriteAction &that) const {
		if (this->mName != that.mName)
			return false;
		if (this->mFrames.GetElementCount() != that.mFrames.GetElementCount())
			return false;
		for (Int i = 0; i < this->mFrames.GetElementCount(); i++)
			if (this->mFrames[i] != that.mFrames[i])
				return false;
		return true;
	}

	Bool SpriteAction::operator!=(const SpriteAction &that) const {
		if (this->mName != that.mName)
			return true;
		if (this->mFrames.GetElementCount() != that.mFrames.GetElementCount())
			return true;
		for (Int i = 0; i < this->mFrames.GetElementCount(); i++)
			if (this->mFrames[i] != that.mFrames[i])
				return true;
		return false;
	}
}