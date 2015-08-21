/******************************************************************************/
/*                                                                            */
/*  FTFontTexture2DFont.hpp                                                  */
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

#ifndef FastFTFontTexture2DFontHppIncluded
#define FastFTFontTexture2DFontHppIncluded

#include <Fast/Types.hpp>
#include <FTGL/ftgl.h>
#include <FTGlyph/FTGlyphImpl.h>
#include <Fast/Array.hpp>
#include <FTFont/FTFontImpl.h>

namespace Fast
{
	class GraphicsContext;
	class AlphaTexture2DData;
	class FrameBufferSurface;

	class FTFontTexture2DGlyph : public FTGlyph
	{
	private:
		GraphicsContext	*mGraphicsContext;
	public:
		FTFont	*mFTFont;
		FTFontTexture2DGlyph(FT_GlyphSlot glyph, UInt glID,
			int offsetX, int offsetY, int width, int height,
			GraphicsContext *graphicsContext);
		virtual ~FTFontTexture2DGlyph();
		virtual const FTPoint&	Render(const FTPoint& pen, int renderMode);
	};

	class FTFontTexture2DFontImpl;

	class FTFontTexture2DGlyphImpl : public FTGlyphImpl
	{
	private:
		friend class FTFontTexture2DGlyph;
		friend class FTFontTexture2DFontImpl;
	protected:
		FrameBufferSurface	*mFrameBufferSurface;
		FTFontTexture2DGlyphImpl(FT_GlyphSlot glyph, UInt glID,
			int offsetX, int offsetY, int width, int height,
			GraphicsContext *graphicsContext);
		virtual ~FTFontTexture2DGlyphImpl();
		virtual const FTPoint& RenderImpl(const FTPoint& pen, int renderMode);
	private:
		GraphicsContext	*mGraphicsContext;
		int				mDestWidth;
		int				mDestHeight;
		FTPoint			mCorner;
		FTPoint			mUV[2];
		UInt			mOpenGLAlphaTexture2DID;
	};

	class FTFontTexture2DFont : public FTFont
	{
	private:
		GraphicsContext	*mGraphicsContext;
	public:
		FrameBufferSurface	*mFrameBufferSurface;
		FTFontTexture2DFont(const char *filePath,
			GraphicsContext *graphicsContext);
		FTFontTexture2DFont(const unsigned char *buffer,
			size_t bufferByteCount, GraphicsContext *graphicsContext);
		virtual ~FTFontTexture2DFont();
		FTPoint RenderWithFrameBufferSurface(const char* string,
			FrameBufferSurface *frameBufferSurface,
			const int len = -1,
			FTPoint position = FTPoint(),
			FTPoint spacing = FTPoint(),
			int renderMode = FTGL::RENDER_ALL);
		FTPoint RenderWithFrameBufferSurface(const wchar_t *string,
			FrameBufferSurface *frameBufferSurface,
			const int len = -1,
			FTPoint position = FTPoint(),
			FTPoint spacing = FTPoint(),
			int renderMode = FTGL::RENDER_ALL);
	protected:
		virtual FTGlyph* MakeGlyph(FT_GlyphSlot slot);
	};

	class FTFontTexture2DFontImpl : public FTFontImpl
	{
	private:
		friend class FTFontTexture2DFont;
		// Private members
		GraphicsContext		*mGraphicsContext;
		Int					mMaximumGLTextureSize;
		Int					mTextureWidth;
		Int					mTextureHeight;
		Array<UInt>			mOpenGLAlphaTexture2DIDArray;
		Int					mGlyphHeight;
		Int					mGlyphWidth;
		Int					mPadding;
		Int					mGlyphCount;
		Int					mRemGlyphs;
		Int					mOffsetX;
		Int					mOffsetY;
		// Private methods
		FTGlyph*	MakeGlyphImpl(FT_GlyphSlot ftGlyph);
		void		CalculateTextureSize();
		UInt		CreateTexture();
		template <typename T>
		inline FTPoint RenderI(const T *s, const int len, FTPoint position,
			FTPoint spacing, int mode);
		friend class FTFontTexture2DFont;
	protected:
		// (Con/De)structors
		FTFontTexture2DFontImpl(FTFont *ftFont, const char *filePath,
			GraphicsContext *graphicsContext);
		FTFontTexture2DFontImpl(FTFont *ftFont, const unsigned char *buffer,
			size_t bufferByteCount, GraphicsContext *graphicsContext);
		virtual ~FTFontTexture2DFontImpl();
		// Etc.
		virtual bool	FaceSize(const unsigned int size,
			const unsigned int res = 72);
		virtual FTPoint	Render(const char *s, const int len, FTPoint position,
							FTPoint spacing, int renderMode);
		virtual FTPoint	Render(const wchar_t *s, const int len,
							FTPoint position, FTPoint spacing, int renderMode);
	};
}

#endif // FastFTFontTexture2DFontHppIncluded