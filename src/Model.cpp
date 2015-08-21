/******************************************************************************/
/*                                                                            */
/*  Model.cpp                                                                 */
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

#include <Fast/Model.hpp>
#include <Fast/ModelData.hpp>
#include <Fast/FileStream.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>
#include <Fast/ModelResource.hpp>
#include <Fast/MeshResource.hpp>
#include <Fast/RenderItem.hpp>

#include "OpenGL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	using namespace OpenGL;

	ErrorType Model::LoadResource(const String &name,
		const ModelData &data, ModelCollection *collection)
	{
		Unbind();
		ModelResource res;
		res.SetName(name);
		res.mMeshResources.SetElementCount(data.GetNumMeshData());
		for (Int i = 0; i < res.mMeshResources.GetElementCount(); i++) {
			// Set up internal resource information for the mesh
			Array<VertexStruct> varray;
			Array<TriangleStruct> iarray;
			MeshResource &mres = res.mMeshResources[i];
			mres.mName = data.GetMeshData(i).GetName();
			mres.mMatrix = data.GetMeshData(i).GetMatrix();
			mres.mNumVertices = data.GetMeshData(i).GetNumVertices();
			mres.mNumFaces = data.GetMeshData(i).GetNumFaces();
			mres.mRenderPreferenceDefaults =
				data.GetMeshData(i).GetRenderPreferenceDefaults();
			mres.mOpenGLVertexArrayID = GL_NONE;
			mres.mOpenGLVertexBufferID = GL_NONE;
			mres.mOpenGLIndexBufferID = GL_NONE;
			collection->GetGraphicsContext()->CreateOpenGLMesh(
				&mres, data.GetMeshData(i), mUsage);
			if (!mres.mOpenGLIndexBufferID || !mres.mOpenGLVertexArrayID ||
				!mres.mOpenGLVertexArrayID)
			{
				return Error::Throw(kErrorOpenGLGenBuffersFailure,
					String("[%s(\"%s\", %p, %p)]", FastFunctionName,
					name.GetCString(), &data, collection));
			}
		}
		// TODO: Load skeleton and animations
		mID = collection->AddResource(res, this);
		mCollection = collection;
		return kErrorNone;
	}

	Model::Model()
	:	Renderable(),
		AssetImplementer()
	{
		mUsage = 0;
		Unbind();
	}

	Model::Model(const Model &that)
	:	Renderable(),
		AssetImplementer()
	{
		mUsage = 0;
		*this = that;
	}

	Model::Model(const String &fileName, ModelCollection *collection)
	:	Renderable(),
		AssetImplementer()
	{
		mUsage = 0;
		Load(fileName, collection);
	}

	Model::Model(StreamReader *streamReader, ModelCollection *collection)
	:	Renderable(),
		AssetImplementer()
	{
		mUsage = 0;
		Load(streamReader, collection);
	}

	Model::Model(const ModelData &modelData, ModelCollection *collection)
	:	Renderable(),
		AssetImplementer()
	{
		mUsage = 0;
		Load(modelData, collection);
	}

	Model::~Model() {
		Unbind();
	}

	ErrorType Model::Load(const String &fileName,
		ModelCollection *collection)
	{
		Bind(collection, collection->GetIDByName(fileName));
		if (-1 < mID)
			return kErrorNone;
		// No model found, load the model data
		ModelData modelData;
		ErrorType error = modelData.Load(fileName);
		if (error)
			return error;
		return LoadResource(fileName, modelData, collection);
	}

	ErrorType Model::Load(StreamReader *streamReader,
		ModelCollection *collection)
	{
		Bind(collection, collection->GetIDByName(streamReader->GetName()));
		if (-1 < mID)
			return kErrorNone;
		// No model found, load the model data
		ModelData modelData;
		ErrorType error = modelData.Load(streamReader);
		if (error)
			return error;
		return LoadResource(streamReader->GetName(), modelData, collection);
	}

	ErrorType Model::Load(const ModelData &modelData,
		ModelCollection *collection)
	{
		Bind(collection, collection->GetIDByName(modelData.GetName()));
		if (-1 < mID)
			return kErrorNone;
		// No model found, load the model data
		return LoadResource(modelData.GetName(), modelData, collection);
	}

	void Model::Unbind() {
		/* FIXME: ModelCollection should handle the code below
		for (Int i = 0; i < mMeshes.GetSize(); i++) {
			if (mMeshes[i].GetOpenGLVertexBufferID())
				glDeleteBuffers(1, &mMeshes[i].GetOpenGLVertexBufferID());
			if (mMeshes[i].GetOpenGLIndexBufferID())
				glDeleteBuffers(1, &mMeshes[i].GetOpenGLIndexBufferID());
		}
		*/
		mMeshes.Clear();
	}

	void Model::Draw(FrameBufferSurface *surface) {
		RenderItem ri(surface);
		/* TODO: ModelResource *mr = GetCollection()->GetResource(mID);
		ri.mRenderPreferences = mRenderPreferences;
		ri.mOpenGLProgramID = mr->mOpenGLProgramID;
		ri.mOpenGLVertexArrayID = mr->mOpenGLVertexArrayID;
		ri.mMeshProperties = mr->mMeshProperties;
		ri.mModelviewProjectionMatrix = mModelviewProjectionMatrix;*/
		GetCollection()->GetGraphicsContext()->QueueRenderItem(ri);
	}
/*
	void Model::Draw3D() {
		for (Int i = 0; i < mMeshes.GetSize(); i++) {
			Mesh &mesh = mMeshes[i];
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, mesh.GetOpenGLVertexBufferID());
			glVertexAttribPointer(0, 3, GL_FLOAT,
				GL_FALSE, sizeof(VertexStruct), 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
				mesh.GetOpenGLIndexBufferID());
			glDrawElements(GL_TRIANGLES, mesh.GetNumFaces()*3,
				GL_UNSIGNED_SHORT, reinterpret_cast<void*>(0));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDisableVertexAttribArray(0);
		}
	}*/

	Model& Model::operator=(const Model &that) {
		this->Bind(that.mCollection, that.mID);
		return *this;
	}

	Bool Model::operator==(const Model &that) const {
		if (&this->GetCollection() != &that.GetCollection())
			return false;
		if (this->mID != that.mID)
			return false;
		return true;
	}

	Bool Model::operator!=(const Model &that) const {
		if (&this->GetCollection() != &that.GetCollection())
			return true;
		if (this->mID != that.mID)
			return true;
		return false;
	}
}
