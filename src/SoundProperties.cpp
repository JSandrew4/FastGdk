/******************************************************************************/
/*                                                                            */
/*  SoundProperties.cpp                                                       */
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

#include <Fast/SoundProperties.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SoundProperties::SoundProperties() {
		mFormat = kSoundFormatNone;
		mFrequency = 0;
		mChannelCount = 0;
		mSamplesByteCount = 0;
		mSampleCount = 0;
	}

	SoundProperties::SoundProperties(SoundFormat format,
		Int frequency, Int sampleCount)
	{
		mSampleCount = sampleCount;
		mFrequency = frequency;
		SetFormat(format);
	}

	SoundFormat SoundProperties::GetFormat() const {
		return mFormat;
	}

	Int SoundProperties::GetFrequency() const {
		return mFrequency;
	}

	Int SoundProperties::GetChannelCount() const {
		return mChannelCount;
	}

	Int SoundProperties::GetSamplesByteCount() const {
		return mSamplesByteCount;
	}

	Int SoundProperties::GetSampleCount() const {
		return mSampleCount;
	}

	void SoundProperties::SetFormat(SoundFormat format) {
		mFormat = format;
		switch (mFormat)
		{
		case kSoundFormatMono8:
			mSamplesByteCount = 1;
			mChannelCount = 1;
			break;
		case kSoundFormatMono16:
			mSamplesByteCount = 2;
			mChannelCount = 1;
		case kSoundFormatStereo8:
			mSamplesByteCount = 1;
			mChannelCount = 2;
			break;
		case kSoundFormatStereo16:
			mSamplesByteCount = 2;
			mChannelCount = 2;
			break;
		case kSoundFormatNone:
		default:
			mSamplesByteCount = 0;
			mChannelCount = 0;
		};
	}

	void SoundProperties::SetFrequency(Int frequency) {
		mFrequency = frequency;
	}

	void SoundProperties::SetSampleCount(Int sampleCount) {
		mSampleCount = sampleCount;
	}

	Bool SoundProperties::operator==(const SoundProperties &that) const {
		if (this->mSamplesByteCount != that.mSamplesByteCount)
			return false;
		if (this->mChannelCount != that.mChannelCount)
			return false;
		if (this->mFormat != that.mFormat)
			return false;
		if (this->mFrequency != that.mFrequency)
			return false;
		if (this->mSampleCount != that.mSampleCount)
			return false;
		return true;
	}

	Bool SoundProperties::operator!=(const SoundProperties &that) const {
		if (this->mSamplesByteCount != that.mSamplesByteCount)
			return true;
		if (this->mChannelCount != that.mChannelCount)
			return true;
		if (this->mFormat != that.mFormat)
			return true;
		if (this->mFrequency != that.mFrequency)
			return true;
		if (this->mSampleCount != that.mSampleCount)
			return true;
		return false;
	}
}