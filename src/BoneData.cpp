/******************************************************************************/
/*                                                                            */
/*  BoneData.cpp                                                              */
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

#include <Fast/BoneData.hpp>

#include "Undefs.hpp"

namespace Fast
{
	BoneData::BoneData() {
		mLength = 0.0f;
		mParentBoneID = 0;
	}

	BoneData::BoneData(const BoneData &that) {
		*this = that;
	}

	BoneData::~BoneData() { }

	const String& BoneData::GetName() const {
		return mName;
	}

	Float BoneData::GetLength() const {
		return mLength;
	}

	Int BoneData::GetParentBoneID() const {
		return mParentBoneID;
	}

	Array<Int>* BoneData::GetChildBoneIDArray() {
		return &mChildBoneIDArray;
	}

	const Array<Int>& BoneData::GetChildBoneIDArray() const {
		return mChildBoneIDArray;
	}

	void BoneData::SetName(const String &name) {
		mName = name;
	}

	void BoneData::SetLength(Float length) {
		mLength = length;
	}

	void BoneData::SetParentBoneID(Int parentBoneID) {
		mParentBoneID = parentBoneID;
	}

	BoneData& BoneData::operator=(const BoneData &that) {
		this->mLength = that.mLength;
		this->mParentBoneID = that.mParentBoneID;
		this->mName = that.mName;
		this->mChildBoneIDArray = that.mChildBoneIDArray;
		return *this;
	}

	Bool BoneData::operator==(const BoneData &that) const {
		if (this->mLength != that.mLength)
			return false;
		if (this->mParentBoneID != that.mParentBoneID)
			return false;
		if (this->mName != that.mName)
			return false;
		if (this->mChildBoneIDArray.GetElementCount() !=
			that.mChildBoneIDArray.GetElementCount())
		{
			return false;
		}
		for (Int i = 0; i < mChildBoneIDArray.GetElementCount(); i++)
			if (this->mChildBoneIDArray[i] != that.mChildBoneIDArray[i])
				return false;
		return true;
	}

	Bool BoneData::operator!=(const BoneData &that) const {
		if (this->mLength != that.mLength)
			return true;
		if (this->mParentBoneID != that.mParentBoneID)
			return true;
		if (this->mName != that.mName)
			return true;
		if (this->mChildBoneIDArray.GetElementCount() !=
			that.mChildBoneIDArray.GetElementCount())
		{
			return true;
		}
		for (Int i = 0; i < mChildBoneIDArray.GetElementCount(); i++)
			if (this->mChildBoneIDArray[i] != that.mChildBoneIDArray[i])
				return true;
		return false;
	}
}