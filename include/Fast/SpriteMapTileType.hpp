/******************************************************************************/
/*                                                                            */
/*  SpriteMapTileType.hpp                                                     */
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

#ifndef FastSpriteMapTileTypeHppIncluded
#define FastSpriteMapTileTypeHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Sprite.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi SpriteMapTileType
	{
	public:
		String	mEntityTypeName;
		Int		mEntityTypeID;
		Sprite	mSprite;
		String	mSpriteName;
		// (Con/De)structors
		SpriteMapTileType(const String &entityTypeName,
			Int entityTypeID, const Sprite &sprite);
		SpriteMapTileType(const SpriteMapTileType &that);
		// Operators
		SpriteMapTileType&	operator= (const SpriteMapTileType &that);
		Bool				operator==(const SpriteMapTileType &that) const;
		Bool				operator!=(const SpriteMapTileType &that) const;
	};

	template class FastApi Array<SpriteMapTileType>;
}

#endif // FastSpriteMapTileTypeHppIncluded