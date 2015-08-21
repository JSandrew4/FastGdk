/******************************************************************************/
/*                                                                            */
/*  Texture2DCollection.cpp                                                   */
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

#include <Fast/Texture2DCollection.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/Texture2DSurface.hpp>
#include <Fast/Texture2DData.hpp>
#include <Fast/Texture2DProperties.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>

#include "OpenGL.hpp"
#include "Undefs.hpp"

namespace Fast
{/* TODO: Remove
	void Texture2DCollection::BuildDefaultResource() {
		mResources.SetElementCount(1);
		Array<Byte> tpi;
		tpi.SetElementCount(12, 0);
		tpi[4] = tpi[5] = tpi[7] = tpi[8] = (Byte)255;
		Texture2DData td = Texture2DData(Texture2DProperties(2, 2, 24), tpi);
		td.SetName("DefaultTexture2D");
		Texture2DSurface ts(td, this);
		SetResourceRetained(AddResource(ts.GetResource(), &ts), true);
	}
	*/
	Texture2DCollection::Texture2DCollection(GraphicsContext *graphicsContext) :
		mGraphicsContext(*graphicsContext)
	{ }

	Texture2DCollection::~Texture2DCollection() {
		UnloadAllResources();
	}

	ErrorType Texture2DCollection::LoadResource(const String &fileName) {
		Texture2DSurface texture;
		ErrorType error = texture.Load(fileName, this);
		if (!error)
			SetResourceRetained(texture.GetID(), true);
		return error;
	}

	ErrorType Texture2DCollection::LoadResource(
		const String &fileName, const String &spriteSheetFileName)
	{
		Texture2DSurface texture;
		ErrorType error = texture.Load(fileName, this, spriteSheetFileName);
		if (!error)
			SetResourceRetained(texture.GetID(), true);
		return error;
	}

	ErrorType Texture2DCollection::LoadResource(
		const String &fileName, const SpriteSheet &spriteSheet)
	{
		Texture2DSurface texture;
		ErrorType error = texture.Load(fileName, this, spriteSheet);
		if (!error)
			SetResourceRetained(texture.GetID(), true);
		return error;
	}

	ErrorType Texture2DCollection::LoadResource(StreamReader *streamReader) {
		Texture2DSurface texture;
		ErrorType error = texture.Load(streamReader, this);
		if (!error)
			SetResourceRetained(texture.GetID(), true);
		return error;
	}

	ErrorType Texture2DCollection::LoadResource(
		StreamReader *streamReader, const String &spriteSheetFileName)
	{
		Texture2DSurface texture;
		ErrorType error = texture.Load(streamReader, this, spriteSheetFileName);
		if (!error)
			SetResourceRetained(texture.GetID(), true);
		return error;
	}

	ErrorType Texture2DCollection::LoadResource(
		StreamReader *streamReader, const SpriteSheet &spriteSheet)
	{
		Texture2DSurface texture;
		ErrorType error = texture.Load(streamReader, this, spriteSheet);
		if (!error)
			SetResourceRetained(texture.GetID(), true);
		return error;
	}

	ErrorType Texture2DCollection::LoadResource(const AssetData &assetData) {
		Texture2DSurface texture;
		ErrorType error = texture.Load((Texture2DData&)assetData, this);
		if (!error)
			SetResourceRetained(texture.GetID(), true);
		return error;
	}

	void Texture2DCollection::UnloadResource(Int id) {
		UnloadReferences(id);
		mGraphicsContext.DeleteOpenGLTexture2DID(mResources[id].GetOpenGLID());
		mResources[id].SetActive(false);
	}

	Int Texture2DCollection::GetIDByOpenGLID(UInt openGLTexture2DID) const {
		for (Int i = 0; i < mResources.GetElementCount(); i++)
			if (mResources[i].IsActive())
				if (mResources[i].GetOpenGLID() == openGLTexture2DID)
					return i;
		return -1;
	}

	GraphicsContext* Texture2DCollection::GetGraphicsContext() {
		return &mGraphicsContext;
	}

	const GraphicsContext& Texture2DCollection::GetGraphicsContext() const {
		return mGraphicsContext;
	}
}
