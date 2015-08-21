/******************************************************************************/
/*                                                                            */
/*  SpriteSheet.cpp                                                           */
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

#include <Fast/SpriteSheet.hpp>
#include <Fast/String.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/FileWriter.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/StreamWriter.hpp>
#include <Fast/Error.hpp>
#include <Fast/Exception.hpp>

#include <cstdlib>

#include "Undefs.hpp"

namespace Fast
{
	namespace SpriteSheetVersion0_1
	{
		void Load(SpriteSheet *ss, StreamReader *f) {
			// Read SubTexture2Ds
			Int numSubTexture2Ds = f->ReadInt();
			for (Int i = 0; i < numSubTexture2Ds; i++) {
				SubTexture2D si;
				si.mName = f->ReadString(f->ReadInt());
				si.mBounds.mX = f->ReadInt();
				si.mBounds.mY = f->ReadInt();
				si.mBounds.mWidth = f->ReadInt();
				si.mBounds.mHeight = f->ReadInt();
				ss->AddSubTexture2D(si);
			}
		}

		void Save(SpriteSheet *ss, StreamWriter *f) {
			// Write SubTexture2Ds
			f->WriteInt(ss->GetSubTexture2DCount());
			for (Int i = 0; i < ss->GetSubTexture2DCount(); i++) {
				f->WriteInt(ss->GetSubTexture2D(i)->mName.GetSizeInBytes());
				f->WriteString(ss->GetSubTexture2D(i)->mName, false);
				f->WriteInt(ss->GetSubTexture2D(i)->mBounds.mX);
				f->WriteInt(ss->GetSubTexture2D(i)->mBounds.mY);
				f->WriteInt(ss->GetSubTexture2D(i)->mBounds.mWidth);
				f->WriteInt(ss->GetSubTexture2D(i)->mBounds.mHeight);
			}
		}
	}

	SpriteSheet::SpriteSheet() { }

	SpriteSheet::SpriteSheet(const SpriteSheet &that) {
		*this = that;
	}

	SpriteSheet::SpriteSheet(const String &fileName) {
		Load(fileName);
	}

	SpriteSheet::SpriteSheet(StreamReader *streamReader) {
		Load(streamReader);
	}

	ErrorType SpriteSheet::Load(const String &fileName) {
		if (fileName.IsEmpty())
			return kErrorNone;
		FileReader f(fileName);
		ErrorType error = f.GetError();
		if (error)
			return Error::Throw(error, String("[%s(\"%s\")]",
				FastFunctionName, fileName.GetCString()));
		return Load(&f);
	}

	ErrorType SpriteSheet::Load(StreamReader *streamReader) {
		if (!streamReader->IsOpen()) {
			Unload();
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->SeekTo(0);
		ErrorType error = kErrorNone;
		// Read magic number and version
		Char magicNumber[5];
		String magicNumberString;
		Version version;
		streamReader->Read(magicNumber, 4);
		magicNumber[4] = '\0';
		magicNumberString = magicNumber;
		if (magicNumberString != "CSPS")
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		version.mMajor = streamReader->ReadInt();
		version.mMinor = streamReader->ReadInt();
		// Read data by version
		if (version == Version(0,1))
			SpriteSheetVersion0_1::Load(this, streamReader);
		else {
			Unload();
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		// Finish up and return
		error = streamReader->GetError();
		if (error) {
			Unload();
			return Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		return kErrorNone;
	}

	void SpriteSheet::Unload() {
		mSubTexture2DArray.Clear();
	}

	const String& SpriteSheet::GetName() const {
		return mName;
	}

	Int SpriteSheet::GetSubTexture2DCount() const {
		return mSubTexture2DArray.GetElementCount();
	}

	SubTexture2D* SpriteSheet::GetSubTexture2D(Int index) {
		if (0 > index || mSubTexture2DArray.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return &mSubTexture2DArray[index];
	}

	const SubTexture2D& SpriteSheet::GetSubTexture2D(Int index) const {
		if (0 > index || mSubTexture2DArray.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return mSubTexture2DArray[index];
	}

	Int SpriteSheet::GetSubTexture2DIndex(const String &name) const {
		for (Int i = 0; i < mSubTexture2DArray.GetElementCount(); i++)
			if (mSubTexture2DArray[i].mName == name)
				return i;
		return -1;
	}

	void SpriteSheet::SetName(const String &name) {
		mName = name;
	}

	void SpriteSheet::AddSubTexture2D(const SubTexture2D &subImage) {
		mSubTexture2DArray.Append(subImage);
	}

	void SpriteSheet::InsertSubTexture2D(const SubTexture2D &subImage, Int index) {
		if (0 > index || mSubTexture2DArray.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%p, %d)]",
				FastFunctionName, &subImage, index));
		mSubTexture2DArray.Insert(subImage, index);
	}

	void SpriteSheet::ReplaceSubTexture2D(const SubTexture2D &subImage, Int index) {
		if (0 > index || mSubTexture2DArray.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%p, %d)]",
				FastFunctionName, &subImage, index));
		mSubTexture2DArray.Replace(subImage, index);
	}

	void SpriteSheet::EraseSubTexture2D(Int index) {
		if (0 > index || mSubTexture2DArray.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		mSubTexture2DArray.Erase(index);
	}

	void SpriteSheet::ClearSubTexture2DArray() {
		for (Int i = GetSubTexture2DCount() - 1; i >= 0; i--)
			EraseSubTexture2D(i);
	}

	ErrorType SpriteSheet::SaveAs(const String &fileName,
		const Version &version)
	{
		FileWriter f(fileName);
		ErrorType error = f.GetError();
		if (error)
			return Error::Throw(error, String("[%s(\"%s\", %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		// Write magic number and version
		f.WriteString("CSPS", false);
		f.WriteInt(version.mMajor);
		f.WriteInt(version.mMinor);
		// Write data by version
		if (version == Version(0,1))
			SpriteSheetVersion0_1::Save(this, &f);
		else
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(\"%s\", %p): version=(%d, %d)]", FastFunctionName,
				fileName.GetCString(), &version, version.mMajor,
				version.mMinor));
		// Finish up and return
		error = f.GetError();
		if (error)
			return Error::Throw(error, String("[%s(\"%s\", %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		f.Close();
		return kErrorNone;
	}

	SpriteSheet& SpriteSheet::operator= (const SpriteSheet &that) {
		this->Unload();
		this->mSubTexture2DArray = that.mSubTexture2DArray;
		return *this;
	}

	Bool SpriteSheet::operator==(const SpriteSheet &that) const {
		if (this->mSubTexture2DArray.GetElementCount() !=
			that.mSubTexture2DArray.GetElementCount())
		{
			return false;
		}
		for (Int i = 0; i < this->mSubTexture2DArray.GetElementCount(); i++)
			if (this->mSubTexture2DArray[i] != that.mSubTexture2DArray[i])
				return false;
		return true;
	}

	Bool SpriteSheet::operator!=(const SpriteSheet &that) const {
		if (this->mSubTexture2DArray.GetElementCount() !=
			that.mSubTexture2DArray.GetElementCount())
		{
			return true;
		}
		for (Int i = 0; i < this->mSubTexture2DArray.GetElementCount(); i++)
			if (this->mSubTexture2DArray[i] != that.mSubTexture2DArray[i])
				return true;
		return false;
	}
}