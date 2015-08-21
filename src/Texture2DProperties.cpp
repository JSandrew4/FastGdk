/******************************************************************************/
/*                                                                            */
/*  Texture2DProperties.cpp                                                   */
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

#include <Fast/Texture2DProperties.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Texture2DProperties::Texture2DProperties() {
		mWidth = 0;
		mHeight = 0;
		mBitsPerPixel = 0;
		mWrapTypeS = kTexture2DWrapRepeat;
		mWrapTypeT = kTexture2DWrapRepeat;
		mMinifyFilterType = kTexture2DFilterLinear;
		mMagnifyFilterType = kTexture2DFilterLinear;
		mBorderColor = Color(0, 0, 0, 255);
	}

	Texture2DProperties::Texture2DProperties(Int width, Int height, Int bitsPerPixel)
	{
		mWidth = width;
		mHeight = height;
		mBitsPerPixel = bitsPerPixel;
		mWrapTypeS = kTexture2DWrapRepeat;
		mWrapTypeT = kTexture2DWrapRepeat;
		mMinifyFilterType = kTexture2DFilterLinear;
		mMagnifyFilterType = kTexture2DFilterLinear;
		mBorderColor = Color(0, 0, 0, 255);
	}

	Int Texture2DProperties::GetWidth() const {
		return mWidth;
	}

	Int Texture2DProperties::GetHeight() const {
		return mHeight;
	}

	Int Texture2DProperties::GetBitsPerPixel() const {
		return mBitsPerPixel;
	}

	const SpriteSheet& Texture2DProperties::GetSpriteSheet() const {
		return mSpriteSheet;
	}

	SpriteSheet* Texture2DProperties::GetSpriteSheet() {
		return &mSpriteSheet;
	}

	Texture2DWrapType Texture2DProperties::GetWrapTypeS() const {
		return mWrapTypeS;
	}

	Texture2DWrapType Texture2DProperties::GetWrapTypeT() const {
		return mWrapTypeT;
	}

	Texture2DFilterType Texture2DProperties::GetMinifyFilterType() const {
		return mMinifyFilterType;
	}

	Texture2DFilterType Texture2DProperties::GetMagnifyFilterType() const {
		return mMagnifyFilterType;
	}

	const Color& Texture2DProperties::GetBorderColor() const {
		return mBorderColor;
	}

	void Texture2DProperties::SetSize(Int width, Int height) {
		mWidth = width;
		mHeight = height;
	}

	void Texture2DProperties::SetWidth(Int width) {
		mWidth = width;
	}

	void Texture2DProperties::SetHeight(Int height) {
		mHeight = height;
	}

	void Texture2DProperties::SetBitsPerPixel(Int bitsPerPixel) {
		mBitsPerPixel = bitsPerPixel;
	}

	void Texture2DProperties::SetSpriteSheet(const SpriteSheet &spriteSheet) {
		mSpriteSheet = spriteSheet;
	}

	void Texture2DProperties::SetWrapTypeS(Texture2DWrapType type) {
		mWrapTypeS = type;
	}

	void Texture2DProperties::SetWrapTypeT(Texture2DWrapType type) {
		mWrapTypeT = type;
	}

	void Texture2DProperties::SetMinifyFilterType(Texture2DFilterType type) {
		mMinifyFilterType = type;
	}

	void Texture2DProperties::SetMagnifyFilterType(Texture2DFilterType type) {
		mMagnifyFilterType = type;
	}

	void Texture2DProperties::SetBorderColor(const Color &borderColor) {
		mBorderColor = borderColor;
	}


	Bool Texture2DProperties::operator==(const Texture2DProperties &that) const {
		if (this->mWidth != that.mWidth)
			return false;
		if (this->mHeight != that.mHeight)
			return false;
		if (this->mBitsPerPixel != that.mBitsPerPixel)
			return false;
		if (this->mSpriteSheet != that.mSpriteSheet)
			return false;
		if (this->mWrapTypeS != that.mWrapTypeS)
			return false;
		if (this->mWrapTypeT != that.mWrapTypeT)
			return false;
		if (this->mMinifyFilterType != that.mMinifyFilterType)
			return false;
		if (this->mMagnifyFilterType != that.mMagnifyFilterType)
			return false;
		if (this->mBorderColor != that.mBorderColor)
			return false;
		return true;
	}

	Bool Texture2DProperties::operator!=(const Texture2DProperties &that) const {
		if (this->mWidth != that.mWidth)
			return true;
		if (this->mHeight != that.mHeight)
			return true;
		if (this->mBitsPerPixel != that.mBitsPerPixel)
			return true;
		if (this->mSpriteSheet != that.mSpriteSheet)
			return true;
		if (this->mWrapTypeS != that.mWrapTypeS)
			return true;
		if (this->mWrapTypeT != that.mWrapTypeT)
			return true;
		if (this->mMinifyFilterType != that.mMinifyFilterType)
			return true;
		if (this->mMagnifyFilterType != that.mMagnifyFilterType)
			return true;
		if (this->mBorderColor != that.mBorderColor)
			return true;
		return false;
	}
}