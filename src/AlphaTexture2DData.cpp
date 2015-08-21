/******************************************************************************/
/*                                                                            */
/*  AlphaTexture2DData.cpp                                                    */
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

#include <Fast/AlphaTexture2DData.hpp>

namespace Fast
{
	AlphaTexture2DData::AlphaTexture2DData() {
		mWidth = mHeight = 0;
	}

	AlphaTexture2DData::AlphaTexture2DData(Int width, Int height) {
		mWidth = width;
		mHeight = height;
		mPixels.SetElementCount(width * height);
	}

	AlphaTexture2DData::AlphaTexture2DData(Int width, Int height,
		const Array<Byte> &pixels)
	{
		mWidth = width;
		mHeight = height;
		mPixels = pixels;
	}

	AlphaTexture2DData::AlphaTexture2DData(const AlphaTexture2DData &that) {
		*this = that;
	}

	AlphaTexture2DData::~AlphaTexture2DData() { }

	Int AlphaTexture2DData::GetWidth() const {
		return mWidth;
	}

	Int AlphaTexture2DData::GetHeight() const {
		return mHeight;
	}

	const Array<Byte>& AlphaTexture2DData::GetPixels() const {
		return mPixels;
	}

	AlphaTexture2DData& AlphaTexture2DData::operator=(
		const AlphaTexture2DData &that)
	{
		this->mWidth = that.mWidth;
		this->mHeight = that.mHeight;
		this->mPixels = that.mPixels;
		return *this;
	}

	Bool AlphaTexture2DData::operator==(const AlphaTexture2DData &that) const {
		if (this->mWidth != that.mWidth)
			return false;
		if (this->mHeight != that.mHeight)
			return false;
		if (memcmp(&this->mPixels[0], &that.mPixels[0],
			this->mWidth * this->mHeight))
		{
			return false;
		}
		return true;
	}

	Bool AlphaTexture2DData::operator!=(const AlphaTexture2DData &that) const {
		if (this->mWidth != that.mWidth)
			return true;
		if (this->mHeight != that.mHeight)
			return true;
		if (memcmp(&this->mPixels[0], &that.mPixels[0],
			this->mWidth * this->mHeight))
		{
			return true;
		}
		return false;
	}
}