/******************************************************************************/
/*                                                                            */
/*  SpriteMapCamera.hpp                                                       */
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

#include <Fast/SpriteMapCamera.hpp>
#include <Fast/SpriteMap.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteMapCamera::SpriteMapCamera() {
		mSpriteMap = 0;
		mRotationDegrees = 0.0f;
		mZoom = -10.0f;
	}

	SpriteMapCamera::SpriteMapCamera(const SpriteMapCamera &that) {
		*this = that;
	}

	SpriteMapCamera::SpriteMapCamera(SpriteMap *spriteMap,
		const Vector2D &startingOrigin, Float startingRotationDegrees,
		Float startingZoom, const Vector2D &origin, Float rotationDegrees,
		Float zoom)
	{
		mSpriteMap = spriteMap;
		mStartingOrigin = startingOrigin;
		mOrigin = origin;
		mStartingRotationDegrees = startingRotationDegrees;
		mRotationDegrees = rotationDegrees;
		mStartingZoom = startingZoom;
		mZoom = zoom;
	}

	SpriteMapCamera::~SpriteMapCamera() { }

	SpriteMap* SpriteMapCamera::GetSpriteMap() {
		return mSpriteMap;
	}

	const SpriteMap& SpriteMapCamera::GetSpriteMap() const {
		return *mSpriteMap;
	}

	const Vector2D& SpriteMapCamera::GetStartingOrigin() const {
		return mStartingOrigin;
	}

	const Vector2D& SpriteMapCamera::GetOrigin() const {
		return mOrigin;
	}

	Float SpriteMapCamera::GetStartingRotationDegrees() const {
		return mStartingRotationDegrees;
	}

	Float SpriteMapCamera::GetRotationDegrees() const {
		return mRotationDegrees;
	}

	Float SpriteMapCamera::GetStartingZoom() const {
		return mStartingZoom;
	}

	Float SpriteMapCamera::GetZoom() const {
		return mZoom;
	}

	void SpriteMapCamera::SetStartingOrigin(const Vector2D &startingOrigin) {
		mStartingOrigin = startingOrigin;
	}

	void SpriteMapCamera::SetOrigin(const Vector2D &origin) {
		mOrigin = origin;
	}

	void SpriteMapCamera::SetStartingRotationDegrees(
		Float startingRotationDegrees)
	{
		mStartingRotationDegrees = startingRotationDegrees;
	}

	void SpriteMapCamera::SetRotationDegrees(Float degrees) {
		mRotationDegrees = degrees;
	}

	void SpriteMapCamera::SetStartingZoom(Float startingZoom) {
		mStartingZoom = startingZoom;
	}

	void SpriteMapCamera::SetZoom(Float zoom) {
		mZoom = zoom;
	}

	void SpriteMapCamera::Reset() {
		mOrigin = mStartingOrigin;
		mRotationDegrees = mStartingRotationDegrees;
		mZoom = mStartingZoom;
	}

	SpriteMapCamera& SpriteMapCamera::operator=(const SpriteMapCamera &that) {
		this->mSpriteMap = that.mSpriteMap;
		this->mStartingOrigin = that.mStartingOrigin;
		this->mOrigin = that.mOrigin;
		this->mStartingRotationDegrees = that.mStartingRotationDegrees;
		this->mRotationDegrees = that.mRotationDegrees;
		this->mStartingZoom = that.mStartingZoom;
		this->mZoom = that.mZoom;
		return *this;
	}

	Bool SpriteMapCamera::operator==(const SpriteMapCamera &that) const {
		if (this->mSpriteMap != that.mSpriteMap)
			return false;
		if (this->mStartingOrigin != that.mStartingOrigin)
			return false;
		if (this->mOrigin != that.mOrigin)
			return false;
		if (this->mStartingRotationDegrees != that.mStartingRotationDegrees)
			return false;
		if (this->mRotationDegrees != that.mRotationDegrees)
			return false;
		if (this->mStartingZoom != that.mStartingZoom)
			return false;
		if (this->mZoom != that.mZoom)
			return false;
		return true;
	}

	Bool SpriteMapCamera::operator!=(const SpriteMapCamera &that) const {
		if (this->mSpriteMap != that.mSpriteMap)
			return true;
		if (this->mStartingOrigin != that.mStartingOrigin)
			return true;
		if (this->mOrigin != that.mOrigin)
			return true;
		if (this->mStartingRotationDegrees != that.mStartingRotationDegrees)
			return true;
		if (this->mRotationDegrees != that.mRotationDegrees)
			return true;
		if (this->mStartingZoom != that.mStartingZoom)
			return true;
		if (this->mZoom != that.mZoom)
			return true;
		return false;
	}
}