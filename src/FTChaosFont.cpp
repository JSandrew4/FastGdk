/******************************************************************************/
/*                                                                            */
/*  FTFontFont.cpp                                                           */
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

#include "FTFontFont.hpp"

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	FTFontGlyph::FTFontGlyph(FT_GlyphSlot glyph, int offsetX,
		int offsetY, int width, int height) :
		FTGlyph(new FTFontGlyphImpl(glyph, offsetX, offsetY, width, height))
	{}

	FTFontGlyph::~FTFontGlyph() { }

	const FTPoint& FTFontGlyph::Render(const FTPoint& pen, int renderMode) {
		FTFontGlyphImpl *myimpl = dynamic_cast<FTFontGlyphImpl *>(impl);
		return myimpl->RenderImpl(pen, renderMode);
	}

	FTFontGlyphImpl::FTFontGlyphImpl(FT_GlyphSlot glyph, int offsetX,
		int offsetY, int width, int height)
		: FTGlyphImpl(glyph),
		mDestWidth(0),
		mDestHeight(0)
	{ }

	FTFontGlyphImpl::~FTFontGlyphImpl() { }

	const FTPoint& FTFontGlyphImpl::RenderImpl(
		const FTPoint& pen, int renderMode)
	{
		return pen;
	}

	FTFontFont::FTFontFont(const char *filePath) :
		FTFont(new FTFontFontImpl(this, filePath))
	{ }

	FTFontFont::FTFontFont(const unsigned char *buffer, size_t bufferByteCount) :
		FTFont(new FTFontFontImpl(this, buffer, bufferByteCount))
	{ }

	FTFontFont::~FTFontFont() { }

	Int FTFontFont::GetGlyphCount() const {
		return ((FTFontFontImpl*)impl)->GetGlyphCount();
	}

	FTGlyph* FTFontFont::MakeGlyph(FT_GlyphSlot ftGlyph) {
		if (impl)
			return ((FTFontFontImpl*)impl)->MakeGlyphImpl(ftGlyph);
		return NULL;
	}

	FTFontFontImpl::FTFontFontImpl(FTFont *ftFont, const char *filePath) :
		FTFontImpl(ftFont, filePath)
	{
		load_flags = FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP;
	}

	FTFontFontImpl::FTFontFontImpl(FTFont *ftFont,
		const unsigned char *buffer, size_t bufferByteCount) :
		FTFontImpl(ftFont, buffer, bufferByteCount)
	{
		load_flags = FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP;
	}

	FTFontFontImpl::~FTFontFontImpl() { }

	FTGlyph* FTFontFontImpl::MakeGlyphImpl(FT_GlyphSlot ftGlyph) {
		FTFontGlyph* tempGlyph = NULL;
		return tempGlyph;
	}

	Bool FTFontFontImpl::FaceSize(const UInt size, const UInt res) {
		return FTFontImpl::FaceSize(size, res);
	}

	Int FTFontFontImpl::GetGlyphCount() const {
		return face.GlyphCount();
	}

	template <typename T> inline FTPoint FTFontFontImpl::RenderI(
		const T* string, const Int len, FTPoint position,
		FTPoint spacing, int renderMode)
	{
		return FTPoint();
	}

	FTPoint FTFontFontImpl::Render(const char *string, const int len,
		FTPoint position, FTPoint spacing, int renderMode)
	{
		return RenderI(string, len, position, spacing, renderMode);
	}

	FTPoint FTFontFontImpl::Render(const wchar_t * string, const int len,
		FTPoint position, FTPoint spacing, int renderMode)
	{
		return RenderI(string, len, position, spacing, renderMode);
	}
}