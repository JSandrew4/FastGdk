/******************************************************************************/
/*                                                                            */
/*  Box2D.hpp                                                                 */
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

#ifndef FastBox2DHppIncluded
#define FastBox2DHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector2D.hpp>

namespace Fast
{
	class FastApi Box2D
	{
	public:
		// Members
		Vector2D	mOrigin;
		Vector2D	mSize;
		// (Con/De)structors
		Box2D();
		Box2D(const Box2D &that);
		Box2D(const Vector2D &origin, const Vector2D &size);
		Box2D(Float originX, Float originY, Float sizeX, Float sizeY);
		~Box2D();
		// Operators
		Box2D&	operator= (const Box2D &that);
		Bool	operator==(const Box2D &that) const;
		Bool	operator!=(const Box2D &that) const;
	};
}

#endif // FastBox2DHppIncluded