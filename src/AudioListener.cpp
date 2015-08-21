/******************************************************************************/
/*                                                                            */
/*  AudioListener.cpp                                                         */
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

#include <Fast/AudioListener.hpp>

#include "Undefs.hpp"

namespace Fast
{
	AudioListener::AudioListener() {
		mLookAt = kFastVector3DUnitX;
		mUp = kFastVector3DUnitZ;
	}

	AudioListener::AudioListener(const AudioListener &that) {
		*this = that;
	}

	AudioListener::~AudioListener() { }

	const Vector3D& AudioListener::GetPosition() const {
		return mPosition;
	}

	const Vector3D& AudioListener::GetLookAt() const {
		return mLookAt;
	}

	const Vector3D& AudioListener::GetUpVector() const {
		return mUp;
	}

	void AudioListener::SetPosition(const Vector3D &position) {
		mPosition = position;
	}

	void AudioListener::SetLookAt(const Vector3D &lookAt) {
		mLookAt = lookAt;
	}

	void AudioListener::SetUpVector(const Vector3D &up) {
		mUp = up;
	}

	void AudioListener::SetOrientation(const Vector3D &lookAt, const Vector3D &up) {
		mLookAt = lookAt;
		mUp = up;
	}

	AudioListener& AudioListener::operator=(const AudioListener &that) {
		this->mPosition = that.mPosition;
		this->mLookAt = that.mLookAt;
		this->mUp = that.mUp;
		return *this;
	}

	Bool AudioListener::operator==(const AudioListener &that) const {
		if (this->mPosition != that.mPosition)
			return false;
		if (this->mLookAt!= that.mLookAt)
			return false;
		if (this->mUp != that.mUp)
			return false;
		return true;
	}

	Bool AudioListener::operator!=(const AudioListener &that) const {
		if (this->mPosition != that.mPosition)
			return true;
		if (this->mLookAt!= that.mLookAt)
			return true;
		if (this->mUp != that.mUp)
			return true;
		return false;
	}
}