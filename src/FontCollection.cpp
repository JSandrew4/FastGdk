/******************************************************************************/
/*                                                                            */
/*  FontCollection.cpp                                                        */
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

#include <Fast/FontCollection.hpp>
#include <Fast/Font.hpp>
#include <Fast/FontData.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>

#include "Undefs.hpp"

namespace Fast
{/* TODO: Remove
	void FontCollection::BuildDefaultResource() {
		mResources.SetElementCount(1);
		FontData fd;
		fd.SetName("DefaultFont");
		Font f(this);
		FontResource fr;
		SetResourceRetained(AddResource(fr, &f), true);
	}
	*/
	FontCollection::FontCollection(Texture2DCollection *texture2DCollection) :
		mTexture2DCollection(*texture2DCollection)
	{ }

	FontCollection::~FontCollection() {
		UnloadAllResources();
	}

	ErrorType FontCollection::LoadResource(const String &fileName) {
		return LoadResource(fileName,
			kFastFontDefaultSize, kFastFontDefaultSize);
	}

	ErrorType FontCollection::LoadResource(
		const String &fileName, Int faceResolution, Int faceSize)
	{
		Font font;
		ErrorType error = font.Load(fileName,
			faceResolution, faceSize, this);
		if (error)
			return Error::Throw(error, String("[%s(\"%s\", %d, %d)]",
			FastFunctionName, fileName.GetCString(),
			faceResolution, faceSize));
		Int id = font.GetID() - 1;
		SetResourceRetained(id, true);
		return kErrorNone;
	}

	ErrorType FontCollection::LoadResource(StreamReader *streamReader) {
		return LoadResource(streamReader,
			kFastFontDefaultSize, kFastFontDefaultSize);
	}

	ErrorType FontCollection::LoadResource(
		StreamReader *streamReader, Int faceResolution, Int faceSize)
	{
		Font font;
		ErrorType error = font.Load(streamReader,
			faceResolution, faceSize, this);
		if (error)
			return Error::Throw(error,
			String("[%s(%p, %d, %d): streamReader.mName=\"%s\"]",
			FastFunctionName, streamReader, faceResolution, faceSize,
			streamReader->GetName().GetCString()));
		Int id = font.GetID() - 1;
		SetResourceRetained(id, true);
		return kErrorNone;
	}

	ErrorType FontCollection::LoadResource(const AssetData &assetData) {
		return LoadResource(assetData,
			kFastFontDefaultSize, kFastFontDefaultSize);
	}

	ErrorType FontCollection::LoadResource(
		const AssetData &assetData, Int faceResolution, Int faceSize)
	{
		Font font;
		ErrorType error = font.Load((FontData&)assetData,
			faceResolution, faceSize, this);
		if (error)
			return Error::Throw(error, String("[%s(%p, %d, %d)]",
				FastFunctionName, &assetData, faceResolution, faceSize));
		Int id = font.GetID() - 1;
		SetResourceRetained(id, true);
		return kErrorNone;
	}

	Texture2DCollection* FontCollection::GetTexture2DCollection() {
		return &mTexture2DCollection;
	}

	const Texture2DCollection& FontCollection::GetTexture2DCollection() const {
		return mTexture2DCollection;
	}

	void FontCollection::UnloadResource(Int id) {
		//mResources[id].GetFontDataBytes()->Clear();
		UnloadReferences(id);
		mResources[id].SetActive(false);
	}
}