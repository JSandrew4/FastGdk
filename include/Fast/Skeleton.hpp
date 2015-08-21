/******************************************************************************/
/*                                                                            */
/*  Skeleton.hpp                                                              */
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

#ifndef FastSkeletonHppIncluded
#define FastSkeletonHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/Bone.hpp>
#include <Fast/Matrix.hpp>

namespace Fast
{
	class String;
	class Model;

	class FastApi Skeleton
	{
	private:
		Model		*mModel;
		Int			mIndex;
		Array<Bone>	mBones;
		Matrix		mMatrix;
	public:
		// (Con/De)structors
		Skeleton(Model *model, Int index,
			const Array<Bone> &bones, const Matrix &matrix);
		Skeleton(const Skeleton &that);
		~Skeleton();
		// Setters
		void	SetMatrix(const Matrix &matrix);
		// Getters
		Model*			GetModel();
		const Model&	GetModel() const;
		Int				GetIndex() const;
		Int				GetNumBones() const;
		Bone*			GetBone(Int index);
		const Bone&		GetBone(Int index) const;
		Bone*			GetBone(const String &name);
		const Bone&		GetBone(const String &name) const;
		Int				GetBoneIndex(const String &name) const;
		const Matrix&	GetMatrix() const;
		// Operators
		Skeleton&	operator= (const Skeleton &that);
		Bool		operator==(const Skeleton &that) const;
		Bool		operator!=(const Skeleton &that) const;
	};

	template class FastApi Array<Skeleton>;
}

#endif // FastSkeletonHppIncluded
