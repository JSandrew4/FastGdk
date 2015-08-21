/******************************************************************************/
/*                                                                            */
/*  Bone.cpp                                                                  */
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

#include <Fast/Bone.hpp>
#include <Fast/String.hpp>
#include <Fast/Skeleton.hpp>
#include <Fast/SkeletonAnimation.hpp>
#include <Fast/SkeletonAnimationAction.hpp>
#include <Fast/SkeletonAnimationKeyFrame.hpp>
#include <Fast/Model.hpp>

namespace Fast
{
	Bone::Bone(const Bone &that) :
		mSkeleton(that.mSkeleton)
	{
		*this = that;
	}

	Bone::Bone(Skeleton *skeleton, Int index) :
		mSkeleton(*skeleton)
	{
		mIndex = index;
		mCurrentAnimationIndex = 0;
		mCurrentActionIndex = 0;
	}

	Bone::~Bone() { }

	void Bone::SetAnimationAction(Int animationIndex, Int actionIndex) {
		// TODO
	}

	void Bone::SetAnimationAction(const String &animationName, Int actionIndex)
	{
		// TODO
	}

	void Bone::SetAnimationAction(Int index, const String &actionName) {
		// TODO
	}

	void Bone::SetAnimationAction(const String &animationName,
		const String &actionName)
	{
		// TODO
	}

	Skeleton* Bone::GetSkeleton() {
		return &mSkeleton;
	}

	const Skeleton& Bone::GetSkeleton() const {
		return mSkeleton;
	}

	Int Bone::GetIndex() const {
		return mIndex;
	}

	SkeletonAnimation* Bone::GetCurrentAnimation() {
		return mSkeleton.GetModel()->GetCollection()->GetResource(
			mSkeleton.GetModel()->GetID())->mSkeletonData[
			mSkeleton.GetIndex()].GetAnimation(mCurrentAnimationIndex);
	}

	const SkeletonAnimation& Bone::GetCurrentAnimation() const {
		return GetSkeleton().GetModel().GetCollection().GetResource(
			GetSkeleton().GetModel().GetID()).mSkeletonData[
			GetSkeleton().GetIndex()].GetAnimation(mCurrentAnimationIndex);
	}

	Int Bone::GetCurrentAnimationIndex() const {
		return mCurrentAnimationIndex;
	}

	SkeletonAnimationAction* Bone::GetCurrentAction() {
		return GetCurrentAnimation()->GetCollection()->GetResource(
			GetCurrentAnimation()->GetID())->mData.GetAction(
			mCurrentActionIndex);
	}

	const SkeletonAnimationAction& Bone::GetCurrentAction() const {
		return GetCurrentAnimation().GetCollection().GetResource(
			GetCurrentAnimation().GetID()).mData.GetAction(
			mCurrentActionIndex);
	}

	Int Bone::GetCurrentActionIndex() const {
		return mCurrentActionIndex;
	}

	Bone& Bone::operator=(const Bone &that) {
		this->mSkeleton = that.mSkeleton;
		this->mIndex = that.mIndex;
		this->mCurrentAnimationIndex = that.mCurrentAnimationIndex;
		this->mCurrentActionIndex = that.mCurrentActionIndex;
		return *this;
	}

	Bool Bone::operator==(const Bone &that) const {
		if (this->mSkeleton != that.mSkeleton)
			return false;
		if (this->mIndex != that.mIndex)
			return false;
		if (this->mCurrentAnimationIndex != that.mCurrentAnimationIndex)
			return false;
		if (this->mCurrentActionIndex != that.mCurrentActionIndex)
			return false;
		return true;
	}

	Bool Bone::operator!=(const Bone &that) const {
		if (this->mSkeleton != that.mSkeleton)
			return true;
		if (this->mIndex != that.mIndex)
			return true;
		if (this->mCurrentAnimationIndex != that.mCurrentAnimationIndex)
			return true;
		if (this->mCurrentActionIndex != that.mCurrentActionIndex)
			return true;
		return false;
	}
}