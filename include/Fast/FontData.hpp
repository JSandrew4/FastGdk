/******************************************************************************/
/*                                                                            */
/*  FontData.hpp                                                              */
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

#ifndef FastFontDataHppIncluded
#define FastFontDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetData.hpp>
#include <Fast/Array.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/FontProperties.hpp>

namespace Fast
{
	class String;
	class StreamReader;

	class FastApi FontData : public AssetData
	{
	protected:
		FontProperties	mProperties;
		CFTFontFont	*mFTFontFont;
		Array<Byte>		mFileByteArray;
		// Internal functions
		ErrorType	LoadFTFontFont(const String &name,
						Int faceSize, Int faceResolution);
	public:
		FontData();
		FontData(const FontData &that);
		FontData(const String &fileName);
		FontData(const String &fileName, Int faceSize, Int faceResolution);
		FontData(StreamReader *streamReader);
		FontData(StreamReader *streamReader, Int faceSize, Int faceResolution);
		~FontData();
		// Allocators
		ErrorType	Load(const String &fileName);
		ErrorType	Load(const String &fileName, Int faceSize,
						Int faceResolution);
		ErrorType	Load(StreamReader *streamReader);
		ErrorType	Load(StreamReader *streamReader,
						Int faceSize, Int faceResolution);
		void		Unload();
		// Getters
		Int					GetFaceSize() const;
		Float				GetAscender() const;
		Float				GetDescender() const;
		Float				GetHeight() const;
		Int					GetGlyphCount() const;
		// Operators
		FontData&	operator= (const FontData &that);
		Bool		operator==(const FontData &that) const;
		Bool		operator!=(const FontData &that) const;
	};
}

#endif // FastFontDataHppIncluded
