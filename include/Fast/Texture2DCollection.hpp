/******************************************************************************/
/*                                                                            */
/*  Texture2DCollection.hpp                                                   */
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

#ifndef FastTexture2DCollectionHppIncluded
#define FastTexture2DCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetCollectionVerifiable.hpp>
#include <Fast/Texture2DResource.hpp>

namespace Fast
{
	class GraphicsContext;
	class StreamReader;

	template class FastApi AssetCollectionVerifiable<Texture2DResource>;

	class FastApi Texture2DCollection :
		public AssetCollectionVerifiable<Texture2DResource>
	{
	private:
		// Hide these functions. No copying collections!
		Texture2DCollection(const Texture2DCollection &that) :
			mGraphicsContext(that.mGraphicsContext)
			{ }
		Texture2DCollection& operator=(const Texture2DCollection &that)
			{ return *this; }
	protected:
		GraphicsContext	&mGraphicsContext;
	public:
		// (Con/De)structors
		Texture2DCollection(GraphicsContext *graphicsContext);
		~Texture2DCollection();
		// Allocators
		ErrorType	LoadResource(const String &fileName);
		ErrorType	LoadResource(const String &fileName,
						const String &spriteSheetFileName);
		ErrorType	LoadResource(const String &fileName,
						const SpriteSheet &spriteSheet);
		ErrorType	LoadResource(StreamReader *streamReader);
		ErrorType	LoadResource(StreamReader *streamReader,
						const String &spriteSheetFileName);
		ErrorType	LoadResource(StreamReader *streamReader,
						const SpriteSheet &spriteSheet);
		ErrorType	LoadResource(const AssetData &assetData);
		void		UnloadResource(Int id);
		// Getters
		Int						GetIDByOpenGLID(UInt openGLTexture2DID) const;
		GraphicsContext*		GetGraphicsContext();
		const GraphicsContext&	GetGraphicsContext() const;
	};
}

#endif // FastTexture2DCollectionHppIncluded
