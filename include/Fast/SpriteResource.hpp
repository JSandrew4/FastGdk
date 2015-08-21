/******************************************************************************/
/*                                                                            */
/*  SpriteResource.hpp                                                        */
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

#ifndef FastSpriteResourceHppIncluded
#define FastSpriteResourceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetResourceBase.hpp>
#include <Fast/SpriteProperties.hpp>
#include <Fast/AssetResourceVerifiableBase.hpp>
#include <Fast/SpriteData.hpp>
#include <Fast/Array.hpp>
#include <Fast/Texture2DSurface.hpp>

namespace Fast
{
	template class FastApi Array<Texture2DSurface>;

	class FastApi SpriteResource : public AssetResourceBase<SpriteProperties>,
		public AssetResourceVerifiableBase
	{
	protected:
		SpriteData				mData;
		Array<Texture2DSurface>	mTexture2DSurfaceArray;
	public:
		// Constructor
		SpriteResource();
		// Getters
		SpriteData*						GetData();
		const SpriteData&				GetData() const;
		Array<Texture2DSurface>*		GetTexture2DSurfaceArray();
		const Array<Texture2DSurface>	GetTexture2DSurfaceArray() const;
	};
}

#endif // FastSpriteResourceHppIncluded