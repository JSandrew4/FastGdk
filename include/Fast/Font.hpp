/******************************************************************************/
/*                                                                            */
/*  Font.hpp                                                                  */
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

#ifndef FastFontHppIncluded
#define FastFontHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Texture2DSurface.hpp>
#include <Fast/Alignment.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/FontCollection.hpp>
#include <Fast/Vector2D.hpp>

#define kFastFontDefaultSize	72

namespace Fast
{
	class String;
	class FontData;
	class FontCollection;
	class Vector3D;
	class Matrix;
	class Quaternion;
	class FrameBufferSurface;

	class FastApi Font : public AssetImplementer<FontCollection, FontResource>
	{
	protected:
		virtual ErrorType	SetUp(const String &fullName,
								const FontData &fontData,
								Int faceResolution, Int faceSize,
								FontCollection *collection);
	public:
		// (Con/De)structors
		Font();
		Font(const Font &that);
		Font(const String &fileName, FontCollection *collection);
		Font(const String &fileName, Int faceResolution,
			Int faceSize, FontCollection *collection);
		Font(StreamReader *streamReader, FontCollection *collection);
		Font(StreamReader *streamReader, Int faceResolution,
			Int faceSize, FontCollection *collection);
		Font(const FontData &fontData, FontCollection *collection);
		Font(const FontData &fontData, Int faceResolution,
			Int faceSize, FontCollection *collection);
		~Font();
		// Allocate functions
		ErrorType	Load(const String &fileName, FontCollection *collection);
		ErrorType	Load(const String &fileName,
						Int faceResolution, Int faceSize,
						FontCollection *collection);
		ErrorType	Load(StreamReader *streamReader,
						FontCollection *collection);
		ErrorType	Load(StreamReader *streamReader,
						Int faceResolution, Int faceSize,
						FontCollection *collection);
		ErrorType	Load(const FontData &fontData, FontCollection *collection);
		ErrorType	Load(const FontData &fontData,
						Int faceResolution, Int faceSize,
						FontCollection *collection);
		void		Unbind();
		// Getters
		Int			GetFaceSize() const;
		Float		GetAscender() const;
		Float		GetDescender() const;
		Float		GetHeight() const;
		Float		GetStringWidth(const String &text);
		Vector2D	GetStringSize(const String &text);
		void		GetStringSize(const String &text, Vector2D *result);
		// Draw functions
		void			DrawString2D(const String &text, Alignment alignment,
							const Vector2D &origin, const Vector2D &scale,
							Float rotationAngle,
							FrameBufferSurface *frameBufferSurface);
		void			DrawString2D(const String &text, Alignment alignment,
							const Matrix &matrix,
							FrameBufferSurface *frameBufferSurface);
		void			DrawString3D(const String &text, Alignment alignment,
							const Vector3D &origin, const Vector3D &scale,
							const Quaternion &rotation,
							FrameBufferSurface *frameBufferSurface);
		void			DrawString3D(const String &text, Alignment alignment,
							const Matrix &matrix,
							FrameBufferSurface *frameBufferSurface);
		virtual void	DrawString(const String &text, Alignment alignment,
							FrameBufferSurface *frameBufferSurface);
		// Operators
		Font&	operator= (const Font &that);
		Bool	operator==(const Font &that);
		Bool	operator!=(const Font &that);
	};
}

#endif // FastFontHppIncluded
