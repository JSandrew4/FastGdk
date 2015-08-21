/******************************************************************************/
/*                                                                            */
/*  SpriteMapCamera.hpp                                                       */
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

#ifndef FastSpriteMapCameraHppIncluded
#define FastSpriteMapCameraHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Box2D.hpp>
#include <Fast/Vector2D.hpp>

namespace Fast
{
	class SpriteMap;

	class FastApi SpriteMapCamera
	{
	private:
		SpriteMap	*mSpriteMap;
		Vector2D	mStartingOrigin;
		Vector2D	mOrigin;
		Float		mStartingRotationDegrees;
		Float		mRotationDegrees;
		Float		mStartingZoom;
		Float		mZoom;
	public:
		// (Con/De)structors
		SpriteMapCamera();
		SpriteMapCamera(const SpriteMapCamera &that);
		SpriteMapCamera(SpriteMap *spriteMap, const Vector2D &startingOrigin,
			Float startingRotationDegrees, Float startingZoom,
			const Vector2D &origin, Float rotationDegrees, Float zoom);
		~SpriteMapCamera();
		// Getters
		SpriteMap*			GetSpriteMap();
		const SpriteMap&	GetSpriteMap() const;
		const Vector2D&		GetStartingOrigin() const;
		const Vector2D&		GetOrigin() const;
		Float				GetStartingRotationDegrees() const;
		Float				GetRotationDegrees() const;
		Float				GetStartingZoom() const;
		Float				GetZoom() const;
		// Setters
		void	SetStartingOrigin(const Vector2D &startingOrigin);
		void	SetOrigin(const Vector2D &origin);
		void	SetStartingRotationDegrees(Float startingRotationDegrees);
		void	SetRotationDegrees(Float rotationDegrees);
		void	SetStartingZoom(Float startingZoom);
		void	SetZoom(Float zoom);
		// Misc
		void	Reset();
		// Operators
		SpriteMapCamera&	operator= (const SpriteMapCamera &that);
		Bool				operator==(const SpriteMapCamera &that) const;
		Bool				operator!=(const SpriteMapCamera &that) const;
	};
}

#endif // FastSpriteMapCameraHppIncluded