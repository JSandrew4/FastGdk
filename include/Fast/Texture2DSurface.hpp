/******************************************************************************/
/*                                                                            */
/*  Texture2DSurface.hpp                                                      */
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

#ifndef FastTexture2DHppIncluded
#define FastTexture2DHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Texture2DCache.hpp>
#include <Fast/Texture2DData.hpp>
#include <Fast/Texture2DCollection.hpp>
#include <Fast/Texture2DResource.hpp>
#include <Fast/SpriteSheet.hpp>

namespace Fast
{
	class String;
	class StreamReader;
	class Rectangle;

	class FastApi Texture2DSurface :
		public AssetImplementer<Texture2DCollection, Texture2DResource>
	{
	private:
		Int	mSubTextureIndex;
		ErrorType	LoadResource(const String &fullName,
						const String &imageName,
						const String &subImageName,
						const Texture2DData &texture2DData,
						Texture2DCollection *collection);
	public:
		// (Con/De)structors
		Texture2DSurface();
		Texture2DSurface(const Texture2DSurface &that);
		Texture2DSurface(UInt openGLTexture2DID,
			Texture2DCollection *collection);
		Texture2DSurface(UInt openGLTexture2DID,
			Texture2DCollection *collection,
			const String &spriteSheetFileName);
		Texture2DSurface(UInt openGLTexture2DID,
			Texture2DCollection *collection,
			const SpriteSheet &spriteSheet);
		Texture2DSurface(const String &fileName,
			Texture2DCollection *collection);
		Texture2DSurface(const String &fileName,
			Texture2DCollection *collection,
			const String &spriteSheetFileName);
		Texture2DSurface(const String &fileName,
			Texture2DCollection *collection,
			const SpriteSheet &spriteSheet);
		Texture2DSurface(StreamReader *streamReader,
			Texture2DCollection *collection);
		Texture2DSurface(StreamReader *streamReader,
			Texture2DCollection *collection,
			const String &spriteSheetFileName);
		Texture2DSurface(StreamReader *streamReader,
			Texture2DCollection *collection,
			const SpriteSheet &spriteSheet);
		Texture2DSurface(const Texture2DData &texture2DData,
			Texture2DCollection *collection);
		Texture2DSurface(const Texture2DData &texture2DData,
			Texture2DCollection *collection,
			const String &subImageName);
		~Texture2DSurface();
		// Load functions
		ErrorType	Load(UInt openGLTexture2DID,
						Texture2DCollection *collection);
		ErrorType	Load(UInt openGLTexture2DID,
						Texture2DCollection *collection,
						const String &spriteSheetFileName);
		ErrorType	Load(UInt openGLTexture2DID,
						Texture2DCollection *collection,
						const SpriteSheet &spriteSheet);
		ErrorType	Load(const String &fileName,
						Texture2DCollection *collection);
		ErrorType	Load(const String &fileName,
						Texture2DCollection *collection,
						const String &spriteSheetFileName);
		ErrorType	Load(const String &fileName,
						Texture2DCollection *collection,
						const SpriteSheet &spriteSheet);
		ErrorType	Load(StreamReader *streamReader,
						Texture2DCollection *collection);
		ErrorType	Load(StreamReader *streamReader,
						Texture2DCollection *collection,
						const String &spriteSheetFileName);
		ErrorType	Load(StreamReader *streamReader,
						Texture2DCollection *collection,
						const SpriteSheet &spriteSheet);
		ErrorType	Load(const Texture2DData &texture2DData,
						Texture2DCollection *collection);
		ErrorType	Load(const Texture2DData &texture2DData,
						Texture2DCollection *collection,
						const String &subImageName);
		void		Unbind();
		// Getters
		Int					GetSubTexture2DIndex() const;
		Int					GetWidth() const;
		Int					GetHeight() const;
		Texture2DData		GetData();
		void				GetData(Texture2DData *texture2DData);
		// Setters
		void	SetSubTexture(Int subTexture2DIndex);
		void	SetSubTexture(const String &subTexture2DName);
		// Operators
		Texture2DSurface&	operator= (const Texture2DSurface &that);
		Bool				operator==(const Texture2DSurface &that) const;
		Bool				operator!=(const Texture2DSurface &that) const;
	};
}

#endif // FastTexture2DHppIncluded
