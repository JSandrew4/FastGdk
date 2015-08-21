/******************************************************************************/
/*                                                                            */
/*  BonePose.cpp                                                              */
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

#include <Fast/BonePose.hpp>

#include "Undefs.hpp"

namespace Fast
{
	BonePose::BonePose() {
		mID = -1;
	}

	BonePose::BonePose(const BonePose &that) {
		*this = that;
	}

	BonePose::~BonePose() { }

	BonePose& BonePose::operator=(const BonePose &that) {
		this->mID = that.mID;
		this->mRotation = that.mRotation;
		return *this;
	}

	Bool BonePose::operator==(const BonePose &that) const {
		if (this->mID != that.mID)
			return false;
		if (this->mRotation != that.mRotation)
			return false;
		return true;
	}

	Bool BonePose::operator!=(const BonePose &that) const {
		if (this->mID != that.mID)
			return true;
		if (this->mRotation != that.mRotation)
			return true;
		return false;
	}
}