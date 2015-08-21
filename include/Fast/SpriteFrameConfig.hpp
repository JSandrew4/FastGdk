/******************************************************************************/
/*                                                                            */
/*  SpriteFrameConfig.hpp                                                     */
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

#ifndef FastSpriteFrameConfigHppIncluded
#define FastSpriteFrameConfigHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi SpriteFrameConfig
	{
	private:
		String		mName;
		Int			mTexture2DIndex;
		Int 		mCollisionModelIndex;
		Vector2D	mOffset;
		Vector2D	mScale;
		Float		mRotationDegrees;
		Bool		mFlipX;
		Bool		mFlipY;
	public:
		// Constructors
		SpriteFrameConfig();
		SpriteFrameConfig(const SpriteFrameConfig &that);
		// Getters
		const String&	GetName() const;
		Int				GetTexture2DIndex() const;
		Int				GetCollisionModelIndex() const;
		const Vector2D&	GetOffset() const;
		const Vector2D&	GetScale() const;
		Float			GetRotationDegrees() const;
		Bool			IsXFlipped() const;
		Bool			IsYFlipped() const;
		// Setters
		void	SetName(const String &name);
		void	SetTexture2DIndex(Int texture2DIndex);
		void	SetCollisionModelIndex(Int collisionModelIndex);
		void	SetOffset(const Vector2D &offset);
		void	SetScale(const Vector2D &scale);
		void	SetRotationDegrees(Float rotationDegrees);
		void	SetFlipX(Bool flipX);
		void	SetFlipY(Bool flipY);
		// Operators
		SpriteFrameConfig&	operator= (const SpriteFrameConfig &that);
		Bool				operator==(const SpriteFrameConfig &that) const;
		Bool				operator!=(const SpriteFrameConfig &that) const;
	};

	template class FastApi Array<SpriteFrameConfig>;
}

#endif // FastSpriteFrameConfigHppIncluded