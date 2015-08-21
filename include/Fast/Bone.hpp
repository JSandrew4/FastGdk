/******************************************************************************/
/*                                                                            */
/*  Bone.hpp                                                                  */
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

#ifndef FastBoneHppIncluded
#define FastBoneHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class Skeleton;
	class String;
	class SkeletonAnimation;
	class SkeletonAnimationAction;
	class SkeletonAnimationKeyFrame;

	class FastApi Bone
	{
	protected:
		Skeleton	&mSkeleton;
		Int			mIndex;
		Int			mCurrentAnimationIndex;
		Int			mCurrentActionIndex;
		Float		mCurrentAnimationKeyFrame; // TODO
	public:
		// (Con/De)structors
		Bone(const Bone &that);
		Bone(Skeleton *skeleton, Int index);
		~Bone();
		// Setters
		void	SetAnimationAction(Int animationIndex, Int actionIndex);
		void	SetAnimationAction(const String &animationName,
					Int actionIndex);
		void	SetAnimationAction(Int index, const String &actionName);
		void	SetAnimationAction(const String &animationName,
					const String &actionName);
		// Getters
		Skeleton*						GetSkeleton();
		const Skeleton&					GetSkeleton() const;
		Int								GetIndex() const;
		SkeletonAnimation*				GetCurrentAnimation();
		const SkeletonAnimation&		GetCurrentAnimation() const;
		Int								GetCurrentAnimationIndex() const;
		SkeletonAnimationAction*		GetCurrentAction();
		const SkeletonAnimationAction&	GetCurrentAction() const;
		Int								GetCurrentActionIndex() const;
		// Operators
		Bone&	operator= (const Bone &that);
		Bool	operator==(const Bone &that) const;
		Bool	operator!=(const Bone &that) const;
	};

	template class FastApi Array<Bone>;
}

#endif // FastBoneHppIncluded
