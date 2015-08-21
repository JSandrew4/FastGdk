/******************************************************************************/
/*                                                                            */
/*  Font.cpp                                                                  */
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

#include <Fast/Font.hpp>
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

	String FontCreateFullName(const String &name, Int faceSize) {
	#if defined(FastOSWindows)
		WChar sizeText[17];
		memset(sizeText, 0, 17*sizeof(WChar));
		swprintf_s(sizeText, 16, L"%d", faceSize);
	#else
		Char sizeText[17];
		memset(sizeText, 0, 17);
		sprintf(sizeText, "%d", faceSize);
	#endif
		String fullName = name + String(":") + String(sizeText);
		return fullName;
	}

	ErrorType Font::SetUp(const String &fullName, const FontData &fontData,
		Int faceResolution, Int faceSize, FontCollection *collection)
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
		// TODO: Remove: Bind(collection, collection->AddResource(fontResource, this));
		mID = collection->AddResource(fontResource, this));
		mCollection = collection;*/
		return kErrorNone;
	}

	Font::Font()
	:	AssetImplementer()
	{
		Unbind();
	}

	Font::Font(const Font &that)
	:	AssetImplementer()
	{
		*this = that;
	}

	Font::Font(const String &fileName, FontCollection *collection)
	:	AssetImplementer()
	{
		Load(fileName, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	Font::Font(const String &fileName, Int faceResolution, Int faceSize,
		FontCollection *collection)
	:	AssetImplementer()
	{
		Load(fileName, faceResolution, faceSize, collection);
	}

	Font::Font(StreamReader *streamReader, FontCollection *collection)
	:	AssetImplementer()
	{
		Load(streamReader, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	Font::Font(StreamReader *streamReader, Int faceResolution, Int faceSize,
		FontCollection *collection)
	:	AssetImplementer()
	{
		Load(streamReader, faceResolution, faceSize, collection);
	}

	Font::Font(const FontData &fontData, FontCollection *collection)
	:	AssetImplementer()
	{
		Load(fontData, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	Font::Font(const FontData &fontData, Int faceResolution, Int faceSize,
		FontCollection *collection)
	:	AssetImplementer()
	{
		Load(fontData, faceResolution, faceSize, collection);
	}

	Font::~Font() {
		Unbind();
	}

	ErrorType Font::Load(const String &fileName, FontCollection * collection) {
		return Load(fileName, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	ErrorType Font::Load(const String &fileName,
		Int faceResolution, Int faceSize, FontCollection * collection)
	{
		String fullName = FontCreateFullName(fileName, faceSize);
		Bind(collection, collection->GetIDByName(fullName));
		if (-1 < mID)
			return kErrorNone;
		// No font was found, load the font data
		FontData fontData;
		ErrorType error = fontData.Load(fileName);
		if (error)
			return Error::Throw(error, String("[%s(%s, %d, %d, %p)]",
				FastFunctionName, fileName.GetCString(), faceResolution,
				faceSize, collection));
		return SetUp(fullName, fontData, faceResolution, faceSize, collection);
	}

	ErrorType Font::Load(StreamReader *streamReader,
		FontCollection * collection)
	{
		return Load(streamReader, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	ErrorType Font::Load(StreamReader *streamReader,
		Int faceResolution, Int faceSize, FontCollection * collection)
	{
		String fullName =
			FontCreateFullName(streamReader->GetName(), faceSize);
		Bind(collection, collection->GetIDByName(fullName));
		if (-1 < mID)
			return kErrorNone;
		// No font was found, load the font data
		FontData fontData;
		ErrorType error = fontData.Load(streamReader);
		if (error)
			return Error::Throw(error,
				String("[%s(%p, %d, %d, %p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader, faceResolution, faceSize,
				collection, streamReader->GetName().GetCString()));
		return SetUp(fullName, fontData, faceResolution, faceSize, collection);
	}

	ErrorType Font::Load(const FontData &fontData, FontCollection * collection)
	{
		return Load(fontData, kFastFontDefaultSize,
			kFastFontDefaultSize, collection);
	}

	ErrorType Font::Load(const FontData &fontData,
		Int faceResolution, Int faceSize, FontCollection * collection)
	{
		String fullName =
			FontCreateFullName(fontData.GetName(), faceSize);
		Bind(collection, collection->GetIDByName(fullName));
		if (-1 < mID)
			return kErrorNone;
		// No font was found, load the font data
		return SetUp(fullName, fontData, faceResolution, faceSize, collection);
	}

	void Font::Unbind() {
		Bind(NULL, -1);
	}

	Int Font::GetFaceSize() const {
		return ((FTFont*)
			GetCollection().GetResource(mID
				).GetFTFont())->FaceSize();
	}

	Float Font::GetAscender() const {
		return ((FTTextureFont*)
			GetCollection().GetResource(mID
				).GetFTFont())->Ascender();
	}

	Float Font::GetDescender() const {
		return ((FTTextureFont*)
			GetCollection().GetResource(mID
				).GetFTFont())->Descender();
	}

	Float Font::GetHeight() const {
		return ((FTTextureFont*)
			GetCollection().GetResource(mID
				).GetFTFont())->LineHeight();
	}

	Float Font::GetStringWidth(const String &text) {
		return ((FTTextureFont*)GetCollection()->GetResource(mID
			)->GetFTFont())->Advance(text.GetWString().mData);
	}

	Vector2D Font::GetStringSize(const String &text) {
		Vector2D result;
		GetStringSize(text, &result);
		return result;
	}

	void Font::GetStringSize(const String &text, Vector2D *result) {
		if (mID < 0) {
			*result = kFastVector2DZero;
			return;
		}
		FTFont *tf =
			(FTFont*)GetCollection()->GetResource(mID)->GetFTFont();
		result->mX = tf->Advance(text.GetWString().mData);
		result->mY = tf->LineHeight();
	}

	void Font::DrawString2D(const String &text,
		Alignment alignment, const Vector2D &origin,
		const Vector2D &scale, Float rotationAngle,
		FrameBufferSurface *frameBufferSurface)
	{/*
		glPushMatrix();
			Matrix scaleMatrix, rotationMatrix, translationMatrix, glMatrix;
			Vector3D scale3D = Vector3D(scale.mX, scale.mY, 0.0f);
			Vector3D origin3D = Vector3D(origin.mX, origin.mY, 0.0f);
			Matrix::CreateScale(scale3D, &scaleMatrix);
			Matrix::CreateRotationZ(rotationAngle, &rotationMatrix);
			Matrix::CreateTranslation(origin3D, &translationMatrix);
			glMatrix = scaleMatrix * rotationMatrix * translationMatrix;
			glMultMatrixf(glMatrix.mElements);
			DrawString(text, alignment);
		glPopMatrix();
	*/}

	void Font::DrawString2D(const String &text,
		Alignment alignment, const Matrix &matrix,
		FrameBufferSurface *frameBufferSurface)
	{/*
		glPushMatrix();
			glMultMatrixf(matrix.mElements);
			DrawString(text, alignment);
		glPopMatrix();
	*/}

	void Font::DrawString3D(const String &text,
		Alignment alignment, const Vector3D &origin,
		const Vector3D &scale, const Quaternion &rotation,
		FrameBufferSurface *frameBufferSurface)
	{/*
		glPushMatrix();
			Matrix scaleMatrix, rotationMatrix, translationMatrix, glMatrix;
			Matrix::CreateScale(scale, &scaleMatrix);
			Matrix::CreateFromQuaternion(rotation, &rotationMatrix);
			Matrix::CreateTranslation(origin, &translationMatrix);
			glMatrix = scaleMatrix * rotationMatrix * translationMatrix;
			glMultMatrixf(glMatrix.mElements);
			DrawString(text, alignment);
		glPopMatrix();
	*/}

	void Font::DrawString3D(const String &text,
		Alignment alignment, const Matrix &matrix,
		FrameBufferSurface *frameBufferSurface)
	{/*
		glPushMatrix();
			glMultMatrixf(matrix.mElements);
			DrawString(text, alignment);
		glPopMatrix();
	*/}

	void Font::DrawString(const String &text, Alignment alignment,
		FrameBufferSurface *frameBufferSurface) {
		if (mID < 0)
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
	Texture2DSurface Font::DrawStringToTexture2D(
		const String &text, const Vector2D &scale)
	{
		// TODO: Render to texture with Fbo?
		return Texture2DSurface(GetCollection()->GetTexture2DCollection());
	}*/

	Font& Font::operator=(const Font &that) {
		this->Bind(that.mCollection, that.mID);
		return *this;
	}

	Bool Font::operator==(const Font &that) {
		if (this->mCollection != that.mCollection)
			return false;
		if (this->mID != that.mID)
			return false;
		return true;
	}

	Bool Font::operator!=(const Font &that) {
		if (this->mCollection != that.mCollection)
			return true;
		if (this->mID != that.mID)
			return true;
		return false;
	}
}