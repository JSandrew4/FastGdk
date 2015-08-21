/******************************************************************************/
/*                                                                            */
/*  Texture2DSurface.cpp                                                      */
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

#include <Fast/Texture2DSurface.hpp>
#include <Fast/Checksum.hpp>
#include <Fast/String.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Error.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/SystemConsole.hpp>

#include <string.h>
#include <cstdio>

#include "OpenGL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	void Texture2DParseSubTexture2DAndFileNames(const String &fullName,
		String *imageName, String *subTexture2DName)
	{
		Int colonIndex = fullName.FindFirstOf(":");
		if (colonIndex < 0) {
			*imageName = fullName;
			*subTexture2DName = "";
		} else {
			*imageName = fullName.GetSubString(0, colonIndex);
			*subTexture2DName = fullName.GetSubString(
				colonIndex+1, fullName.GetTextLength()-1);
		}
	}

	ErrorType Texture2DSurface::LoadResource(const String &fullName,
		const String &imageName, const String &subTexture2DName,
		const Texture2DData &texture2DData,
		Texture2DCollection *collection)
	{
		// Check the format before we do anything else
		if (texture2DData.GetBitsPerPixel() != 24 &&
			texture2DData.GetBitsPerPixel() != 32)
		{
			return Error::Throw(kErrorOpenGLFormatInvalid,
				String("[%s(%s, %s, %s, %p)]", FastFunctionName,
				fullName.GetCString(), imageName.GetCString(),
				subTexture2DName.GetCString(), &texture2DData));
		}
		// Check for existing texture with matching checksum
		Checksum checksum(texture2DData.GetPixels().GetData(),
			texture2DData.GetPixels().GetElementCount());
		Bind(collection, collection->GetIDByChecksum(checksum));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (texture2DData.GetSpriteSheet().GetName() !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !texture2DData.GetSpriteSheet().GetName().IsEmpty())
			{
				SpriteSheet spriteSheet;
				if (1 > texture2DData.GetSpriteSheet().GetSubTexture2DCount()) {
					SubTexture2D subTexture2D;
					subTexture2D.mBounds = Rectangle(0, 0,
						GetResource().GetProperties().GetWidth(),
						GetResource().GetProperties().GetHeight());
					subTexture2D.mName = "Default";
					spriteSheet.AddSubTexture2D(subTexture2D);
					spriteSheet.SetName("Auto-Generated SpriteSheet");
					res->GetProperties()->SetSpriteSheet(spriteSheet);
				} else
					res->GetProperties()->SetSpriteSheet(
						texture2DData.GetSpriteSheet());
				mSubTextureIndex =
					res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex(
						subTexture2DName);
			}
			return kErrorNone;
		}
		// If no match, generate new texture
		UInt openGLID = 0;
		GraphicsContext *gc = collection->GetGraphicsContext();
		openGLID = gc->GenerateNewOpenGLTexture2DID();
		if (!openGLID)
			return Error::Throw(kErrorOpenGLGenTexturesFailure,
				String("[%s(%s, %s, %s, %p)]", FastFunctionName,
				fullName.GetCString(), imageName.GetCString(),
				subTexture2DName.GetCString(), &texture2DData));
		Texture2DResource texture2DResource;
		texture2DResource.SetName(fullName);
		texture2DResource.SetChecksum(checksum);
		texture2DResource.GetProperties()->SetWidth(texture2DData.GetWidth());
		texture2DResource.GetProperties()->SetHeight(texture2DData.GetHeight());
		texture2DResource.GetProperties()->SetBitsPerPixel(
			texture2DData.GetBitsPerPixel());
		texture2DResource.GetProperties()->SetSpriteSheet(
			texture2DData.GetSpriteSheet());
		texture2DResource.SetOpenGLID(openGLID);
		texture2DResource.SetActive(true);
		texture2DResource.SetRetained(false);
		mID = collection->AddResource(texture2DResource, this);
		mCollection = collection;
		gc->StoreTexture2DData(openGLID, texture2DData);
		return kErrorNone;
	}

	Texture2DSurface::Texture2DSurface() : AssetImplementer() {
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Unbind();
	}

	Texture2DSurface::Texture2DSurface(const Texture2DSurface &that)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		*this = that;
	}

	Texture2DSurface::Texture2DSurface(UInt openGLTexture2DID,
		Texture2DCollection *collection)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(openGLTexture2DID, collection);
	}

	Texture2DSurface::Texture2DSurface(UInt openGLTexture2DID,
		Texture2DCollection *collection, const String &spriteSheetFileName)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(openGLTexture2DID, collection, spriteSheetFileName);
	}

	Texture2DSurface::Texture2DSurface(UInt openGLTexture2DID,
		Texture2DCollection *collection, const SpriteSheet &spriteSheet)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(openGLTexture2DID, collection, spriteSheet);
	}

	Texture2DSurface::Texture2DSurface(const String &fileName,
		Texture2DCollection *collection)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(fileName, collection);
	}

	Texture2DSurface::Texture2DSurface(const String &fileName,
		Texture2DCollection *collection, const String &spriteSheetFileName) :
		AssetImplementer()
	{
		mSubTextureIndex = 0;
		Load(fileName, collection, spriteSheetFileName);
	}

	Texture2DSurface::Texture2DSurface(const String &fileName,
		Texture2DCollection *collection, const SpriteSheet &spriteSheet)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(fileName, collection, spriteSheet);
	}

	Texture2DSurface::Texture2DSurface(StreamReader *streamReader,
		Texture2DCollection *collection) :
		AssetImplementer()
	{
		mSubTextureIndex = 0;
		Load(streamReader, collection);
	}

	Texture2DSurface::Texture2DSurface(StreamReader *streamReader,
		Texture2DCollection *collection, const String &spriteSheetFileName)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(streamReader, collection, spriteSheetFileName);
	}

	Texture2DSurface::Texture2DSurface(StreamReader *streamReader,
		Texture2DCollection *collection, const SpriteSheet &spriteSheet)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(streamReader, collection, spriteSheet);
	}

	Texture2DSurface::Texture2DSurface(const Texture2DData &texture2DData,
		Texture2DCollection *collection)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(texture2DData, collection);
	}

	Texture2DSurface::Texture2DSurface(const Texture2DData &texture2DData,
		Texture2DCollection *collection, const String &subTexture2DName)
	:	AssetImplementer()
	{
		printf("Created texture surface %p\n", this);
		mSubTextureIndex = 0;
		Load(texture2DData, collection, subTexture2DName);
	}

	Texture2DSurface::~Texture2DSurface() {
		Unbind();
		printf("Freed texture surface %p\n", this);
	}

	ErrorType Texture2DSurface::Load(UInt openGLTexture2DID,
		Texture2DCollection *collection)
	{
		return Load(openGLTexture2DID, collection, "");
	}

	ErrorType Texture2DSurface::Load(UInt openGLTexture2DID,
		Texture2DCollection *collection,
		const String &spriteSheetFileName)
	{
		Bind(collection, collection->GetIDByOpenGLID(openGLTexture2DID));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (spriteSheetFileName !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !spriteSheetFileName.IsEmpty())
			{
				SpriteSheet spriteSheet;
				if (spriteSheet.Load(spriteSheetFileName)) {
					SubTexture2D subTexture2D;
					subTexture2D.mBounds = Rectangle(0, 0,
						GetResource().GetProperties().GetWidth(),
						GetResource().GetProperties().GetHeight());
					subTexture2D.mName = "Default";
					spriteSheet.AddSubTexture2D(subTexture2D);
					spriteSheet.SetName("Auto-Generated SpriteSheet");
				} 
				res->GetProperties()->SetSpriteSheet(spriteSheet);
			}
			mSubTextureIndex =
				res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex("");
			// All done.
			return kErrorNone;
		}
		// No texture was found, get the image properties
		Texture2DProperties texture2DProperties;
		collection->GetGraphicsContext()->RetrieveTexture2DProperties(
			openGLTexture2DID, &texture2DProperties);
		if (texture2DProperties.GetWidth() == 0)
			return Error::Throw(kErrorInvalidValue,
				String("[%s(%d, %s)]", FastFunctionName,
					openGLTexture2DID, spriteSheetFileName.GetCString()));
		// Get image data so that we can generate a checksum
		Texture2DData texture2DData(texture2DProperties);
		collection->GetGraphicsContext()->RetrieveTexture2DData(
			openGLTexture2DID, &texture2DData);
		// Add to collection
		Texture2DResource texture2DResource;
		texture2DResource.SetName(String("Texture %u", openGLTexture2DID));
		texture2DResource.GetChecksum()->Calculate(
			texture2DData.GetPixels().GetData(),
			texture2DData.GetPixels().GetElementCount());
		texture2DResource.SetProperties(texture2DProperties);
		texture2DResource.GetProperties()->GetSpriteSheet()->Load(
			spriteSheetFileName);
		texture2DResource.SetOpenGLID(openGLTexture2DID);
		texture2DResource.SetActive(true);
		texture2DResource.SetRetained(false);
		mID = collection->AddResource(texture2DResource, this);
		mCollection = collection;
		return kErrorGeneric;
	}

	ErrorType Texture2DSurface::Load(UInt openGLTexture2DID,
		Texture2DCollection *collection,
		const SpriteSheet &spriteSheet)
	{
		Bind(collection, collection->GetIDByOpenGLID(openGLTexture2DID));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (spriteSheet.GetName() !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !spriteSheet.GetName().IsEmpty())
			{
				res->GetProperties()->SetSpriteSheet(spriteSheet);
			}
			mSubTextureIndex =
				res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex("");
			return kErrorNone;
		}
		// No texture was found, get the image properties
		Texture2DProperties texture2DProperties;
		// TODO
		//collection.GetGraphicsContext()->RetrieveTexture2DProperties(
		//	openGLTexture2DID, &texture2DProperties);
		if (texture2DProperties.GetWidth() == 0)
			return Error::Throw(kErrorInvalidValue,
				String("[%s(%d, %s)]", FastFunctionName,
				openGLTexture2DID, spriteSheet.GetName().GetCString()));
		// Get image data so that we can generate a checksum
		Texture2DData texture2DData(texture2DProperties);
		collection->GetGraphicsContext()->RetrieveTexture2DData(
			openGLTexture2DID, &texture2DData);
		// Add to collection
		Texture2DResource texture2DResource;
		texture2DResource.SetName(String("Texture %u", openGLTexture2DID));
		texture2DResource.GetChecksum()->Calculate(
			texture2DData.GetPixels().GetData(),
			texture2DData.GetPixels().GetElementCount());
		texture2DResource.SetProperties(texture2DProperties);
		texture2DResource.GetProperties()->SetSpriteSheet(spriteSheet);
		texture2DResource.SetOpenGLID(openGLTexture2DID);
		texture2DResource.SetActive(true);
		texture2DResource.SetRetained(false);
		mID = collection->AddResource(texture2DResource, this);
		mCollection = collection;
		return kErrorGeneric;
	}

	ErrorType Texture2DSurface::Load(const String &fileName,
		Texture2DCollection *collection) {
		return Load(fileName, collection, "");
	}

	ErrorType Texture2DSurface::Load(const String &fileName,
		Texture2DCollection *collection,
		const String &spriteSheetFileName)
	{
		String fullName = fileName;
		String imageName, subTexture2DName;
		Texture2DParseSubTexture2DAndFileNames(fullName, &imageName, &subTexture2DName);
		Bind(collection, collection->GetIDByName(imageName));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (spriteSheetFileName !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !spriteSheetFileName.IsEmpty())
			{
				SpriteSheet spriteSheet;
				if (spriteSheet.Load(spriteSheetFileName)) {
					SubTexture2D subTexture2D;
					subTexture2D.mBounds = Rectangle(0, 0,
						GetResource().GetProperties().GetWidth(),
						GetResource().GetProperties().GetHeight());
					subTexture2D.mName = "Default";
					spriteSheet.AddSubTexture2D(subTexture2D);
					spriteSheet.SetName("Auto-Generated SpriteSheet");
				} 
				res->GetProperties()->SetSpriteSheet(spriteSheet);
			}
			mSubTextureIndex =
				res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex(
					subTexture2DName);
			return kErrorNone;
		}
		// No texture was found, load the image data
		Texture2DData texture2DData;
		ErrorType error =
			texture2DData.Load(imageName, spriteSheetFileName.IsEmpty() ?
				SpriteSheet() : SpriteSheet(spriteSheetFileName));
		if (error)
			return error;
		return LoadResource(fullName, imageName,
			subTexture2DName, texture2DData, collection);
	}

	ErrorType Texture2DSurface::Load(const String &fileName,
		Texture2DCollection *collection,
		const SpriteSheet &spriteSheet)
	{
		String fullName = fileName;
		String imageName, subTexture2DName;
		Texture2DParseSubTexture2DAndFileNames(fullName, &imageName, &subTexture2DName);
		Bind(collection, collection->GetIDByName(imageName));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (spriteSheet.GetName() !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !spriteSheet.GetName().IsEmpty())
			{
				res->GetProperties()->SetSpriteSheet(spriteSheet);
			}
			mSubTextureIndex =
				res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex(
					subTexture2DName);
			return kErrorNone;
		}
		// No texture was found, load the image data
		Texture2DData texture2DData;
		ErrorType error = texture2DData.Load(imageName, spriteSheet);
		if (error)
			return error;
		return LoadResource(fullName, imageName,
			subTexture2DName, texture2DData, collection);
	}

	ErrorType Texture2DSurface::Load(StreamReader *streamReader,
		Texture2DCollection *collection) {
		return Load(streamReader, collection, "");
	}

	ErrorType Texture2DSurface::Load(StreamReader *streamReader,
		Texture2DCollection *collection,
		const String &spriteSheetFileName)
	{
		String fullName = streamReader->GetName();
		String imageName, subTexture2DName;
		Texture2DParseSubTexture2DAndFileNames(fullName, &imageName, &subTexture2DName);
		Bind(collection, collection->GetIDByName(imageName));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (spriteSheetFileName !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !spriteSheetFileName.IsEmpty())
			{
				SpriteSheet spriteSheet;
				if (spriteSheet.Load(spriteSheetFileName)) {
					SubTexture2D subTexture2D;
					subTexture2D.mBounds = Rectangle(0, 0,
						GetResource().GetProperties().GetWidth(), GetResource().GetProperties().GetHeight());
					subTexture2D.mName = "Default";
					spriteSheet.AddSubTexture2D(subTexture2D);
					spriteSheet.SetName("Auto-Generated SpriteSheet");
				} 
				res->GetProperties()->SetSpriteSheet(spriteSheet);
			}
			mSubTextureIndex =
				res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex(subTexture2DName);
			return kErrorNone;
		}
		// No texture was found, load the image data
		Texture2DData texture2DData;
		ErrorType error =
			texture2DData.Load(streamReader, SpriteSheet(spriteSheetFileName));
		if (error)
			return error;
		return LoadResource(fullName, imageName,
			subTexture2DName, texture2DData, collection);
	}

	ErrorType Texture2DSurface::Load(StreamReader *streamReader,
		Texture2DCollection *collection,
		const SpriteSheet &spriteSheet)
	{
		String fullName = streamReader->GetName();
		String imageName, subTexture2DName;
		Texture2DParseSubTexture2DAndFileNames(fullName, &imageName, &subTexture2DName);
		Bind(collection, collection->GetIDByName(imageName));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (spriteSheet.GetName() !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !spriteSheet.GetName().IsEmpty())
			{
				res->GetProperties()->SetSpriteSheet(spriteSheet);
			}
			mSubTextureIndex =
				res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex(subTexture2DName);
			return kErrorNone;
		}
		// No texture was found, load the image data
		Texture2DData texture2DData;
		ErrorType error = texture2DData.Load(streamReader, spriteSheet);
		if (error)
			return error;
		return LoadResource(fullName, imageName,
			subTexture2DName, texture2DData, collection);
	}

	ErrorType Texture2DSurface::Load(const Texture2DData &texture2DData,
		Texture2DCollection *collection)
	{
		return Load(texture2DData, collection, "");
	}

	ErrorType Texture2DSurface::Load(const Texture2DData &texture2DData,
		Texture2DCollection *collection,
		const String &subTexture2DName)
	{
		String imageName = texture2DData.GetName();
		String fullName = imageName + String(":") + subTexture2DName;
		Bind(collection, collection->GetIDByName(imageName));
		mSubTextureIndex = 0;
		if (-1 < mID) {
			// Check for SpriteSheet update
			Texture2DResource *res = GetCollection()->GetResource(mID);
			if (texture2DData.GetSpriteSheet().GetName() !=
				res->GetProperties()->GetSpriteSheet()->GetName()
				&& !texture2DData.GetSpriteSheet().GetName().IsEmpty())
			{
				res->GetProperties()->SetSpriteSheet(
					texture2DData.GetSpriteSheet());
			}
			mSubTextureIndex =
				res->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex(
					subTexture2DName);
			return kErrorNone;
		}
		// No texture was found, load the image data
		return LoadResource(fullName, imageName,
			subTexture2DName, texture2DData, collection);
	}

	void Texture2DSurface::Unbind() {
		Bind(NULL, -1);
		mSubTextureIndex = 0;
	}

	Int Texture2DSurface::GetSubTexture2DIndex() const {
		return mSubTextureIndex;
	}

	Texture2DData Texture2DSurface::GetData() {
		Texture2DData texture2DData;
		GetData(&texture2DData);
		return texture2DData;
	}

	void Texture2DSurface::GetData(Texture2DData *texture2DData) {
		*texture2DData = Texture2DData(
			*GetCollection()->GetResource(mID)->GetProperties());
		GetCollection()->GetGraphicsContext()->RetrieveTexture2DData(
			GetResource().GetOpenGLID(), texture2DData);
	}

	Int Texture2DSurface::GetWidth() const {
		return GetResource().GetProperties().GetWidth();
	}

	Int Texture2DSurface::GetHeight() const {
		return GetResource().GetProperties().GetHeight();
	}

	void Texture2DSurface::SetSubTexture(Int subTextureIndex) {
		mSubTextureIndex = subTextureIndex;
	}

	void Texture2DSurface::SetSubTexture(const String &subTextureName) {
		mSubTextureIndex =
			GetCollection()->GetResource(
				mID)->GetProperties()->GetSpriteSheet()->GetSubTexture2DIndex(
					subTextureName);
	}

	Texture2DSurface& Texture2DSurface::operator=(const Texture2DSurface &that)
	{
		this->Bind(that.mCollection, that.mID);
		this->mSubTextureIndex = that.mSubTextureIndex;
		return *this;
	}

	Bool Texture2DSurface::operator==(const Texture2DSurface &that) const {
		if (&this->GetCollection() != &that.GetCollection())
			return false;
		if (this->mID != that.mID)
			return false;
		if (this->mSubTextureIndex != that.mSubTextureIndex)
			return false;
		return true;
	}

	Bool Texture2DSurface::operator!=(const Texture2DSurface &that) const {
		if (&this->GetCollection() != &that.GetCollection())
			return true;
		if (this->mID != that.mID)
			return true;
		if (this->mSubTextureIndex != that.mSubTextureIndex)
			return true;
		return false;
	}
}
