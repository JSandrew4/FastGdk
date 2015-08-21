/******************************************************************************/
/*                                                                            */
/*  Texture2DFont.hpp                                                         */
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

#ifndef FastTexture2DFontHppIncluded
#define FastTexture2DFontHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Font.hpp>

namespace Fast
{
	class String;
	class FontData;
	class FontCollection;
	class Vector3D;
	class Matrix;
	class Quaternion;

	class FastApi Texture2DFont : public Font
	{
	protected:
		ErrorType	SetUp(const String &fullName, const FontData &fontData,
						Int faceResolution, Int faceSize,
						FontCollection *collection);
	public:
		// (Con/De)structors
		Texture2DFont();
		Texture2DFont(const Texture2DFont &that);
		Texture2DFont(const String &fileName, FontCollection *collection);
		Texture2DFont(const String &fileName, Int faceResolution,
			Int faceSize, FontCollection *collection);
		Texture2DFont(StreamReader *streamReader, FontCollection *collection);
		Texture2DFont(StreamReader *streamReader, Int faceResolution,
			Int faceSize, FontCollection *collection);
		Texture2DFont(const FontData &fontData, FontCollection *collection);
		Texture2DFont(const FontData &fontData, Int faceResolution,
			Int faceSize, FontCollection *collection);
		~Texture2DFont();
		// Draw functions
		void 	DrawString(const String &text, Alignment alignment);
		// Operators
		Texture2DFont&	operator= (const Texture2DFont &that);
		Bool			operator==(const Texture2DFont &that);
		Bool			operator!=(const Texture2DFont &that);
	};
}

#endif // FastTexture2DFontHppIncluded
