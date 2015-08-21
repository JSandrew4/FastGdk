/******************************************************************************/
/*                                                                            */
/*  SpriteMapChunk.cpp                                                        */
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

#include <Fast/SpriteMapChunk.hpp>
#include <Fast/SpriteMap.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteMapChunk::SpriteMapChunk() { }

	SpriteMapChunk::SpriteMapChunk(const SpriteMapChunk &that) {
		*this = that;
	}

	SpriteMapChunk::SpriteMapChunk(
		const Point &tileOffset, Int width, Int height)
	{
		mTileOffset = tileOffset;
		mWidth = width;
		mHeight = height;
		mTiles.SetElementCount(mWidth * mHeight);
	}

	SpriteMapChunk::SpriteMapChunk(const Point &tileOffset,
		Int width, Int height, const Array<Short> &tiles)
	{
		mTileOffset = tileOffset;
		mWidth = width;
		mHeight = height;
		mTiles.SetElementCountCapacity(mWidth * mHeight);
		for (Int i = 0; i < mTiles.GetElementCountCapacity(); i++) {
			if (tiles[i] == kFastSpriteMapChunkRLETag) {
				i += 2;
				mTiles.Append(tiles[i], tiles[i-1]);
			} else
				mTiles.Append(tiles[i]);
		}
	}

	SpriteMapChunk::~SpriteMapChunk() { }

	const Point& SpriteMapChunk::GetTileOffset() const {
		return mTileOffset;
	}

	Int SpriteMapChunk::GetWidth() const {
		return mWidth;
	}

	Int SpriteMapChunk::GetHeight() const {
		return mHeight;
	}

	Short SpriteMapChunk::GetTile(Int x, Int y) const {
		Int tileIndex = (mWidth * (x - mTileOffset.mX)) +
			(y - mTileOffset.mY);
		/*
		Int actualTileIndex = 0;
		for (Int i = 0; i < mCompressedTiles.Getsize(); i++) {
			if (mCompressedTiles[i] == kFastSpriteMapChunkRLETag) {
				i++;
				actualTileIndex += mCompressedTiles[i];
				i++;
				if (actualTileIndex >= tileIndex)
					return mCompressedTiles[i];
			} else if (actualTileIndex == tileIndex)
				return mCompressedTiles[i];
			else
				actualTileIndex++;
		}
		*/
		return mTiles[tileIndex];
	}

	Bool SpriteMapChunk::Encloses(Int x, Int y) const {
		return (x >= mTileOffset.mX && y >= mTileOffset.mY &&
			x < mTileOffset.mX + mWidth &&
			y < mTileOffset.mY + mHeight);
	}

	void SpriteMapChunk::GetTiles(Array<Short> &tiles) const {
		tiles = mTiles;
	}

	void SpriteMapChunk::GetCompressedTiles(Array<Short> &tiles) const {
		tiles.Clear();
		for (Int i = 0; i < mTiles.GetElementCount(); i++) {
			Short numRecurringTiles = 1;
			Short currentTile = i;
			for (Int j = i+1; j < mTiles.GetElementCount(); j++) {
				if (mTiles[j] == currentTile)
					numRecurringTiles++;
				else
					break;
			}
			if (numRecurringTiles > 3) {
				tiles.Append((Short)kFastSpriteMapChunkRLETag);
				tiles.Append(numRecurringTiles);
				tiles.Append(mTiles[i]);
				i += numRecurringTiles;
			} else {
				tiles.Append(mTiles[i]);
			}
		}
	}

	void SpriteMapChunk::SetTile(Int x, Int y, Short dictIndex) {
		Int tileIndex = (mWidth * (x - mTileOffset.mX)) +
			(y - mTileOffset.mY);
		/*
		Int actualTileIndex = 0;
		for (Int i = 0; i < mCompressedTiles.GetSize(); i++) {
			if (mCompressedTiles[i] == kFastSpriteMapChunkRLETag) {
				i++;
				if (tileIndex <= (actualTileIndex + mCompressedTiles[i])) {
					Int firstHalfLen = tileIndex - actualTileIndex;
					Int secondHalfLen =
						actualTileIndex + mCompressedTiles[i] - tileIndex - 1;
					if (firstHalfLen > 3) {
						// TODO
					} else {
						for (Int j = 0; j < firstHalfLen; j++) {
							
						}
					}
					if (secondHalfLen > 3) {
						// TODO
					}
					// TODO: assign dictIndex
				} else {
					actualIndex += mCompressedTiles[i];
					i++;
				}
			} else if (actualTileIndex == tileIndex) {
				mCompressedTiles[i] = dictIndex;
				return;
			} else {
				actualTileIndex++;
			}
		}
		*/
		mTiles[tileIndex] = dictIndex;
	}

	void SpriteMapChunk::ReplaceAllTilesOfType(Short oldType, Short newType) {
		for (Int i = 0; i < mTiles.GetElementCount(); i++)
			if (mTiles[i] == oldType)
				mTiles[i] = newType;
	}

	SpriteMapChunk& SpriteMapChunk::operator=(const SpriteMapChunk &that) {
		this->mTileOffset = that.mTileOffset;
		this->mWidth = that.mWidth;
		this->mHeight = that.mHeight;
		this->mTiles = that.mTiles;
		return *this;
	}

	Bool SpriteMapChunk::operator==(const SpriteMapChunk &that) const {
		if (this->mTileOffset != that.mTileOffset)
			return false;
		if (this->mWidth != that.mWidth)
			return false;
		if (this->mHeight != that.mHeight)
			return false;
		if (this->mTiles.GetElementCount() != that.mTiles.GetElementCount())
			return false;
		for (Int i = 0; i < this->mTiles.GetElementCount(); i++)
			if (this->mTiles[i] != that.mTiles[i])
				return false;
		return true;
	}

	Bool SpriteMapChunk::operator!=(const SpriteMapChunk &that) const {
		if (this->mTileOffset != that.mTileOffset)
			return true;
		if (this->mWidth != that.mWidth)
			return true;
		if (this->mHeight != that.mHeight)
			return true;
		if (this->mTiles.GetElementCount() != that.mTiles.GetElementCount())
			return true;
		for (Int i = 0; i < this->mTiles.GetElementCount(); i++)
			if (this->mTiles[i] != that.mTiles[i])
				return true;
		return false;
	}
}