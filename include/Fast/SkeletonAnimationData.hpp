/******************************************************************************/
/*                                                                            */
/*  SkeletonAnimationData.hpp                                                 */
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

#ifndef FastSkeletonAnimationDataHppIncluded
#define FastSkeletonAnimationDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/SkeletonPose.hpp>
#include <Fast/SkeletonAnimationKeyFrame.hpp>
#include <Fast/SkeletonAnimationAction.hpp>
#include <Fast/AssetData.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class String;
	class StreamReader;

	class FastApi SkeletonAnimationData : public AssetData
	{
	private:
		Array<SkeletonPose>					mPoses;
		Array<SkeletonAnimationKeyFrame>	mKeyFrames;
		Array<SkeletonAnimationAction>		mActions;
	public:
		// (Con/De)structors
		SkeletonAnimationData();
		SkeletonAnimationData(const SkeletonAnimationData &that);
		SkeletonAnimationData(const String &fileName);
		SkeletonAnimationData(StreamReader *streamReader);
		~SkeletonAnimationData();
		// Allocators
		ErrorType	Load(const String &fileName);
		ErrorType	Load(StreamReader *streamReader);
		void		Unload();
		// Modify functions
		void	AddAction(const SkeletonAnimationAction &action);
		void	InsertAction(const SkeletonAnimationAction &action, Int index);
		void	ReplaceAction(const SkeletonAnimationAction &action, Int index);
		void	RemoveAction(Int index);
		// Get functions
		SkeletonAnimationAction*		GetAction(Int index);
		const SkeletonAnimationAction&	GetAction(Int index) const;
		SkeletonAnimationAction*		GetAction(const String &name);
		const SkeletonAnimationAction&	GetAction(const String &name) const;
		Int								GetActionIndex(
											const String &name) const;
		// Operators
		SkeletonAnimationData&	operator= (const SkeletonAnimationData &that);
		Bool					operator==(const SkeletonAnimationData &that)
									const;
		Bool					operator!=(const SkeletonAnimationData &That)
									const;
	};
}

#endif // FastSkeletonAnimationDataHppIncluded