/******************************************************************************/
/*                                                                            */
/*  Model.hpp                                                                 */
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

#ifndef FastModelHppIncluded
#define FastModelHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/Mesh.hpp>
#include <Fast/Skeleton.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/ModelCollection.hpp>
#include <Fast/Renderable.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class String;
	class StreamReader;
	class ModelData;
	class MeshResource;
	class MeshData;
	class GraphicsContext;
	class Skeleton;
	class SkeletonAnimation;

	class FastApi Model :
		public AssetImplementer<ModelCollection, ModelResource>,
		public Renderable
	{
	private:
		Array<Mesh>			mMeshes;
		Array<Skeleton>		mSkeletons;
		ErrorType	LoadResource(const String &fileName,
						const ModelData &modelData,
						ModelCollection *collection);
	protected:
		Int					mUsage;
	public:
		// (Con/De)structors
		Model();
		Model(const Model &that);
		Model(const String &fileName, ModelCollection *collection);
		Model(const ModelData &modelData, ModelCollection *collection);
		Model(StreamReader *streamReader, ModelCollection *collection);
		~Model();
		// Allocation functions
		ErrorType	Load(const String &fileName,
						ModelCollection *collection);
		ErrorType	Load(const ModelData &modelData,
						ModelCollection *collection);
		ErrorType	Load(StreamReader *streamReader,
						ModelCollection *collection);
		void		Unbind();
		// Getters
		Mesh*						GetMesh(Int index);
		const Mesh&					GetMesh(Int index) const;
		Mesh*						GetMesh(const String &name);
		const Mesh&					GetMesh(const String &name) const;
		Int							GetMeshIndex(const String &name) const;
		Skeleton*					GetSkeleton(Int index);
		const Skeleton&				GetSkeleton(Int index) const;
		Skeleton*					GetSkeleton(const String &name);
		const Skeleton&				GetSkeleton(const String &name) const;
		Int							GetSkeletonIndex(const String &name) const;
		SkeletonAnimation*			GetAnimation(Int index);
		const SkeletonAnimation&	GetAnimation(Int index) const;
		SkeletonAnimation*			GetAnimation(const String &name);
		const SkeletonAnimation&	GetAnimation(const String &name) const;
		Int							GetAnimationIndex(const String &name) const;
		// Setters
		void	AddAnimation(const SkeletonAnimation &animation);
		void	InsertAnimation(const SkeletonAnimation &animation, Int index);
		void	ReplaceAnimation(const SkeletonAnimation &animation, Int index);
		void	RemoveAnimation(Int index);
		// Draw functions
		void	Draw(FrameBufferSurface *surface);
		// Operators
		Model&	operator= (const Model &that);
		Bool	operator==(const Model &that) const;
		Bool	operator!=(const Model &that) const;
	};
}

#endif // FastModelHppIncluded
