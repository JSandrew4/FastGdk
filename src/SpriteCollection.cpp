/******************************************************************************/
/*                                                                            */
/*  SpriteCollection.cpp                                                      */
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

#include <Fast/SpriteCollection.hpp>
#include <Fast/Texture2DCollection.hpp>
#include <Fast/ModelCollection.hpp>
#include <Fast/ModelData.hpp>
//#include <Fast/ShaderProgramCollection.hpp>
#include <Fast/String.hpp>
#include <Fast/Sprite.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/AssetData.hpp>
#include <Fast/Error.hpp>
#include <Fast/GraphicsContext.hpp>

namespace Fast
{/* TODO: Remove
	void SpriteCollection::BuildDefaultResource() {
		mResources.SetElementCount(1);
		SpriteData sd;
		sd.SetName("DefaultSprite");
		sd.AddTexture2DAndSpriteSheetNames("DefaultTexture2D", "");
		Sprite s(sd, this);
		SetResourceRetained(AddResource(s.GetResource(), &s), true);
		// Create a quad for sprites to be drawn onto
		ModelData modelData;
		MeshData meshData;
		Array<Vertex> vertices(6);
		vertices[0] = Vertex(0, 0, 0, 0, 0);
		vertices[1] = Vertex(0, 0, 1, 0, 1);
		vertices[2] = Vertex(1, 0, 1, 1, 1);
		vertices[3] = Vertex(0, 0, 0, 0, 0);
		vertices[4] = Vertex(1, 0, 1, 1, 1);
		vertices[5] = Vertex(1, 0, 0, 1, 0);
		meshData.SetName("Main");
		meshData.AppendVertices(vertices);
		modelData.SetName("SpriteQuad");
		modelData.AddMeshData(meshData);
		mSurfaceQuad.Load(modelData);
	}
	*/
	SpriteCollection::SpriteCollection(Texture2DCollection *texture2DCollection,
		ModelCollection *modelCollection,
		ShaderProgramCollection *shaderProgramCollection)
	:	mTexture2DCollection(*texture2DCollection),
		mModelCollection(*modelCollection),
		mShaderProgramCollection(*shaderProgramCollection),
		mSurfaceQuad()
	{ }

	SpriteCollection::~SpriteCollection() {
		UnloadAllResources();
	}

	ErrorType SpriteCollection::LoadResource(const String &fileName) {
		Sprite sprite;
		ErrorType error = sprite.Load(fileName, this);
		if (!error)
			SetResourceRetained(sprite.GetID(), true);
		return error;
	}

	ErrorType SpriteCollection::LoadResource(StreamReader *streamReader) {
		Sprite sprite;
		ErrorType error = sprite.Load(streamReader, this);
		if (!error)
			SetResourceRetained(sprite.GetID(), true);
		return error;
	}

	ErrorType SpriteCollection::LoadResource(const AssetData &assetData) {
		Sprite sprite;
		ErrorType error = sprite.Load((SpriteData&)assetData, this);
		if (!error)
			SetResourceRetained(sprite.GetID(), true);
		return error;
	}

	void SpriteCollection::UnloadResource(Int id) {
		UnloadReferences(id);
		mResources[id].SetActive(false);
		mResources[id].GetTexture2DSurfaceArray()->Clear();
	}

	Texture2DCollection* SpriteCollection::GetTexture2DCollection() {
		return &mTexture2DCollection;
	}

	const Texture2DCollection& SpriteCollection::GetTexture2DCollection() const
	{
		return mTexture2DCollection;
	}

	ModelCollection* SpriteCollection::GetModelCollection() {
		return &mModelCollection;
	}

	const ModelCollection& SpriteCollection::GetModelCollection() const {
		return mModelCollection;
	}

	ShaderProgramCollection* SpriteCollection::GetShaderProgramCollection() {
		return &mShaderProgramCollection;
	}

	const ShaderProgramCollection&
		SpriteCollection::GetShaderProgramCollection() const
	{
		return mShaderProgramCollection;
	}

	GraphicsContext* SpriteCollection::GetGraphicsContext() {
		return GetTexture2DCollection()->GetGraphicsContext();
	}

	const GraphicsContext& SpriteCollection::GetGraphicsContext() const {
		return GetTexture2DCollection().GetGraphicsContext();
	}
}