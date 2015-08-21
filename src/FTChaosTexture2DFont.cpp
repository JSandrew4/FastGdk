/******************************************************************************/
/*                                                                            */
/*  FTFontTexture2DFont.cpp                                                  */
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

#include "FTFontTexture2DFont.hpp"

#include <Fast/GraphicsContext.hpp>
#include <Fast/AlphaTexture2DData.hpp>
#include <Fast/RenderItem.hpp>

#include <cmath>

#include "Undefs.hpp"

namespace Fast
{
	FTFontTexture2DGlyph::FTFontTexture2DGlyph(FT_GlyphSlot glyph,
		UInt glID, int offsetX, int offsetY, int width, int height,
		GraphicsContext *graphicsContext) :
		FTGlyph(new FTFontTexture2DGlyphImpl(
			glyph, glID, offsetX, offsetY, width, height,
			graphicsContext))
	{}

	FTFontTexture2DGlyph::~FTFontTexture2DGlyph() { }

	const FTPoint& FTFontTexture2DGlyph::Render(
		const FTPoint& pen, int renderMode)
	{
		FTFontTexture2DGlyphImpl *myimpl =
			dynamic_cast<FTFontTexture2DGlyphImpl *>(impl);
		myimpl->mFrameBufferSurface = ((FTFontTexture2DFont*)mFTFont)->mFrameBufferSurface;
		return myimpl->RenderImpl(pen, renderMode);
	}
	
	FTFontTexture2DGlyphImpl::FTFontTexture2DGlyphImpl(FT_GlyphSlot glyph,
		UInt glID, int offsetX, int offsetY, int width, int height,
		GraphicsContext *graphicsContext)
		: FTGlyphImpl(glyph),
		mGraphicsContext(graphicsContext),
		mDestWidth(0),
		mDestHeight(0),
		mOpenGLAlphaTexture2DID(glID)
	{
		err = FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);
		if (err || glyph->format != ft_glyph_format_bitmap)
			return;
		FT_Bitmap bitmap = glyph->bitmap;
		mDestWidth = bitmap.width;
		mDestHeight = bitmap.rows;
		if (mDestWidth && mDestHeight) {
			mGraphicsContext->StoreAlphaTexture2DData(
				mOpenGLAlphaTexture2DID, AlphaTexture2DData(
					mDestWidth, mDestHeight, Array<Byte>(
						(Byte*)bitmap.buffer, mDestWidth * mDestHeight)),
				offsetX, offsetY);
		}

