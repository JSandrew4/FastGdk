/******************************************************************************/
/*                                                                            */
/*  FontCollection.hpp                                                        */
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

#ifndef FastFontCollectionHppIncluded
#define FastFontCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetCollectionVerifiable.hpp>
#include <Fast/FontResource.hpp>

namespace Fast
{
	class String;
	class StreamReader;
	class AssetData;
	class Texture2DCollection;

	template class FastApi AssetCollectionVerifiable<FontResource>;

	class FastApi FontCollection :
		public AssetCollectionVerifiable<FontResource>
	{
	private:
		// Hide these functions. No copying collections!
		FontCollection(const FontCollection &that) :
			mTexture2DCollection(that.mTexture2DCollection)
			{ }
		FontCollection& operator=(const FontCollection &that) { return *this; }
	protected:
		Texture2DCollection	&mTexture2DCollection;
	public:
		// (Con/De)structors
		FontCollection(Texture2DCollection *texture2DCollection);
		~FontCollection();
		// Allocation functions
		ErrorType	LoadResource(const String &fileName);
		ErrorType	LoadResource(const String &fileName,
						Int faceResolution, Int faceSize);
		ErrorType	LoadResource(StreamReader *streamReader);
		ErrorType	LoadResource(StreamReader *streamReader,
						Int faceResolution, Int faceSize);
		ErrorType	LoadResource(const AssetData &assetData);
		ErrorType	LoadResource(const AssetData &assetData,
						Int faceResolution, Int faceSize);
		void		UnloadResource(Int id);
		// Get functions
		Texture2DCollection*		GetTexture2DCollection();
		const Texture2DCollection&	GetTexture2DCollection() const;
	};
}

#endif // FastFontCollectionHppIncluded
