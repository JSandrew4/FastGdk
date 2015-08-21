/******************************************************************************/
/*                                                                            */
/*  SpriteMapTileType.cpp                                                     */
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

#include <Fast/SpriteMapTileType.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteMapTileType::SpriteMapTileType(const SpriteMapTileType &that) :
		mSprite(that.mSprite)
	{
		*this = that;
	}

	SpriteMapTileType::SpriteMapTileType(const String &entityTypeName,
		Int entityTypeID, const Sprite &sprite) :
		mSprite(sprite)
	{
		mEntityTypeName = entityTypeName;
		mEntityTypeID = entityTypeID;
		mSpriteName = mSprite.GetName();
	}

	SpriteMapTileType& SpriteMapTileType::operator=(
		const SpriteMapTileType &that)
	{
		this->mEntityTypeName = that.mEntityTypeName;
		this->mEntityTypeID = that.mEntityTypeID;
		this->mSprite = that.mSprite;
		this->mSpriteName = that.mSpriteName;
		return *this;
	}

	Bool SpriteMapTileType::operator==(const SpriteMapTileType &that) const {
		if (this->mEntityTypeID != that.mEntityTypeID)
			return true;
		if (this->mEntityTypeName != that.mEntityTypeName)
			return true;
		if (this->mSprite != that.mSprite)
			return true;
		if (this->mSpriteName != that.mSpriteName)
			return true;
		return false;
	}

	Bool SpriteMapTileType::operator!=(const SpriteMapTileType &that) const {
		if (this->mEntityTypeID != that.mEntityTypeID)
			return false;
		if (this->mEntityTypeName != that.mEntityTypeName)
			return false;
		if (this->mSprite != that.mSprite)
			return false;
		if (this->mSpriteName != that.mSpriteName)
			return false;
		return true;
	}
}