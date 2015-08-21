/******************************************************************************/
/*                                                                            */
/*  SpriteMapChunk.hpp                                                        */
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

#ifndef FastSpriteMapChunkHppIncluded
#define FastSpriteMapChunkHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Point.hpp>
#include <Fast/Array.hpp>

#define kFastSpriteMapChunkRLETag	0xffff

namespace Fast
{
	class FastApi SpriteMapChunk
	{
	private:
		Point			mTileOffset;
		Int				mWidth;
		Int				mHeight;
		Array<Short>	mTiles;
	public:
		// (Con/De)structors
		SpriteMapChunk();
		SpriteMapChunk(const SpriteMapChunk &that);
		SpriteMapChunk(const Point &tileOffset, Int width, Int height);
		SpriteMapChunk(const Point &tileOffset, Int width, Int height,
			const Array<Short> &tiles);
		~SpriteMapChunk();
		// Getters
		const Point&	GetTileOffset() const;
		Int				GetWidth() const;
		Int				GetHeight() const;
		Short			GetTile(Int x, Int y) const;
		Bool			Encloses(Int x, Int y) const;
		void			GetTiles(Array<Short> &tiles) const;
		void			GetCompressedTiles(Array<Short> &tiles) const;
		// Setters
		void	SetTile(Int x, Int y, Short dictIndex);
		void	ReplaceAllTilesOfType(Short oldType, Short newType);
		// Operators
		SpriteMapChunk& operator= (const SpriteMapChunk &that);
		Bool			operator==(const SpriteMapChunk &that) const;
		Bool			operator!=(const SpriteMapChunk &that) const;
	};

	template class FastApi Array<SpriteMapChunk>;
}

#endif // FastSpriteMapChunkHppIncluded