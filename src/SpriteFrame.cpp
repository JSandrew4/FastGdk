/******************************************************************************/
/*                                                                            */
/*  SpriteFrame.cpp                                                           */
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

#include <Fast/SpriteFrame.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteFrame::SpriteFrame() {
		mFrameConfigIndex = 0;
		mDelayMicroseconds = 0;
		mInterpType = 0;
	}

	SpriteFrame::SpriteFrame(const SpriteFrame &that) {
		*this = that;
	}

	SpriteFrame::SpriteFrame(const String &name,
		Int frameConfigIndex, Int delayMicroseconds, Int interpType)
	{
		mName = name;
		mFrameConfigIndex = frameConfigIndex;
		mDelayMicroseconds = delayMicroseconds;
		mInterpType = interpType;
	}

	const String& SpriteFrame::GetName() const {
		return mName;
	}

	Int SpriteFrame::GetFrameConfigIndex() const {
		return mFrameConfigIndex;
	}

	Long SpriteFrame::GetDelayMicroseconds() const {
		return mDelayMicroseconds;
	}

	Int SpriteFrame::GetInterpType() const {
		return mInterpType;
	}

	void SpriteFrame::SetName(const String &name) {
		mName = name;
	}

	void SpriteFrame::SetFrameConfigIndex(Int frameConfigIndex) {
		mFrameConfigIndex = frameConfigIndex;
	}

	void SpriteFrame::SetDelayMicroseconds(Long delayMicroseconds) {
		mDelayMicroseconds = delayMicroseconds;
	}

	void SpriteFrame::SetInterpType(Int interpType) {
		mInterpType = interpType;
	}

	SpriteFrame& SpriteFrame::operator= (const SpriteFrame &that) {
		this->mName = that.mName;
		this->mFrameConfigIndex = that.mFrameConfigIndex;
		this->mDelayMicroseconds = that.mDelayMicroseconds;
		this->mInterpType = that.mInterpType;
		return *this;
	}

	Bool SpriteFrame::operator==(const SpriteFrame &that) const {
		if (this->mName != that.mName)
			return false;
		if (this->mFrameConfigIndex != that.mFrameConfigIndex)
			return false;
		if (this->mDelayMicroseconds != that.mDelayMicroseconds)
			return false;
		if (this->mInterpType != that.mInterpType)
			return false;
		return true;
	}

	Bool SpriteFrame::operator!=(const SpriteFrame &that) const {
		if (this->mName != that.mName)
			return true;
		if (this->mFrameConfigIndex != that.mFrameConfigIndex)
			return true;
		if (this->mDelayMicroseconds != that.mDelayMicroseconds)
			return true;
		if (this->mInterpType != that.mInterpType)
			return true;
		return false;
	}
}