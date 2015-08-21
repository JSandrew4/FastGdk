/******************************************************************************/
/*                                                                            */
/*  FTFontFont.hpp                                                           */
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

#ifndef FastFTFontFontHppIncluded
#define FastFTFontFontHppIncluded

#include <Fast/Types.hpp>
#include <FTGL/ftgl.h>
#include <FTGlyph/FTGlyphImpl.h>
#include <Fast/Array.hpp>
#include <FTFont/FTFontImpl.h>

namespace Fast
{
	class FTFontGlyph : public FTGlyph
	{
	public:
		FTFontGlyph(FT_GlyphSlot glyph, int offsetX, int offsetY, int width, int height);
		virtual ~FTFontGlyph();
		virtual const FTPoint&	Render(const FTPoint& pen, int renderMode);
	};

	class FTFontFontImpl;

	class FTFontGlyphImpl : public FTGlyphImpl
	{
		friend class FTFontGlyph;
		friend class FTFontFontImpl;
	protected:
		FTFontGlyphImpl(FT_GlyphSlot glyph, int offsetX,
			int offsetY, int width, int height);
		virtual ~FTFontGlyphImpl();
		virtual const FTPoint& RenderImpl(const FTPoint& pen, int renderMode);
	private:
		int mDestWidth;
		int mDestHeight;
		FTPoint mCorner;
		FTPoint mUV[2];
	};

	class FTFontFont : public FTFont
	{
	public:
		FTFontFont(const char *filePath);
		FTFontFont(const unsigned char *buffer, size_t bufferByteCount);
		virtual ~FTFontFont();
		Int	GetGlyphCount() const;
	protected:
		virtual FTGlyph*	MakeGlyph(FT_GlyphSlot slot);
	};

	class FTFontFontImpl : public FTFontImpl
	{
	private:
		friend class FTFontFont;
		// Private methods
		FTGlyph*	MakeGlyphImpl(FT_GlyphSlot ftGlyph);
		template <typename T>
		inline FTPoint RenderI(const T *s, const int len, FTPoint position,
			FTPoint spacing, int mode);
	protected:
		// (Con/De)structors
		FTFontFontImpl(FTFont *ftFont, const char *filePath);
		FTFontFontImpl(FTFont *ftFont, const unsigned char *buffer,
			size_t bufferByteCount);
		virtual ~FTFontFontImpl();
		// Etc.
		Int				GetGlyphCount() const;
		virtual bool	FaceSize(const unsigned int size,
							const unsigned int res = 72);
		virtual FTPoint	Render(const char *s, const int len, FTPoint position,
							FTPoint spacing, int renderMode);
		virtual FTPoint	Render(const wchar_t *s, const int len,
							FTPoint position, FTPoint spacing, int renderMode);
	};
}

#endif // FastFTFontFontHppIncluded