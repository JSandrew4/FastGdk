/******************************************************************************/
/*                                                                            */
/*  ModelData.cpp                                                             */
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

#include <Fast/ModelData.hpp>
#include <Fast/String.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>

#include "OpenGL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	using namespace OpenGL;

	ModelData::ModelData() {
		Unload();
	}

	ModelData::ModelData(const ModelData &that) {
		Unload();
		*this = that;
	}

	ModelData::ModelData(const String &fileName) {
		Unload();
		Load(fileName);
	}

	ModelData::ModelData(StreamReader *streamReader) {
		Unload();
		Load(streamReader);
	}

	ModelData::~ModelData() {
		Unload();
	}

	ErrorType ModelData::Load(const String &fileName) {
		Unload();
		FileReader file(fileName);
		return Load(&file);
	}

	ErrorType ModelData::Load(StreamReader *streamReader) {
		Unload();
		/*
		ErrorType error = kErrorNone;
		if (!streamReader->IsOpen())
			return Error::Throw(kErrorFileNotFound, String("(%s: %s)",
				FastFunctionName, streamReader->GetName().GetData()));
		mName = streamReader->GetName();
		streamReader->SeekTo(0);
		// Check file signature
		Char sig[5];
		memset(sig, 0, 5);
		streamReader->Read(sig, 4);
		error = streamReader->GetError();
		if (error) {
			streamReader->Close();
			Unload();
			return Error::Throw(error, String("(%s: %s)",
				FastFunctionName, streamReader->GetName().GetData()));
		}
		if (strcmp(sig, "GDKM"))
			return Error::Throw(kErrorModelFormatInvalid, String("(%s: %s)",
				FastFunctionName, streamReader->GetName().GetData()));
		// Get meshes
		Int numMeshes = streamReader->ReadInt();
		error = streamReader->GetError();
		if (error) {
			streamReader->Close();
			Unload();
			return Error::Throw(error, String("(%s: %s)",
				FastFunctionName, streamReader->GetName().GetData()));
		}
		mMeshData.Resize(numMeshes);
		for (Int i = 0; i < numMeshes; i++) {
			// Get mesh name
			Byte meshNameLength;
			meshNameLength = streamReader->ReadByte();
			mMeshData[i].mName.Resize(meshNameLength);
			streamReader->Read((Byte*)mMeshData[i].mName.GetData(),
				meshNameLength);
			// Get Matrix
			mMeshData[i].mMatrix = streamReader->ReadMatrix();
			// Get vertices and normals
			Int numVertices = streamReader->ReadInt();
			mMeshData[i].mVertices.Resize(numVertices);
			for (Int j = 0; j < numVertices; j++) {
				streamReader->Read((Byte*)&mMeshData[i].mVertices[j],
					6 * sizeof(Float));
				// Read vertex weights and such (not implemented yet)
				Short numInfluences = streamReader->ReadShort();
				for (Int k = 0; k < numInfluences; k++) {
					streamReader->ReadShort(); // boneId
					streamReader->ReadFloat(); // weight
				}
			}
			// Get faces
			Int numFaces = streamReader->ReadInt();
			mMeshData[i].mFaces.Resize(numFaces);
			for (Int j = 0; j < numFaces; j++) {
				// FIXME: indices to Short, read all in one call
				mMeshData[i].mFaces[j].mIndices[0] = streamReader->ReadInt();
				mMeshData[i].mFaces[j].mIndices[1] = streamReader->ReadInt();
				mMeshData[i].mFaces[j].mIndices[2] = streamReader->ReadInt();
			}
			// FIXME: Is there a skeleton to load?
			Short numBones = streamReader->ReadShort();
			if (numBones > 0) {
				mMeshData[i].mSkeleton.mBones.Resize(numBones);
				// FIXME: Get skeleton name
				Byte skeletonNameLength;
				skeletonNameLength = streamReader->ReadByte();
				mMeshData[i].mSkeleton.mName.Resize(skeletonNameLength);
				streamReader->Read((Byte*)
					mMeshData[i].mSkeleton.mName.GetData(),
					skeletonNameLength);
				// FIXME: Get skeleton matrix
				mMeshData[i].mSkeleton.mMatrix = streamReader->ReadMatrix();
				// FIXME: Get bones
				for (Short j = 0; j < numBones; j++) {
					Byte boneNameLength = streamReader->ReadByte();
					mMeshData[i].mSkeleton.mBones[j].mName.Resize(
						boneNameLength);
					streamReader->Read(
						(Byte*)mMeshData[i].mSkeleton.mBones[j].mName.GetData(),
						boneNameLength);
					mMeshData[i].mSkeleton.mBones[j].mParent =
						streamReader->ReadShort();
					mMeshData[i].mSkeleton.mBones[j].mMatrix =
						streamReader->ReadMatrix();
				}
			}
			// If an error occurred, truncate the broken mesh and return
			error = streamReader->GetError();
			if (error) {
				streamReader->Close();
				mMeshData.Resize(i);
				return Error::Throw(error, String("(%s: %s)",
					FastFunctionName,
					streamReader->GetName().GetData()));
			}
		}
		streamReader->Close();
		*/
		return kErrorNone;
	}

	void ModelData::Unload() {
		mMeshData.Clear();
	}

	SkeletonData* ModelData::GetSkeletonData(Int index) {
		return &mSkeletonData[index];		
	}

	const SkeletonData& ModelData::GetSkeletonData(Int index) const {
		return mSkeletonData[index];
	}

	MeshData* ModelData::GetMeshData(Int index) {
		return &mMeshData[index];
	}

	const MeshData& ModelData::GetMeshData(Int index) const {
		return mMeshData[index];
	}

	SkeletonAnimation* ModelData::GetSkeletonAnimation(Int index) {
		return &mSkeletonAnimations[index];
	}

	const SkeletonAnimation& ModelData::GetSkeletonAnimation(Int index) const {
		return mSkeletonAnimations[index];
	}

	Int ModelData::GetNumSkeletonData() const {
		return mSkeletonData.GetElementCount();
	}

	void ModelData::AddSkeletonData(const SkeletonData &skeleton) {
		mSkeletonData.Append(skeleton);
	}

	void ModelData::InsertSkeletonData(const SkeletonData &skeleton, Int index)
	{
		mSkeletonData.Insert(skeleton, index);	
	}

	void ModelData::ReplaceSkeletonData(const SkeletonData &skeleton, Int index)
	{
		mSkeletonData.Replace(skeleton, index);
	}

	void ModelData::RemoveSkeletonData(Int index) {
		mSkeletonData.Erase(index);
	}

	Int ModelData::GetNumMeshData() const {
		return mMeshData.GetElementCount();
	}

	void ModelData::AddMeshData(const MeshData &mesh) {
		mMeshData.Append(mesh);
	}

	void ModelData::InsertMeshData(const MeshData &mesh, Int index) {
		mMeshData.Insert(mesh, index);
	}

	void ModelData::ReplaceMeshData(const MeshData &mesh, Int index) {
		mMeshData.Replace(mesh, index);
	}

	void ModelData::RemoveMeshData(Int index) {
		mMeshData.Erase(index);
	}

	Int ModelData::GetNumSkeletonAnimations() const {
		return mSkeletonAnimations.GetElementCount();
	}

	void ModelData::AddSkeletonAnimation(const SkeletonAnimation &animation) {
		mSkeletonAnimations.Append(animation);
	}

	void ModelData::InsertSkeletonAnimation(
		const SkeletonAnimation &animation, Int index)
	{
		mSkeletonAnimations.Insert(animation, index);
	}

	void ModelData::ReplaceSkeletonAnimation(
		const SkeletonAnimation &animation, Int index)
	{
		mSkeletonAnimations.Replace(animation, index);
	}

	void ModelData::RemoveSkeletonAnimation(Int index) {
		mSkeletonAnimations.Erase(index);
	}
}
