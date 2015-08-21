/******************************************************************************/
/*                                                                            */
/*  Texture2DData.cpp                                                         */
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

#include <Fast/Texture2DData.hpp>
#include <Fast/String.hpp>
#include <Fast/FileSystem.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/FileWriter.hpp>
#include <Fast/System.hpp>
#include <Fast/Error.hpp>
#include <Fast/SpriteSheet.hpp>

extern "C" {
#	include <png.h>
#	include <jpeglib.h>
}

#include "PngStream.hpp"
#include "Undefs.hpp"

namespace Fast
{
	ErrorType Texture2DData::LoadPng(const String &fileName) {
		Int y, numRowBytes;
		png_byte bitDepth;
		png_structp png;
		png_infop pngInfo;
		Int numPasses;
		png_bytep *rows;
		UByte header[8];
		FILE *file;
	#if defined(FastOSWindows)
		_wfopen_s((FILE**)&file, fileName.GetWString().mData, L"rb");
	#else
		file = fopen(fileName.GetData(), "rb");
	#endif
		if (!file)
			return Error::Throw(kErrorFileNotFound, String("[%s(\"%s\")]",
				FastFunctionName, fileName.GetCString()));
		fread(header, 1, 8, file);
		if (png_sig_cmp(header, 0, 8))
			return Error::Throw(kErrorImageFormatInvalid, String(
				"[%s(\"%s\")]", FastFunctionName, fileName.GetCString()));
		png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		pngInfo = png_create_info_struct(png);
		//setjmp(png_jmpbuf(png));
		png_init_io(png, file);
		png_set_sig_bytes(png, 8);
		png_read_info(png, pngInfo);
		mProperties.SetWidth(png_get_image_width(png, pngInfo));
		mProperties.SetHeight(png_get_image_height(png, pngInfo));
		bitDepth = png_get_bit_depth(png, pngInfo);
		numPasses = png_set_interlace_handling(png);
		numRowBytes = png_get_rowbytes(png, pngInfo);
		png_read_update_info(png, pngInfo);
		//setjmp(png_jmpbuf(png));
		rows = (png_bytep*)
			malloc(sizeof(png_bytep) * mProperties.GetHeight());
		for (y = 0; y < mProperties.GetHeight(); y++)
			rows[y] = (png_byte*)malloc(numRowBytes);
		// TODO: PNG error handler
		png_read_image(png, rows);
		fclose(file);
		mProperties.SetBitsPerPixel((numRowBytes * 8) / mProperties.GetWidth());
		mPixels.SetElementCount(mProperties.GetHeight() * numRowBytes);
		for (int i = 0; i < mProperties.GetHeight(); i++)
			memcpy(&(mPixels[0]) +
				(numRowBytes * (mProperties.GetHeight()-1-i)),
				rows[i], numRowBytes);
		free(rows);
		png_destroy_read_struct(&png, 0, 0);
		return kErrorNone;
	}
	
