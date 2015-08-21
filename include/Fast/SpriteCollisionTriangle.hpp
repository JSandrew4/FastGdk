/******************************************************************************/
/*                                                                            */
/*  SpriteCollisionTriangle.hpp                                               */
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

#ifndef FastSpriteCollisionTriangleHppIncluded
#define FastSpriteCollisionTriangleHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi SpriteCollisionTriangle
	{
	public:
		Vector2D	mComponentA;
		Vector2D	mComponentB;
		Vector2D	mComponentC;
		// (Con/De)structors
		SpriteCollisionTriangle();
		SpriteCollisionTriangle(const SpriteCollisionTriangle &that);
		SpriteCollisionTriangle(const Vector2D &componentA,
			const Vector2D &componentB, const Vector2D &componentC);
		// Operators
		SpriteCollisionTriangle&	operator= (
										const SpriteCollisionTriangle &that);
		Bool						operator==(
										const SpriteCollisionTriangle &that)
										const;
		Bool						operator!=(
										const SpriteCollisionTriangle &that)
										const;
	};

	template class FastApi Array<SpriteCollisionTriangle>;
}

#endif // FastSpriteCollisionTriangleHppIncluded