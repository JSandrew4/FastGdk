/******************************************************************************/
/*                                                                            */
/*  VideoMode.cpp                                                             */
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

#include <Fast/VideoMode.hpp>

#include "Undefs.hpp"

namespace Fast
{
	VideoMode::VideoMode() {
		mWidth = mHeight = mRefreshRate = mBitsPerPixel = 0;
	}

	VideoMode::VideoMode(Int width, Int height, Int bitsPerPixel, Int refreshRate) {
		mWidth = width;
		mHeight = height;
		mBitsPerPixel = bitsPerPixel;
		mRefreshRate = refreshRate;
	}

	Bool VideoMode::operator==(const VideoMode &that) const {
		return (this->mWidth == this->mWidth  &&
			this->mHeight == that.mHeight &&
			this->mBitsPerPixel == that.mBitsPerPixel &&
			this->mRefreshRate == that.mRefreshRate);
	}

	Bool VideoMode::operator!=(const VideoMode &that) const {
		return (this->mWidth != this->mWidth ||
			this->mHeight != that.mHeight ||
			this->mBitsPerPixel != that.mBitsPerPixel ||
			this->mRefreshRate != that.mRefreshRate);
	}
}
