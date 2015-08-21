/******************************************************************************/
/*                                                                            */
/*  FontData.cpp                                                              */
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

#include <Fast/FontData.hpp>
#include <Fast/String.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/Error.hpp>

#include <cstring>
#include <FTGL/ftgl.h>

#include "FTFontFont.hpp"
#include "Undefs.hpp"

using namespace FTGL;

namespace Fast
{
	ErrorType FontData::LoadFTFontFont(const String &name,
		Int faceSize, Int faceResolution)
	{
		if (mFileByteArray.IsEmpty() || !faceSize || !faceResolution) {
			Unload();
			// Don't return error because we should never get to this point
			//	without another error having been thrown already unless there's
			//	really nothing wrong.
			return kErrorNone;
		}
		FTFontFont *ftFont = new FTFontFont((unsigned char*)&mFileByteArray[0],
			(size_t)mFileByteArray.GetElementCount());
		if (ftFont->Error()) {
			delete ftFont;
			Unload();
			return Error::Throw(kErrorFontCreationFailure,
				String("[%s(%s, %d, %d)]", FastFunctionName, name.GetCString(),
					faceSize, faceResolution));
		}
		ftFont->FaceSize(faceSize);
		if (!ftFont->CharMap(ft_encoding_unicode) &&
			!ftFont->CharMap(ft_encoding_latin_1) &&
			!ftFont->CharMap(ft_encoding_none))
		{
			delete ftFont;
			Unload();
			return Error::Throw(kErrorFontInvalidEncoding,
				String("[%s(%s, %d, %d)]", FastFunctionName, name.GetCString(),
					faceSize, faceResolution));
		}
		mName = name;
		mFTFontFont = (CFTFontFont*)ftFont;
		mProperties.SetFaceResolution(faceResolution);
		return kErrorNone;
	}

	FontData::FontData() {
		mFTFontFont = NULL;
		Unload();
	}

	FontData::FontData(const FontData &that) {
		mFTFontFont = NULL;
		*this = that;
	}

	FontData::FontData(const String &fileName) {
		mFTFontFont = NULL;
		Load(fileName);
	}

	FontData::FontData(const String &fileName, Int faceResolution, Int faceSize) {
		mFTFontFont = NULL;
		Load(fileName, faceResolution, faceSize);
	}

	FontData::FontData(StreamReader *streamReader) {
		mFTFontFont = NULL;
		Load(streamReader);
	}

	FontData::FontData(StreamReader *streamReader, Int faceResolution, Int faceSize)
	{
		mFTFontFont = NULL;
		Load(streamReader, faceResolution, faceSize);
	}

	FontData::~FontData() {
		Unload();
	}

	ErrorType FontData::Load(const String &fileName) {
		return Load(fileName, 72, 72);
	}
	
	ErrorType FontData::Load(const String &fileName,
		Int faceResolution, Int faceSize)
	{
		FileReader fr(fileName);
		return Load(&fr, faceResolution, faceSize);
	}

	ErrorType FontData::Load(StreamReader *streamReader) {
		return Load(streamReader, 72, 72);
	}

	ErrorType FontData::Load(StreamReader *streamReader,
		Int faceResolution, Int faceSize)
	{
		Unload();
		if (!faceResolution || !faceSize)
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(%p, %d, %d): streamReader->mName=\"%s\"]",
					FastFunctionName, streamReader, faceSize,
					faceResolution, streamReader->GetName().GetCString()));
		if (!streamReader->IsOpen())
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p, %d, %d): streamReader->mName=\"%s\"]",
					FastFunctionName, streamReader, faceSize,
					faceResolution, streamReader->GetName().GetCString()));
		streamReader->SeekTo(0);
		mFileByteArray.SetElementCount((Int)streamReader->GetSize());
		streamReader->Read(&mFileByteArray[0],
			mFileByteArray.GetElementCount());
		ErrorType error = streamReader->GetError();
		streamReader->Close();
		if (error) {
			Unload();
			return Error::Throw(error,
				String("[%s(%p, %d, %d): streamReader->mName=\"%s\"]",
					FastFunctionName, streamReader, faceSize,
					faceResolution, streamReader->GetName().GetCString()));
		}
		return LoadFTFontFont(streamReader->GetName(),
			faceSize, faceResolution);
	}

	void FontData::Unload() {
		mProperties = FontProperties();
		mName.Clear();
		mFileByteArray.Clear();
		delete mFTFontFont;
		mFTFontFont = NULL;
	}

	Int FontData::GetFaceSize() const {
		if (!mFTFontFont)
			return 0;
		return (Int)((FTFontFont*)mFTFontFont)->FaceSize();
	}

	Float FontData::GetAscender() const {
		if (!mFTFontFont)
			return 0.0f;
		return (Float)((FTFontFont*)mFTFontFont)->Ascender();
	}

	Float FontData::GetDescender() const {
		if (!mFTFontFont)
			return 0.0f;
		return (Float)((FTFontFont*)mFTFontFont)->Descender();
	}

	Float FontData::GetHeight() const {
		if (!mFTFontFont)
			return 0.0f;
		return (Float)((FTFontFont*)mFTFontFont)->LineHeight();
	}

	Int FontData::GetGlyphCount() const {
		if (!mFTFontFont)
			return 0;
		return (Int)((FTFontFont*)mFTFontFont)->GetGlyphCount();
	}

	FontData& FontData::operator=(const FontData &that) {
		this->Unload();
		this->mFileByteArray = that.mFileByteArray;
		this->LoadFTFontFont(that.mName, that.GetFaceSize(),
			that.mProperties.GetFaceResolution());
		return *this;
	}

	Bool FontData::operator==(const FontData &that) const {
		if (this->GetName() != that.GetName())
			return false;
		if (this->mFileByteArray.GetElementCount() !=
			that.mFileByteArray.GetElementCount())
		{
			return false;
		}
		if (memcmp(&this->mFileByteArray[0], &that.mFileByteArray[0],
			that.mFileByteArray.GetElementCount()))
		{
			return false;
		}
		return true;
	}

	Bool FontData::operator!=(const FontData &that) const {
		if (this->GetName() != that.GetName())
			return true;
		if (this->mFileByteArray.GetElementCount() !=
			that.mFileByteArray.GetElementCount())
		{
			return true;
		}
		if (memcmp(&this->mFileByteArray[0], &that.mFileByteArray[0],
			that.mFileByteArray.GetElementCount()))
		{
			return true;
		}
		return false;
	}
}
