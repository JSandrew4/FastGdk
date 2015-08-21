/******************************************************************************/
/*                                                                            */
/*  SkeletonData.cpp                                                          */
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

#include <Fast/SkeletonData.hpp>

namespace Fast
{
	SkeletonData::SkeletonData() { }

	SkeletonData::SkeletonData(const SkeletonData &that) {
		*this = that;
	}

	SkeletonData::~SkeletonData() { }

	void SkeletonData::SetName(const String &name) {
		mName = name;
	}

	void SkeletonData::SetMatrix(const Matrix &matrix) {
		mMatrix = matrix;
	}

	void SkeletonData::AddBoneData(const BoneData &boneData) {
		// TODO
	}

	void SkeletonData::InsertBoneData(const BoneData &boneData, Int index) {
		// TODO
	}

	void SkeletonData::ReplaceBoneData(const BoneData &boneData, Int index) {
		// TODO
	}

	void SkeletonData::RemoveBoneData(Int index) {
		// TODO
	}

	void SkeletonData::AddAnimation(const SkeletonAnimation &animation) {
		// TODO
	}

	void SkeletonData::InsertAnimation(
		const SkeletonAnimation &animation, Int index)
	{
		// TODO
	}

	void SkeletonData::ReplaceAnimation(
		const SkeletonAnimation &animation, Int index)
	{
		// TODO
	}

	void SkeletonData::RemoveAnimation(Int index) {
		// TODO
	}

	const String& SkeletonData::GetName() const {
		return mName;
	}

	const Matrix& SkeletonData::GetMatrix() const {
		return mMatrix;
	}

	BoneData* SkeletonData::GetBoneData(Int index) {
		return &mBoneData[index];
	}

	const BoneData& SkeletonData::GetBoneData(Int index) const {
		return mBoneData[index];
	}

	BoneData* SkeletonData::GetBoneData(const String &name) {
		return &mBoneData[GetBoneDataIndex(name)];
	}

	const BoneData& SkeletonData::GetBoneData(const String &name) const {
		return mBoneData[GetBoneDataIndex(name)];
	}

	Int SkeletonData::GetBoneDataIndex(const String& name) const {
		// TODO
		return 0;
	}

	SkeletonAnimation* SkeletonData::GetAnimation(Int index) {
		// TODO
		return NULL;
	}

	const SkeletonAnimation& SkeletonData::GetAnimation(Int index) const {
		// TODO
		return *((SkeletonAnimation*)NULL);
	}

	SkeletonAnimation* SkeletonData::GetAnimation(const String &name) {
		// TODO
		return NULL;
	}

	const SkeletonAnimation& SkeletonData::GetAnimation(
		const String &name) const
	{
		// TODO
		return *((SkeletonAnimation*)NULL);
	}

	Int SkeletonData::GetAnimationIndex(const String &name) const {
		// TODO
		return 0;
	}

	SkeletonData& SkeletonData::operator=(const SkeletonData &that) {
		// TODO
		return *this;
	}

	Bool SkeletonData::operator==(const SkeletonData &that) const {
		// TODO
		return false;
	}

	Bool SkeletonData::operator!=(const SkeletonData &that) const {
		// TODO
		return true;
	}
}