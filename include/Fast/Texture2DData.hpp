/******************************************************************************/
/*                                                                            */
/*  Texture2DData.hpp                                                         */
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

#ifndef FastTexture2DDataHppIncluded
#define FastTexture2DDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Texture2DProperties.hpp>
#include <Fast/AssetData.hpp>

namespace Fast
{
	class String;
	class StreamReader;
	class SpriteSheet;

	class FastApi Texture2DData : public AssetData
	{
	private:
		// Members
		Array<Byte>			mPixels;
		Texture2DProperties	mProperties;
		// Load functions
		ErrorType	LoadPng(const String &fileName);
		ErrorType	LoadPng(StreamReader *streamReader);
		ErrorType	LoadBmp(const String &fileName);
		ErrorType	LoadBmp(StreamReader *streamReader);
		ErrorType	LoadJpg(const String &fileName);
		ErrorType	LoadJpg(StreamReader *streamReader);
	public:
		// (Con/De)structors
		Texture2DData();
		Texture2DData(const Texture2DData &that);
		Texture2DData(const Texture2DProperties &properties);
		Texture2DData(const Texture2DProperties &properties,
			const Array<Byte> &pixels);
		Texture2DData(const String &fileName, const SpriteSheet &spriteSheet);
		Texture2DData(StreamReader *streamReader,
			const SpriteSheet &spriteSheet);
		Texture2DData(const String &fileName);
		Texture2DData(StreamReader *streamReader);
		~Texture2DData();
		// Get functions
		const Array<Byte>&			GetPixels() const;
		Int							GetWidth() const;
		Int							GetHeight() const;
		Int							GetBitsPerPixel() const;
		const SpriteSheet&			GetSpriteSheet() const;
		const Texture2DProperties&	GetProperties() const;
		// Set functions
		void	SetPixels(const Texture2DProperties &properties,
					const Array<Byte> &pixels);
		void	SetWidth(Int width);
		void	SetHeight(Int height);
		void	SetBitsPerPixel(Int bitsPerPixel);
		void	SetSize(Int width, Int height, Int bitsPerPixel = 32);
		void	SetSpriteSheet(const SpriteSheet &spriteSheet);
		void	SetProperties(const Texture2DProperties &properties);
		// Allocate functions
		ErrorType	Load(const String &fileName,
						const SpriteSheet &spriteSheet);
		ErrorType	Load(StreamReader *streamReader,
						const SpriteSheet &spriteSheet);
		ErrorType	Load(const String &fileName);
		ErrorType	Load(StreamReader *streamReader);
		void		Unload();
		// Save functions
		ErrorType	SaveAsPng(const String &fileName);
		ErrorType	SaveAsBmp(const String &fileName);
		ErrorType	SaveAsJpg(const String &fileName, UByte quality = 100);
		// Operators
		Texture2DData&	operator= (const Texture2DData &that);
		Bool			operator==(const Texture2DData &that) const;
		Bool			operator!=(const Texture2DData &that) const;
	};
}

#endif // FastTexture2DDataHppIncluded
