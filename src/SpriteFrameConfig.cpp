/******************************************************************************/
/*                                                                            */
/*  SpriteFrameConfig.cpp                                                     */
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

#include <Fast/SpriteFrameConfig.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteFrameConfig::SpriteFrameConfig() {
		mTexture2DIndex = 0;
		mCollisionModelIndex = 0;
		mRotationDegrees = 0;
		mFlipX = false;
		mFlipY = false;
	}

	SpriteFrameConfig::SpriteFrameConfig(const SpriteFrameConfig &that) {
		*this = that;
	}

	const String& SpriteFrameConfig::GetName() const {
		return mName;
	}

	Int SpriteFrameConfig::GetTexture2DIndex() const {
		return mTexture2DIndex;
	}

	Int SpriteFrameConfig::GetCollisionModelIndex() const {
		return mCollisionModelIndex;
	}

	const Vector2D& SpriteFrameConfig::GetOffset() const {
		return mOffset;
	}

	const Vector2D& SpriteFrameConfig::GetScale() const {
		return mScale;
	}

	Float SpriteFrameConfig::GetRotationDegrees() const {
		return mRotationDegrees;
	}

	Bool SpriteFrameConfig::IsXFlipped() const {
		return mFlipX;
	}

	Bool SpriteFrameConfig::IsYFlipped() const {
		return mFlipY;
	}

	void SpriteFrameConfig::SetName(const String &name) {
		mName = name;
	}

	void SpriteFrameConfig::SetTexture2DIndex(Int texture2DIndex) {
		mTexture2DIndex = texture2DIndex;
	}

	void SpriteFrameConfig::SetCollisionModelIndex(Int collisionModelIndex) {
		mCollisionModelIndex = collisionModelIndex;
	}

	void SpriteFrameConfig::SetOffset(const Vector2D &offset) {
		mOffset = offset;
	}

	void SpriteFrameConfig::SetScale(const Vector2D &scale) {
		mScale = scale;
	}

	void SpriteFrameConfig::SetRotationDegrees(Float rotationDegrees) {
		mRotationDegrees = rotationDegrees;
	}

	void SpriteFrameConfig::SetFlipX(Bool flipX) {
		mFlipX = flipX;
	}

	void SpriteFrameConfig::SetFlipY(Bool flipY) {
		mFlipY = flipY;
	}

	SpriteFrameConfig& SpriteFrameConfig::operator=(
		const SpriteFrameConfig &that)
	{
		this->mName = that.mName;
		this->mTexture2DIndex = that.mTexture2DIndex;
		this->mCollisionModelIndex = that.mCollisionModelIndex;
		this->mOffset = that.mOffset;
		this->mScale = that.mScale;
		this->mRotationDegrees = that.mRotationDegrees;
		this->mFlipX = that.mFlipX;
		this->mFlipY = that.mFlipY;
		return *this;
	}

	Bool SpriteFrameConfig::operator==(const SpriteFrameConfig &that) const {
		if (this->mName != that.mName)
			return false;
		if (this->mTexture2DIndex != that.mTexture2DIndex)
			return false;
		if (this->mCollisionModelIndex != that.mCollisionModelIndex)
			return false;
		if (this->mOffset != that.mOffset)
			return false;
		if (this->mScale != that.mScale)
			return false;
		if (this->mRotationDegrees != that.mRotationDegrees)
			return false;
		if (this->mFlipX != that.mFlipX)
			return false;
		if (this->mFlipY != that.mFlipY)
			return false;
		return true;
	}

	Bool SpriteFrameConfig::operator!=(const SpriteFrameConfig &that) const {
		if (this->mName != that.mName)
			return true;
		if (this->mTexture2DIndex != that.mTexture2DIndex)
			return true;
		if (this->mCollisionModelIndex != that.mCollisionModelIndex)
			return true;
		if (this->mOffset != that.mOffset)
			return true;
		if (this->mScale != that.mScale)
			return true;
		if (this->mRotationDegrees != that.mRotationDegrees)
			return true;
		if (this->mFlipX != that.mFlipX)
			return true;
		if (this->mFlipY != that.mFlipY)
			return true;
		return false;
	}
}