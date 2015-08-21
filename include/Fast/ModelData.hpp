/******************************************************************************/
/*                                                                            */
/*  ModelData.hpp                                                             */
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

#ifndef FastModelDataHppIncluded
#define FastModelDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/AssetData.hpp>
#include <Fast/SkeletonData.hpp>
#include <Fast/MeshData.hpp>
#include <Fast/SkeletonAnimation.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class String;
	class StreamReader;

	template class FastApi Array<MeshData>;

	class FastApi ModelData : public AssetData
	{
	private:
		Array<SkeletonData>			mSkeletonData;
		Array<MeshData>				mMeshData;
		Array<SkeletonAnimation>	mSkeletonAnimations;
	public:
		// (Con/De)structors
		ModelData();
		ModelData(const ModelData &that);
		ModelData(const String &fileName);
		ModelData(StreamReader *streamReader);
		~ModelData();
		// Allocators
		ErrorType	Load(const String &fileName);
		ErrorType	Load(StreamReader *streamReader);
		void		Unload();
		// Getters
		SkeletonData*				GetSkeletonData(Int index);
		const SkeletonData&			GetSkeletonData(Int index) const;
		MeshData*					GetMeshData(Int index);
		const MeshData&				GetMeshData(Int index) const;
		SkeletonAnimation*			GetSkeletonAnimation(Int index);
		const SkeletonAnimation&	GetSkeletonAnimation(Int index) const;
		// Modifiers
		Int		GetNumSkeletonData() const;
		void	AddSkeletonData(const SkeletonData &skeleton);
		void	InsertSkeletonData(const SkeletonData &skeleton, Int index);
		void	ReplaceSkeletonData(const SkeletonData &skeleton, Int index);
		void	RemoveSkeletonData(Int index);
		Int		GetNumMeshData() const;
		void	AddMeshData(const MeshData &mesh);
		void	InsertMeshData(const MeshData &mesh, Int index);
		void	ReplaceMeshData(const MeshData &mesh, Int index);
		void	RemoveMeshData(Int index);
		Int		GetNumSkeletonAnimations() const;
		void	AddSkeletonAnimation(const SkeletonAnimation &animation);
		void	InsertSkeletonAnimation(const SkeletonAnimation &animation,
					Int index);
		void	ReplaceSkeletonAnimation(const SkeletonAnimation &animation,
					Int index);
		void	RemoveSkeletonAnimation(Int index);
	};
}

#endif // FastModelDataHppIncluded
