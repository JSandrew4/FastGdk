/******************************************************************************/
/*                                                                            */
/*  Texture2DFont.cpp                                                         */
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

#include <Fast/Texture2DFont.hpp>
#include <Fast/String.hpp>
#include <Fast/FontCollection.hpp>
#include <Fast/FontData.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Error.hpp>

#include <FTGL/ftgl.h>

#include "OpenGL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	using namespace FTGL;

	ErrorType Texture2DFont::SetUp(const String &fullName,
		const FontData &fontData, Int faceResolution, Int faceSize,
		FontCollection *collection)
	{/*
		// Check for existing font with matching checksum
		// TODO: how should checksums for fonts work?
		// If no match, store fontData in new resource ...
		Texture2DFont *ftFont = new Texture2DFont(*((Texture2DFont*)fontData.GetFTFont()));
		FontResource fontResource(ftFont);
		// Now finish up the new resource
		fontResource.SetName(fullName);
		// TODO: fontResource.mChecksum = checksum;
		fontResource.SetActive(true);
		fontResource.SetRetained(false);
		mID = collection->AddResource(fontResource, this);
		mCollection = collection;*/
		return kErrorNone;
	}

	Texture2DFont::Texture2DFont()
	:	Font()
	{ }

	Texture2DFont::Texture2DFont(const Texture2DFont &that)
	:	Font()
	{
		*this = that;
	}

	Texture2DFont::Texture2DFont(const String &fileName,
		FontCollection *collection)
	:	Font()
	{
		Load(fileName, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	Texture2DFont::Texture2DFont(const String &fileName, Int faceResolution,
		Int faceSize, FontCollection *collection)
	:	Font()
	{
		Load(fileName, faceResolution, faceSize, collection);
	}

	Texture2DFont::Texture2DFont(StreamReader *streamReader,
		FontCollection *collection)
	:	Font()
	{
		Load(streamReader, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	Texture2DFont::Texture2DFont(StreamReader *streamReader, Int faceResolution,
		Int faceSize, FontCollection *collection)
	:	Font()
	{
		Load(streamReader, faceResolution, faceSize, collection);
	}

	Texture2DFont::Texture2DFont(const FontData &fontData,
		FontCollection *collection)
	:	Font()
	{
		Load(fontData, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	Texture2DFont::Texture2DFont(const FontData &fontData, Int faceResolution,
		Int faceSize, FontCollection *collection)
	:	Font()
	{
		Load(fontData, faceResolution, faceSize, collection);
	}

	Texture2DFont::~Texture2DFont() {
		Unbind();
	}

	void Texture2DFont::DrawString(const String &text, Alignment alignment) {
		if (mID <= 0)
			return;
		FTFont *tf = (FTFont*)
			GetCollection()->GetResource(mID)->GetFTFont();
		Float h = GetAscender();
		Float w = GetStringWidth(text);
		Float x = 0.0f, y = 0.0f;
		switch (alignment)
		{
		case kAlignCenter:
			x -= w / 2.0f;
			y -= h / 2.0f;
			break;
		case kAlignTopLeft:
			y -= h;
			break;
		case kAlignTopMiddle:
			x -= w / 2.0f;
			y -= h;
			break;
		case kAlignTopRight:
			x -= w;
			y -= h;
			break;
		case kAlignMiddleLeft:
			y -= h / 2.0f;
			break;
		case kAlignMiddleRight:
			x -= w;
			y -= h / 2.0f;
			break;
		case kAlignBottomLeft:
			break;
		case kAlignBottomMiddle:
			x -= w / 2.0f;
			break;
		case kAlignBottomRight:
			x -= w;
			break;
		case kAlignNone:
		default:
			break;
		}
		/*glPushMatrix();
			glTranslatef(x, y, 0.0f);
			tf->Render(text.GetWString().mData);
		glPopMatrix();*/
	}
	/*	// TODO: We probably don't need this function now. The Text entity will
		//	handle drawing a font to a frameBuffer instead
	Texture2DSurface Texture2DFont::DrawStringToTexture2D(
		const String &text, const Vector2D &scale)
	{
		// TODO: Render to texture with Fbo?
		return Texture2DSurface(GetCollection()->GetTexture2DCollection());
	}*/

	Texture2DFont& Texture2DFont::operator=(const Texture2DFont &that) {
		this->Bind(that.mCollection, that.mID);
		return *this;
	}

	Bool Texture2DFont::operator==(const Texture2DFont &that) {
		if (this->mCollection != that.mCollection)
			return false;
		if (this->mID != that.mID)
			return false;
		return true;
	}

	Bool Texture2DFont::operator!=(const Texture2DFont &that) {
		if (this->mCollection != that.mCollection)
			return true;
		if (this->mID != that.mID)
			return true;
		return false;
	}
}