	ErrorType Texture2DData::LoadPng(StreamReader *streamReader) {
		ErrorType error;
		Byte *data;
		Long size;
		PngBuffer pngBuffer;
		UByte header[8];
		png_byte bitDepth = 0;
		Int numPasses = 0;
		Int numRowBytes = 0;
		png_byte *row;
		png_structp png = 0;
		png_infop pngInfo = 0;
		size = streamReader->GetSize();
		data = new Byte[(UInt)size];
		streamReader->Read(data, size);
		error = streamReader->GetError();
		if (error) {
			streamReader->Close();
			Unload();
			return Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->Close();
		memcpy(&header[0], &data[0], 8);
		if (!png_check_sig(header, 8))
			return Error::Throw(kErrorImageFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		pngInfo = png_create_info_struct(png);
		pngBuffer.mData = (UByte*)data;
		pngBuffer.mSize = (UInt)size;
		pngBuffer.mIndex = 8;
		png_set_read_fn(png, &pngBuffer, PngStream::Read);
		png_set_sig_bytes(png, 8);
		png_read_info(png, pngInfo);
		mProperties.SetWidth(png_get_image_width(png, pngInfo));
		mProperties.SetHeight(png_get_image_height(png, pngInfo));
		bitDepth = png_get_bit_depth(png, pngInfo);
		numPasses = png_set_interlace_handling(png);
		numRowBytes = png_get_rowbytes(png, pngInfo);
		row = new png_byte[numRowBytes];
		mProperties.SetBitsPerPixel((numRowBytes * 8) / mProperties.GetWidth());
		mPixels.SetElementCount(mProperties.GetWidth() * mProperties.GetHeight() *
			(mProperties.GetBitsPerPixel() / 8));
		for (Int i = 0; i < mProperties.GetHeight(); i++) {
			png_read_row(png, row, 0);
			memcpy(&mPixels[(numRowBytes * mProperties.GetHeight()) -
				(i * numRowBytes) - numRowBytes], row, numRowBytes);
		}
		delete [] row;
		png_destroy_read_struct(&png, 0, 0);
		delete data;
		return kErrorNone;
	}
	
	ErrorType Texture2DData::LoadBmp(const String &fileName) {
		FileReader fr(fileName);
		return LoadBmp(&fr);
	}

	ErrorType Texture2DData::LoadBmp(StreamReader *streamReader) {
		Int offset;
		ErrorType error;
		if (!streamReader->IsOpen()) {
			Unload();
			streamReader->Close();
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->SeekTo(10);
		offset = streamReader->ReadInt();
		streamReader->SeekTo(18);
		mProperties.SetWidth(streamReader->ReadInt());
		mProperties.SetHeight(streamReader->ReadInt());
		streamReader->SeekTo(28);
		mProperties.SetBitsPerPixel((Int)streamReader->ReadShort());
		if (mProperties.GetBitsPerPixel() != 24 &&
			mProperties.GetBitsPerPixel() != 32)
		{
			Unload();
			streamReader->Close();
			return Error::Throw(kErrorImageFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->SeekTo(offset);
		/* Get pixels as BGR(A) */
		mPixels.SetElementCount(mProperties.GetWidth() * mProperties.GetHeight() *
			(mProperties.GetBitsPerPixel() / 8));
		streamReader->Read((Byte*)mPixels.GetData(), mPixels.GetElementCount());
		error = streamReader->GetError();
		if (error) {
			streamReader->Close();
			Unload();
			return Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->Close();
		/* Re-sort bytes from BGR(A) to RGB(A) */
		UByte temp[4];
		for (Int i = 0; i < mPixels.GetElementCount();
			i += (mProperties.GetBitsPerPixel() / 8))
		{
			if (mProperties.GetBitsPerPixel() == 24) {
				temp[0] = mPixels[i];
				temp[1] = mPixels[i + 1];
				temp[2] = mPixels[i + 2];
				mPixels[i + 2] = temp[0];
				mPixels[i + 1] = temp[1];
				mPixels[i + 0] = temp[2];
			} else if (mProperties.GetBitsPerPixel() == 32) {
				temp[0] = mPixels[i];
				temp[1] = mPixels[i + 1];
				temp[2] = mPixels[i + 2];
				temp[3] = mPixels[i + 3];
				mPixels[i + 2] = temp[0];
				mPixels[i + 1] = temp[1];
				mPixels[i + 0] = temp[2];
				mPixels[i + 3] = temp[3];
			}
		}
		return kErrorNone;
	}
	
	ErrorType Texture2DData::LoadJpg(const String &fileName) {
		jpeg_decompress_struct jpg;
		jpeg_error_mgr jpgError;
		FILE *file;
		int numRowBytes;
		UByte **buffer;
#if defined(FastOSWindows)
		_wfopen_s((FILE**)&file, fileName.GetWString().mData, L"rb");
#else
		file = fopen(fileName.GetData(), "rb");
#endif
		if (!file) {
			this->Unload();
			return Error::Throw(kErrorFileNotFound, String("[%s(\"%s\")]",
				FastFunctionName, fileName.GetCString()));
		}
		memset(&jpg, 0, sizeof(jpg));
		jpg.err = jpeg_std_error(&jpgError);
		jpeg_create_decompress(&jpg);
		jpeg_stdio_src(&jpg, file);
		jpeg_read_header(&jpg, true);
		jpeg_start_decompress(&jpg);
		numRowBytes = jpg.output_width * jpg.output_components;
		mProperties.SetBitsPerPixel(jpg.output_components * 8);
		mProperties.SetHeight(jpg.output_height);
		mProperties.SetWidth(jpg.output_width);
		mPixels.SetElementCount(numRowBytes * jpg.output_height);
		buffer = new UByte*;
		buffer[0] = new UByte[numRowBytes];
		while (jpg.output_scanline < jpg.output_height) {
			JDIMENSION read_now = jpeg_read_scanlines(&jpg, buffer, 1);
			memcpy(&this->mPixels[0] +
				((jpg.output_height - jpg.output_scanline) * numRowBytes),
				buffer[0], numRowBytes);
		}
		delete [] buffer[0];
		delete buffer;
		jpeg_finish_decompress(&jpg);
		jpeg_destroy_decompress(&jpg);
		fclose(file);
		return kErrorNone;
	}
	
	ErrorType Texture2DData::LoadJpg(StreamReader *streamReader) {
		ErrorType error;
		Byte *data;
		Long size;
		jpeg_decompress_struct jpg;
		jpeg_error_mgr jpgError;
		int numRowBytes;
		UByte **buffer;
		size = streamReader->GetSize();
		data = new Byte[(UInt)size];
		streamReader->Read(data, size);
		error = streamReader->GetError();
		if (error) {
			streamReader->Close();
			Unload();
			return Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->Close();
		memset(&jpg, 0, sizeof(jpg));
		jpg.err = jpeg_std_error(&jpgError);
		jpeg_create_decompress(&jpg);
		jpeg_mem_src(&jpg, (unsigned char*)data, (unsigned long)size);
		jpeg_read_header(&jpg, true);
		jpeg_start_decompress(&jpg);
		numRowBytes = jpg.output_width * jpg.output_components;
		mProperties.SetBitsPerPixel(jpg.output_components * 8);
		mProperties.SetHeight(jpg.output_height);
		mProperties.SetWidth(jpg.output_width);
		mPixels.SetElementCount(numRowBytes * jpg.output_height);
		buffer = new UByte*;
		buffer[0] = new UByte[numRowBytes];
		while (jpg.output_scanline < jpg.output_height) {
			JDIMENSION read_now = jpeg_read_scanlines(&jpg, buffer, 1);
			memcpy(&this->mPixels[0] +
				((jpg.output_height - jpg.output_scanline) * numRowBytes),
				buffer[0], numRowBytes);
		}
		delete [] buffer[0];
		delete buffer;
		jpeg_finish_decompress(&jpg);
		jpeg_destroy_decompress(&jpg);
		delete data;
		return kErrorNone;
	}

	Texture2DData::Texture2DData() { }

	Texture2DData::Texture2DData(const Texture2DData &that) {
		*this = that;
	}

	Texture2DData::Texture2DData(const Texture2DProperties &properties) {
		mProperties = properties;
		mPixels.SetElementCount(mProperties.GetWidth() *
			mProperties.GetHeight() *
			(mProperties.GetBitsPerPixel() / 8));
	}

	Texture2DData::Texture2DData(const Texture2DProperties &properties,
		const Array<Byte> &pixels)
	{
		SetPixels(properties, pixels);
	}

	Texture2DData::Texture2DData(const String &fileName,
		const SpriteSheet &spriteSheet)
	{
		Load(fileName, spriteSheet);
	}

	Texture2DData::Texture2DData(StreamReader *streamReader,
		const SpriteSheet &spriteSheet)
	{
		Load(streamReader, spriteSheet);
	}

	Texture2DData::Texture2DData(const String &fileName) {
		Load(fileName);
	}

	Texture2DData::Texture2DData(StreamReader *streamReader) {
		Load(streamReader);
	}

	Texture2DData::~Texture2DData() {
		Unload();
	}

	const Array<Byte>& Texture2DData::GetPixels() const {
		return mPixels;
	}

	Int Texture2DData::GetWidth() const {
		return mProperties.GetWidth();
	}

	Int Texture2DData::GetHeight() const {
		return mProperties.GetHeight();
	}

	Int Texture2DData::GetBitsPerPixel() const {
		return mProperties.GetBitsPerPixel();
	}

	const SpriteSheet& Texture2DData::GetSpriteSheet() const {
		return mProperties.GetSpriteSheet();
	}

	const Texture2DProperties& Texture2DData::GetProperties() const {
		return mProperties;
	}

	void Texture2DData::SetPixels(const Texture2DProperties &properties,
		const Array<Byte> &pixels)
	{
		if (pixels.GetElementCount() !=
			properties.GetHeight() * properties.GetWidth() *
			properties.GetBitsPerPixel())
		{
			mPixels = pixels;
			mProperties = properties;
		}
	}

	void Texture2DData::SetWidth(Int width) {
		Int oldWidth = mProperties.GetWidth();
		if (oldWidth != width) {
			Array<Byte> oldPixels = mPixels;
			Int smallerWidth = (width < oldWidth) ? width : oldWidth;
			Int bitsPerPixel = mProperties.GetBitsPerPixel();
			Int height = mProperties.GetHeight();
			mProperties.SetWidth(width);
			mPixels.SetElementCount(width * height * bitsPerPixel);
			for (Int i = 0; i < height; i++)
				for (Int j = 0; j < smallerWidth * bitsPerPixel; j++)
					mPixels[i + (width * j)] = oldPixels[i + (oldWidth * j)];
		}
	}

	void Texture2DData::SetHeight(Int height) {
		Int oldHeight = mProperties.GetHeight();
		if (oldHeight != height) {
			Array<Byte> oldPixels = mPixels;
			Int smallerHeight = (height < oldHeight) ? height : oldHeight;
			Int bitsPerPixel = mProperties.GetBitsPerPixel();
			Int width = mProperties.GetWidth();
			mProperties.SetHeight(height);
			mPixels.SetElementCount(width * height * bitsPerPixel);
			for (Int i = 0; i < smallerHeight; i++)
				for (Int j = 0; j < width * bitsPerPixel; j++)
					mPixels[i + (width * j)] = oldPixels[i + (width * j)];
		}
	}

	void Texture2DData::SetBitsPerPixel(Int bitsPerPixel) {
		Int oldBitsPerPixel = mProperties.GetBitsPerPixel();
		if (bitsPerPixel != oldBitsPerPixel &&
			(24 == bitsPerPixel || 32 == bitsPerPixel))
		{
			Int width = mProperties.GetWidth();
			Int height = mProperties.GetHeight();
			Array<Byte> oldPixels = mPixels;
			mProperties.SetBitsPerPixel(bitsPerPixel);
			mPixels.SetElementCount(width * height * bitsPerPixel);
			for (Int i = 0; i < width * height; i++) {
				if (24 == bitsPerPixel) {
					mPixels[(i * 3) + 1] = oldPixels[(i * 4) + 1];
					mPixels[(i * 3) + 2] = oldPixels[(i * 4) + 2];
					mPixels[(i * 3) + 3] = oldPixels[(i * 4) + 3];
				} else {
					mPixels[(i * 4) + 1] = oldPixels[(i * 3) + 1];
					mPixels[(i * 4) + 2] = oldPixels[(i * 3) + 2];
					mPixels[(i * 4) + 3] = oldPixels[(i * 3) + 3];
					mPixels[(i * 4) + 4] = (Byte)255;
				}
			}
		}
	}

	void Texture2DData::SetSize(Int width, Int height, Int bitsPerPixel) {
		Int oldWidth = mProperties.GetWidth();
		Int oldHeight = mProperties.GetHeight();
		Int oldBitsPerPixel = mProperties.GetBitsPerPixel();
		if (bitsPerPixel == oldBitsPerPixel) {
			if (width == oldWidth) {
				if (height == oldHeight)
					return;
				else return SetHeight(height);
			} else return SetWidth(width);
		} else if (width == oldWidth && height == oldHeight) {
			return SetBitsPerPixel(bitsPerPixel);
		} else {
			Array<Byte> oldPixels = mPixels;
			mProperties.SetWidth(width);
			mProperties.SetHeight(height);
			mProperties.SetBitsPerPixel(bitsPerPixel);
			mPixels.SetElementCount(width * height * bitsPerPixel, (Byte)255);
			Int offset24, offset32;
			for (Int i = 0; i < height && i < oldHeight; i++) {
				for (Int j = 0; j < width && j < oldWidth; j++) {
					offset24 = (width * j) + (i * 3);
					offset32 = (width * j) + (i * 4);
					if (24 == bitsPerPixel) {
						mPixels[offset24 + 0] = oldPixels[offset32 + 0];
						mPixels[offset24 + 1] = oldPixels[offset32 + 1];
						mPixels[offset24 + 2] = oldPixels[offset32 + 2];
					} else {
						mPixels[offset32 + 0] = oldPixels[offset24 + 0];
						mPixels[offset32 + 1] = oldPixels[offset24 + 1];
						mPixels[offset32 + 2] = oldPixels[offset24 + 2];
						mPixels[offset32 + 3] = (Byte)255;
					}
				}
			}
		}
	}

	void Texture2DData::SetSpriteSheet(const SpriteSheet &spriteSheet) {
		mProperties.SetSpriteSheet(spriteSheet);
	}

	void Texture2DData::SetProperties(const Texture2DProperties &properties) {
		SetSize(properties.GetWidth(), properties.GetHeight(),
			properties.GetBitsPerPixel());
		mProperties = properties;
	}

	ErrorType Texture2DData::Load(const String &fileName,
		const SpriteSheet &spriteSheet)
	{
		Unload();
		ErrorType e;
		FileReader file(fileName);
		if (!file.IsOpen())
			return Error::Throw(kErrorFileNotFound,
				String("[%s(\"%s\", %p): spriteSheet.mName=\"%s\"]",
				FastFunctionName, fileName.GetCString(), &spriteSheet,
				spriteSheet.GetName().GetCString()));
		mName = fileName;
		Char check = file.ReadByte();
		file.Close();
		switch(check)
		{
		case '\x42':
			e = LoadBmp(fileName);
			break;
		case '\xff':
			e = LoadJpg(fileName);
			break;
		case '\x89':
			e = LoadPng(fileName);
			break;
		default:
			e = kErrorImageFormatInvalid;
		}
		if (e) {
			Unload();
			return Error::Throw(e,
				String("[%s(\"%s\", %p): spriteSheet.mName=\"%s\"]",
				FastFunctionName, fileName.GetCString(), &spriteSheet,
				spriteSheet.GetName().GetCString()));
		}
		SetSpriteSheet(spriteSheet);
		return kErrorNone;
	}

	ErrorType Texture2DData::Load(StreamReader *streamReader,
		const SpriteSheet &spriteSheet)
	{
		Unload();
		ErrorType e;
		if (!streamReader->IsOpen())
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p, %p): streamReader->mName=\"%s\" spriteSheet.mName=\"%s\"]",
				FastFunctionName, streamReader, &spriteSheet,
				streamReader->GetName().GetCString(),
				spriteSheet.GetName().GetCString()));
		mName = streamReader->GetName();
		streamReader->SeekTo(0);
		Char check = streamReader->ReadByte();
		streamReader->SeekTo(0);
		switch(check)
		{
		case '\x42':
			e = LoadBmp(streamReader);
			break;
		case '\xff':
			e = LoadJpg(streamReader);
			break;
		case '\x89':
			e = LoadPng(streamReader);
			break;
		default:
			e = kErrorImageFormatInvalid;
		}
		if (e) {
			Unload();
			return Error::Throw(e,
				String("[%s(%p, %p): streamReader->mName=\"%s\" spriteSheet.mName=\"%s\"]",
				FastFunctionName, streamReader, &spriteSheet,
				streamReader->GetName().GetCString(),
				spriteSheet.GetName().GetCString()));
		}
		SetSpriteSheet(spriteSheet);
		return kErrorNone;
	}

	ErrorType Texture2DData::Load(const String &fileName) {
		return Load(fileName, SpriteSheet());
	}

	ErrorType Texture2DData::Load(StreamReader *streamReader) {
		return Load(streamReader, SpriteSheet());
	}

	void Texture2DData::Unload() {
		mProperties = Texture2DProperties();
		mPixels.Clear();
		mName.Clear();
	}
	/*
	// These functions have been replaced by SetBitsPerPixel() and SetSize()
	//	We'll keep them around for now for reference just in case.

	ErrorType Texture2DData::ConvertToRgb() {
		Texture2DData imageData = *this;
		return ConvertToRgb(imageData, this);
	}

	Texture2DData Texture2DData::ConvertToRgb(const Texture2DData &imageData) {
		Texture2DData newimg;
		ConvertToRgb(imageData, &newimg);
		return newimg;
	}

	ErrorType Texture2DData::ConvertToRgb(
		const Texture2DData &imageData, Texture2DData *result)
	{
		if (imageData.mProperties.GetBitsPerPixel() == 24) {
			*result = imageData;
			return kErrorNone;
		} else if (imageData.mProperties.GetBitsPerPixel() != 32 ||
			imageData.mPixels.GetElementCount() == 0)
		{
			*result = imageData;
			return Error::Throw(kErrorImageFormatInvalid,
				String("[%s(%p, %p): imageData.mName=\"%s\"]",
				FastFunctionName, &imageData, result,
				imageData.GetName().GetCString()));
		}
		result->mName = imageData.mName;
		result->mProperties.SetBitsPerPixel(24);
		result->mProperties.SetWidth(imageData.mProperties.GetWidth());
		result->mProperties.SetHeight(imageData.mProperties.GetHeight());
		result->mPixels.SetElementCount(result->mProperties.GetWidth() *
			result->mProperties.GetHeight() *
			(result->mProperties.GetBitsPerPixel() / 8));
		for (Int i = 0;
			i < (result->mProperties.GetWidth() *
				result->mProperties.GetHeight());
			i++)
		{
			result->mPixels[3*i]	= imageData.mPixels[4*i];
			result->mPixels[3*i+1]	= imageData.mPixels[4*i+1];
			result->mPixels[3*i+2]	= imageData.mPixels[4*i+2];
		}
		return kErrorNone;
	}

	ErrorType Texture2DData::ConvertToRgba() {
		Texture2DData imageData = *this;
		return ConvertToRgba(imageData, this);
	}

	Texture2DData Texture2DData::ConvertToRgba(const Texture2DData &imageData) {
		Texture2DData newimg;
		ConvertToRgba(imageData, &newimg);
		return newimg;
	}

	ErrorType Texture2DData::ConvertToRgba(
		const Texture2DData &imageData, Texture2DData *result)
	{
		if (imageData.mProperties.GetBitsPerPixel() == 32) {
			*result = imageData;
			return kErrorNone;
		} else if (imageData.mProperties.GetBitsPerPixel() != 24 ||
			imageData.mPixels.GetElementCount() == 0)
		{
			*result = imageData;
			return Error::Throw(kErrorImageFormatInvalid,
				String("[%s(%p, %p): imageData.mName=\"%s\"]",
				FastFunctionName, &imageData, result,
				imageData.GetName().GetCString()));
		}
		result->mName = imageData.mName;
		result->mProperties.SetBitsPerPixel(32);
		result->mProperties.SetWidth(imageData.mProperties.GetWidth());
		result->mProperties.SetHeight(imageData.mProperties.GetHeight());
		result->mPixels.SetElementCount(result->mProperties.GetWidth() *
			result->mProperties.GetHeight() *
			(result->mProperties.GetBitsPerPixel() / 8));
		for (Int i = 0;
			i < (result->mProperties.GetWidth() *
				result->mProperties.GetHeight());
			i++)
		{
			result->mPixels[4*i]	= imageData.mPixels[3*i];
			result->mPixels[4*i+1]	= imageData.mPixels[3*i+1];
			result->mPixels[4*i+2]	= imageData.mPixels[3*i+2];
			result->mPixels[4*i+3]	= (Byte)255;
		}
		return kErrorNone;
	}
	*/
	ErrorType Texture2DData::SaveAsPng(const String &fileName) {
		png_structp png;
		png_infop pngInfo;
		FILE *file;
#if defined(FastOSWindows)
		_wfopen_s((FILE**)&file, fileName.GetWString().mData, L"wb");
#else
		file = fopen(fileName.GetData(), "wb");
#endif
		if (!file)
			return Error::Throw(kErrorFileCreationFailure, String(
				"[%s(\"%s\")]", FastFunctionName, fileName.GetCString()));
		png = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
		if (!png) {
			fclose(file);
			return Error::Throw(kErrorPngCreationFailure, String(
				"[%s(\"%s\")]", FastFunctionName, fileName.GetCString()));
		}
		pngInfo = png_create_info_struct(png);
		if (!pngInfo) {
			fclose(file);
			png_destroy_write_struct(&png, &pngInfo);
			return Error::Throw(kErrorPngCreationFailure, String(
				"[%s(\"%s\")]", FastFunctionName, fileName.GetCString()));
		}
		png_init_io(png, file);
		if (mProperties.GetBitsPerPixel() == 24)
			png_set_IHDR(png, pngInfo, mProperties.GetWidth(),
				mProperties.GetHeight(), 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
		else if (mProperties.GetBitsPerPixel() == 32)
			png_set_IHDR(png, pngInfo, mProperties.GetWidth(),
				mProperties.GetHeight(), 8, PNG_COLOR_TYPE_RGB_ALPHA,
				PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
				PNG_FILTER_TYPE_DEFAULT);
		else {
			fclose(file);
			png_destroy_info_struct(png, &pngInfo);
			png_destroy_write_struct(&png, &pngInfo);
			return Error::Throw(kErrorImageFormatInvalid, String(
				"[%s(\"%s\")]", FastFunctionName, fileName.GetCString()));
		}
		png_write_info(png, pngInfo);
		setjmp(png_jmpbuf(png));
		for (Int i = 0; i < mProperties.GetHeight(); i++)
			png_write_row(png,
				(UByte*)&mPixels[
				(mProperties.GetHeight()-1-i) * mProperties.GetWidth() *
				(mProperties.GetBitsPerPixel()/8)]);
		png_write_end(png, pngInfo);
		png_destroy_info_struct(png, &pngInfo);
		png_destroy_write_struct(&png, &pngInfo);
		fclose(file);
		return kErrorNone;
	}

	ErrorType Texture2DData::SaveAsBmp(const String &fileName) {
		if ((mProperties.GetBitsPerPixel() != 24 &&
			mProperties.GetBitsPerPixel() != 32) || mPixels.GetElementCount() == 0)
		{
			return Error::Throw(kErrorImageFormatInvalid, String(
				"[%s(\"%s\")]", FastFunctionName, fileName.GetCString()));
		}
		FileWriter file(fileName);
		file.Write((Byte*)"BM", 2);						// Sig
		file.WriteInt((mProperties.GetWidth() *			// Size
			mProperties.GetHeight() *
			(mProperties.GetBitsPerPixel() / 8)) + 54);
		file.WriteShort(0);								// Reserved1
		file.WriteShort(0);								// Reserved2
		file.WriteInt(54);								// Offset
		file.WriteInt(40);								// HeaderSize
		file.WriteInt(mProperties.GetWidth());			// Width
		file.WriteInt(mProperties.GetHeight());			// Height
		file.WriteShort(1);								// NumPlanes
		file.WriteShort(mProperties.GetBitsPerPixel());	// BitsPerPixel
		file.WriteInt(0);								// CompressionType
		file.WriteInt(mProperties.GetHeight() *			// ImageSize
			mProperties.GetWidth() *
			(mProperties.GetBitsPerPixel() / 8));
		file.WriteInt(0);								// HResolution
		file.WriteInt(0);								// VResolution
		file.WriteInt(0);								// NumColors
		file.WriteInt(0);								// NumImportantColors
		for (Int i = 0;
			i < (mProperties.GetWidth() * mProperties.GetHeight()); i++)
		{
			if (mProperties.GetBitsPerPixel() == 24) {
				file.WriteByte(mPixels[3*i+2]);
				file.WriteByte(mPixels[3*i+1]);
				file.WriteByte(mPixels[3*i]);
			} else if (mProperties.GetBitsPerPixel() == 32) {
				file.WriteByte(mPixels[4*i+2]);
				file.WriteByte(mPixels[4*i+1]);
				file.WriteByte(mPixels[4*i]);
				file.WriteByte(mPixels[4*i+3]);
			}
		}
		file.Close();
		return kErrorNone;
	}

	ErrorType Texture2DData::SaveAsJpg(
		const String &fileName, UByte quality)
	{
		if (mProperties.GetBitsPerPixel() != 24)
			return Error::Throw(kErrorImageFormatInvalid, String(
				"[%s(\"%s\", %hhu)]", FastFunctionName,
				fileName.GetCString(), quality));
		jpeg_compress_struct jpg;
		jpeg_error_mgr jpgError;
		FILE *file;
		int numRowBytes;
		UByte **buffer;
#if defined(FastOSWindows)
		_wfopen_s((FILE**)&file, fileName.GetWString().mData, L"wb");
#else
		file = fopen(fileName.GetData(), "wb");
#endif
		if (!file)
			return Error::Throw(kErrorFileCreationFailure, String(
				"[%s(\"%s\", %hhu)]", FastFunctionName,
				fileName.GetCString(), quality));
		memset(&jpg, 0, sizeof(jpg));
		jpg.err = jpeg_std_error(&jpgError);
		jpeg_create_compress(&jpg);
		jpeg_stdio_dest(&jpg, file);
		jpg.image_width = mProperties.GetWidth();
		jpg.image_height = mProperties.GetHeight();
		jpg.input_components = mProperties.GetBitsPerPixel() / 8;
		jpg.in_color_space = JCS_RGB;
		numRowBytes = jpg.image_width * jpg.input_components;
		buffer = new UByte*;
		buffer[0] = new UByte[numRowBytes];
		jpeg_set_defaults(&jpg);
		jpeg_set_quality(&jpg, quality, true);
		jpeg_start_compress(&jpg, 1);
		while (jpg.next_scanline < jpg.image_height) {
			memcpy(buffer[0], &mPixels[0] +
				((jpg.image_height - jpg.next_scanline - 1) * numRowBytes),
				numRowBytes);
			jpeg_write_scanlines(&jpg, &buffer[0], 1);
		}
		delete [] buffer[0];
		delete buffer;
		jpeg_finish_compress(&jpg);
		jpeg_destroy_compress(&jpg);
		fclose(file);
		return kErrorNone;
	}

	Texture2DData& Texture2DData::operator=(const Texture2DData &that) {
		this->Unload();
		this->mProperties.SetBitsPerPixel(that.mProperties.GetBitsPerPixel());
		this->mProperties.SetHeight(that.mProperties.GetHeight());
		this->mProperties.SetWidth(that.mProperties.GetWidth());
		this->mPixels = that.mPixels;
		return *this;
	}

	Bool Texture2DData::operator==(const Texture2DData &that) const {
		return (this->mProperties.GetHeight() == that.mProperties.GetHeight() &&
			this->mProperties.GetWidth() == that.mProperties.GetWidth() &&
			this->mProperties.GetBitsPerPixel() ==
				that.mProperties.GetBitsPerPixel() &&
			!memcmp(this->mPixels.GetData(), that.mPixels.GetData(),
				(this->mPixels.GetElementCount() >
					that.mPixels.GetElementCount()) ?
				this->mPixels.GetElementCount() :
				that.mPixels.GetElementCount()));
	}

	Bool Texture2DData::operator!=(const Texture2DData &that) const {
		return (this->mProperties.GetHeight() != that.mProperties.GetHeight() ||
			this->mProperties.GetWidth() != that.mProperties.GetWidth() ||
			this->mProperties.GetBitsPerPixel() !=
				that.mProperties.GetBitsPerPixel() ||
			memcmp(this->mPixels.GetData(), that.mPixels.GetData(),
				(this->mPixels.GetElementCount() >
					that.mPixels.GetElementCount()) ?
				this->mPixels.GetElementCount() :
				that.mPixels.GetElementCount()));
	}
}