		mUV[0].X(static_cast<float>(offsetX) / static_cast<float>(width));
		mUV[0].Y(static_cast<float>(offsetY) / static_cast<float>(height));
		mUV[1].X(static_cast<float>(offsetX + mDestWidth) /
			static_cast<float>(width));
		mUV[1].Y(static_cast<float>(offsetY + mDestHeight) /
			static_cast<float>(height));
		mCorner = FTPoint(glyph->bitmap_left, glyph->bitmap_top);
	}

	FTFontTexture2DGlyphImpl::~FTFontTexture2DGlyphImpl() { }

	const FTPoint& FTFontTexture2DGlyphImpl::RenderImpl(
		const FTPoint& pen, int renderMode)
	{
		RenderItem ri(mFrameBufferSurface);
		// TODO: Set render preferences
		mGraphicsContext->QueueRenderItem(ri);
		return advance;
	}

	FTFontTexture2DFont::FTFontTexture2DFont(const char *filePath,
		GraphicsContext *graphicsContext) :
		FTFont(new FTFontTexture2DFontImpl(this, filePath, graphicsContext)),
		mGraphicsContext(graphicsContext)
	{ }

	FTFontTexture2DFont::FTFontTexture2DFont(
		const unsigned char *buffer, size_t bufferByteCount,
		GraphicsContext *graphicsContext) :
		FTFont(new FTFontTexture2DFontImpl(this, buffer, bufferByteCount,
			graphicsContext)),
		mGraphicsContext(graphicsContext)
	{ }

	FTFontTexture2DFont::~FTFontTexture2DFont() { }

	FTGlyph* FTFontTexture2DFont::MakeGlyph(FT_GlyphSlot ftGlyph) {
		if (impl) {
			FTGlyph *g =
				((FTFontTexture2DFontImpl*)impl)->MakeGlyphImpl(ftGlyph);
			((FTFontTexture2DGlyph*)g)->mFTFont = this;
			return g;
		}
		return NULL;
	}

	FTPoint FTFontTexture2DFont::RenderWithFrameBufferSurface(
		const char* string, FrameBufferSurface *frameBufferSurface,
		const int len, FTPoint position, FTPoint spacing, int renderMode)
	{
		mFrameBufferSurface = frameBufferSurface;
		return Render(string, len, position, spacing, renderMode);
	}

	FTPoint FTFontTexture2DFont::RenderWithFrameBufferSurface(
		const wchar_t *string, FrameBufferSurface *frameBufferSurface,
		const int len, FTPoint position, FTPoint spacing, int renderMode)
	{
		mFrameBufferSurface = frameBufferSurface;
		return Render(string, len, position, spacing, renderMode);
	}

	static inline UInt NextPowerOf2(UInt in) {
		in -= 1;
		in |= in >> 16;
		in |= in >> 8;
		in |= in >> 4;
		in |= in >> 2;
		in |= in >> 1;
		return in + 1;
	}

	FTFontTexture2DFontImpl::FTFontTexture2DFontImpl(
		FTFont *ftFont, const char *filePath, GraphicsContext *graphicsContext) :
		FTFontImpl(ftFont, filePath),
		mMaximumGLTextureSize(0),
		mTextureWidth(0),
		mTextureHeight(0),
		mGlyphHeight(0),
		mGlyphWidth(0),
		mPadding(3),
		mOffsetX(0),
		mOffsetY(0),
		mGraphicsContext(graphicsContext)
	{
		load_flags = FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP;
		mRemGlyphs = mGlyphCount = face.GlyphCount();
	}

	FTFontTexture2DFontImpl::FTFontTexture2DFontImpl(FTFont *ftFont,
		const unsigned char *buffer, size_t bufferByteCount,
		GraphicsContext *graphicsContext) :
		FTFontImpl(ftFont, buffer, bufferByteCount),
		mMaximumGLTextureSize(0),
		mTextureWidth(0),
		mTextureHeight(0),
		mGlyphHeight(0),
		mGlyphWidth(0),
		mPadding(3),
		mOffsetX(0),
		mOffsetY(0),
		mGraphicsContext(graphicsContext)
	{
		load_flags = FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP;
		mRemGlyphs = mGlyphCount = face.GlyphCount();
	}

	FTFontTexture2DFontImpl::~FTFontTexture2DFontImpl() {
		for (Int i = 0; i < mOpenGLAlphaTexture2DIDArray.GetElementCount(); i++)
			mGraphicsContext->DeleteOpenGLTexture2DID(
				mOpenGLAlphaTexture2DIDArray[i]);
	}

	FTGlyph* FTFontTexture2DFontImpl::MakeGlyphImpl(FT_GlyphSlot ftGlyph) {
		mGlyphHeight = static_cast<Int>(charSize.Height() + 0.5);
		mGlyphWidth = static_cast<Int>(charSize.Width() + 0.5);
		if (mGlyphHeight < 1)
			mGlyphHeight = 1;
		if (mGlyphWidth < 1)
			mGlyphWidth = 1;
		if (mOpenGLAlphaTexture2DIDArray.IsEmpty()) {
			mOpenGLAlphaTexture2DIDArray.Append(CreateTexture());
			mOffsetX = mOffsetY = mPadding;
		}
		if (mOffsetX > (mTextureWidth - mGlyphWidth)) {
			mOffsetX = mPadding;
			mOffsetY += mGlyphHeight;
			if (mOffsetY > (mTextureHeight - mGlyphHeight)) {
				mOpenGLAlphaTexture2DIDArray.Append(CreateTexture());
				mOffsetY = mPadding;
			}
		}
		FTFontTexture2DGlyph *tempGlyph = new FTFontTexture2DGlyph(
			ftGlyph, mOpenGLAlphaTexture2DIDArray[
				mOpenGLAlphaTexture2DIDArray.GetElementCount()-1],
			mOffsetX, mOffsetY, mTextureWidth,
			mTextureHeight, mGraphicsContext);
		mOffsetX += static_cast<Int>(tempGlyph->BBox().Upper().X() -
			tempGlyph->BBox().Lower().X() + mPadding + 0.5);
		--mRemGlyphs;
		return tempGlyph;
	}

	void FTFontTexture2DFontImpl::CalculateTextureSize() {
		if (!mMaximumGLTextureSize)
			mMaximumGLTextureSize =
				mGraphicsContext->GetCapabilities().GetMaxTexture2DSize();
		mTextureWidth = NextPowerOf2(
			(mRemGlyphs * mGlyphWidth) + (mPadding * 2));
		mTextureWidth = mTextureWidth > mMaximumGLTextureSize ?
			mMaximumGLTextureSize : mTextureWidth;
		Int h = static_cast<Int>((mTextureWidth - (mPadding * 2)) /
			mGlyphWidth + 0.5);
		mTextureHeight = NextPowerOf2(((mGlyphCount / h) + 1) * mGlyphHeight);
		mTextureHeight = mTextureHeight > mMaximumGLTextureSize ?
			mMaximumGLTextureSize : mTextureHeight;
	}

	UInt FTFontTexture2DFontImpl::CreateTexture() {
		CalculateTextureSize();
		AlphaTexture2DData alphaTexture2DData(mTextureWidth, mTextureHeight);
		UInt openGLAlphaTexture2DID =
			mGraphicsContext->GenerateNewOpenGLTexture2DID();
		mGraphicsContext->StoreAlphaTexture2DData(openGLAlphaTexture2DID,
			alphaTexture2DData, mOffsetX, mOffsetY);
		return openGLAlphaTexture2DID;
	}

	Bool FTFontTexture2DFontImpl::FaceSize(const UInt size, const UInt res) {
		for (Int i = 0; i < mOpenGLAlphaTexture2DIDArray.GetElementCount(); i++)
			mGraphicsContext->DeleteOpenGLTexture2DID(
				mOpenGLAlphaTexture2DIDArray[i]);
		mOpenGLAlphaTexture2DIDArray.Clear();
		mRemGlyphs = mGlyphCount = face.GlyphCount();
		return FTFontImpl::FaceSize(size, res);
	}

	template <typename T> inline FTPoint FTFontTexture2DFontImpl::RenderI(
		const T* string, const Int len, FTPoint position,
		FTPoint spacing, int renderMode)
	{
		return FTFontImpl::Render(string, len, position, spacing, renderMode);
	}

	FTPoint FTFontTexture2DFontImpl::Render(const char *string, const int len,
		FTPoint position, FTPoint spacing, int renderMode)
	{
		return RenderI(string, len, position, spacing, renderMode);
	}

	FTPoint FTFontTexture2DFontImpl::Render(const wchar_t * string,
		const int len, FTPoint position, FTPoint spacing, int renderMode)
	{
		return RenderI(string, len, position, spacing, renderMode);
	}
}