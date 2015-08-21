/******************************************************************************/
/*                                                                            */
/*  Skeleton.cpp                                                              */
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

#include <Fast/Skeleton.hpp>
#include <Fast/Model.hpp>

namespace Fast
{
	Skeleton::Skeleton(const Skeleton &that) {
		*this = that;
	}

	Skeleton::Skeleton(Model *model, Int index,
		const Array<Bone> &bones, const Matrix &matrix)
	{
		mModel = model;
		mIndex = index;
		mBones = bones;
		mMatrix = matrix;
	}

	Skeleton::~Skeleton() { }

	void Skeleton::SetMatrix(const Matrix &matrix) {
		mMatrix = matrix;
	}

	Model* Skeleton::GetModel() {
		return mModel;
	}

	const Model& Skeleton::GetModel() const {
		return *mModel;
	}

	Int Skeleton::GetIndex() const {
		return mIndex;
	}

	Int Skeleton::GetNumBones() const {
		return mBones.GetElementCount();
	}

	Bone* Skeleton::GetBone(Int index) {
		return &mBones[index];
	}

	const Bone& Skeleton::GetBone(Int index) const {
		return mBones[index];
	}

	Bone* Skeleton::GetBone(const String &name) {
		return &mBones[GetBoneIndex(name)];
	}

	const Bone& Skeleton::GetBone(const String &name) const {
		return mBones[GetBoneIndex(name)];
	}

	Int Skeleton::GetBoneIndex(const String &name) const {
		for (Int i = 0; i < mBones.GetElementCount(); i++) {
			if (name == GetModel().GetCollection().GetResource(
				mModel->GetID()).mSkeletonData[mIndex].GetBoneData(i).GetName())
			{
				return i;
			}
		}
		return 0;
	}

	const Matrix& Skeleton::GetMatrix() const {
		return mMatrix;
	}

	Skeleton& Skeleton::operator=(const Skeleton &that) {
		this->mModel = that.mModel;
		this->mIndex = that.mIndex;
		this->mBones = that.mBones;
		this->mMatrix = that.mMatrix;
		return *this;
	}

	Bool Skeleton::operator==(const Skeleton &that) const {
		if (this->mModel != that.mModel)
			return false;
		if (this->mIndex != that.mIndex)
			return false;
		if (this->mBones.GetElementCount() != that.mBones.GetElementCount())
			return false;
		for (Int i = 0; i < this->mBones.GetElementCount(); i++)
			if (this->mBones[i] != that.mBones[i])
				return false;
		if (this->mMatrix != that.mMatrix)
			return false;
		return true;
	}

	Bool Skeleton::operator!=(const Skeleton &that) const {
		if (this->mModel != that.mModel)
			return true;
		if (this->mIndex != that.mIndex)
			return true;
		if (this->mBones.GetElementCount() != that.mBones.GetElementCount())
			return true;
		for (Int i = 0; i < this->mBones.GetElementCount(); i++)
			if (this->mBones[i] != that.mBones[i])
				return true;
		if (this->mMatrix != that.mMatrix)
			return true;
		return false;
	}
}