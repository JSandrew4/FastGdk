/******************************************************************************/
/*                                                                            */
/*  SkeletonData.hpp                                                          */
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

#ifndef FastSkeletonDataHppIncluded
#define FastSkeletonDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>
#include <Fast/BoneData.hpp>
#include <Fast/SkeletonAnimation.hpp>
#include <Fast/Matrix.hpp>

namespace Fast
{
	class FastApi SkeletonData
	{
	private:
		String						mName;
		Matrix						mMatrix;
		Array<BoneData>				mBoneData;
		Array<SkeletonAnimation>	mAnimations;
	public:
		// (Con/De)structors
		SkeletonData();
		SkeletonData(const SkeletonData &that);
		~SkeletonData();
		// Modify functions
		void	SetName(const String &name);
		void	SetMatrix(const Matrix &matrix);
		void	AddBoneData(const BoneData &boneData);
		void	InsertBoneData(const BoneData &boneData, Int index);
		void	ReplaceBoneData(const BoneData &boneData, Int index);
		void	RemoveBoneData(Int index);
		void	AddAnimation(const SkeletonAnimation &animation);
		void	InsertAnimation(const SkeletonAnimation &animation, Int index);
		void	ReplaceAnimation(const SkeletonAnimation &animation, Int index);
		void	RemoveAnimation(Int index);
		// Get functions
		const String&				GetName() const;
		const Matrix&				GetMatrix() const;
		BoneData*					GetBoneData(Int index);
		const BoneData&				GetBoneData(Int index) const;
		BoneData*					GetBoneData(const String &name);
		const BoneData&				GetBoneData(const String &name) const;
		Int							GetBoneDataIndex(const String& name) const;
		SkeletonAnimation*			GetAnimation(Int index);
		const SkeletonAnimation&	GetAnimation(Int index) const;
		SkeletonAnimation*			GetAnimation(const String &name);
		const SkeletonAnimation&	GetAnimation(const String &name) const;
		Int							GetAnimationIndex(const String &name) const;
		// Operators
		SkeletonData&	operator= (const SkeletonData &that);
		Bool			operator==(const SkeletonData &that) const;
		Bool			operator!=(const SkeletonData &that) const;
	};

	template class FastApi Array<SkeletonData>;
}

#endif // FastSkeletonDataHppIncluded